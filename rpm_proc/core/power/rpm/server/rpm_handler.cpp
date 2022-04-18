/*===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include <assert.h>
#include <string.h>

#include "time_service.h"
#include "CoreVerify.h"

#include "rpm_config.h"
#include "rpm_estimator.h"
#include "rpm_handler.h"
#include "rpmserver_internal.h"
#include "swevent.h"
#include "rpm_settling_timer.h"
#include "rpm_spm_handshake.h"
#include <stddef.h>
#include "DALSys.h"
#include "glink.h"
#include "glink_rpm.h"


static const unsigned ERR_KEY  = 0x00727265;
static const unsigned MSG__KEY  = 0x2367736d;
static const unsigned TRNS__KEY  = 0x736e7274;

static boolean disable_settling = TRUE;

static unsigned v1_to_v0_service(rpm_v1_service_type v1_type)
{
  switch(v1_type)
  {
    case RPM_V1_REQUEST_SERVICE:
        return RPM_REQUEST_SERVICE;	    
    case RPM_V1_SYSTEMDB_SERVICE:
        return RPM_SYSTEMDB_SERVICE;	    
    case RPM_V1_COMMAND_SERVICE:
        return RPM_COMMAND_SERVICE;	    
    default:
        return (unsigned)v1_type;
  }
}

static void memscpy_word_aligned(void * dst, size_t dst_size, void * src, size_t src_size)
{
    CORE_VERIFY(dst);
    CORE_VERIFY(src);
    CORE_VERIFY(dst_size % 4 == 0); 
    CORE_VERIFY(src_size % 4 == 0); 
    //memscpy(dst, dst_size, src, src_size);
    memcpy(dst, src, dst_size);
}

void rpm_glink_link_state_isr(glink_link_info_type *link_info, Handler *handler)
{
    switch(link_info->link_state)
    {	    
        case GLINK_LINK_STATE_UP:
            handler->portOpen();		
            break;
	case GLINK_LINK_STATE_DOWN:
            break;
    }	
}	

void rpm_glink_port_state_isr(glink_handle_type port, Handler *handler, glink_channel_event_type event)
{
    CORE_VERIFY(port == handler->glinkPort_);
    switch(event)
    {	    
        case GLINK_CONNECTED:
            break;
	case GLINK_REMOTE_DISCONNECTED:
            CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_close(port));
            break;
        case GLINK_LOCAL_DISCONNECTED:
            break;
    }	
}	

void rpm_glink_handler(glink_handle_type port, Handler *handler, void *unused_intent_data,
		         void *buffer, size_t size, size_t intent_used, 
                         glink_buffer_provider_fn vprovider, glink_buffer_provider_fn pprovider)
{
	handler->rpm_glink_enqueue(port, unused_intent_data, buffer, size, intent_used, vprovider, pprovider);
}

void Handler::rpm_glink_enqueue(glink_handle_type port, void *unused_intent_data, 
                         void *buffer, size_t size, size_t intent_used, 
                         glink_buffer_provider_fn vprovider, glink_buffer_provider_fn pprovider)
{
    void  *vector;    
    size_t vector_size, rx_buffer_offset = 0;

    if((port != glinkPort_) || (size == 0))
        return;

    //make sure the buffer is big enough to fit the request
    if(size > rxBufLen_)
        ERR_FATAL("Need larger RPM rx buffer.", size, sizeof(rxBuf_), 0);

    handlerStart_ = time_service_now();

    //read the raw message
    do
    {
        vector = vprovider(buffer, rx_buffer_offset, &vector_size);
        if(vector)
        {
            memscpy_word_aligned(rxBuf_ + (rx_buffer_offset/sizeof(unsigned)), vector_size, vector, vector_size);
            rx_buffer_offset += vector_size;    
        }   
    } while(vector);

    CORE_VERIFY(rx_buffer_offset == size);   

    haveMessageLen_ = rx_buffer_offset;

    //do the basic message processing    
    haveMessage_ = loadMessage();

    //if we still have processing, schedule the message
    if(haveMessage_)
    {
        SWEVENT(RPM_MESSAGE_RECEIVED, ee_, messageHeader_->msg_id, messageHeader_->set);

        // We have a message to process.  Now we need to decide if we handle it now
        // or later--NAS requests don't actually get processed immediately unless
        // there's an aborted wakeup indicated.
        uint32 sig_value;
        CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_sigs_remote_get(glinkPort_, &sig_value));
        if(messageHeader_->set == RPM_NEXT_ACTIVE_SET && !sig_value)
            return; // Don't process this yet.
        else
        {
            isIdle_ = false;
            isHandlerDispatching_ = true;
            state_ = DISPATCH;

            CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_rpm_mask_rx_interrupt(glinkPort_, true, NULL));

            //[MDA] TODO: Figure out a way to determine if this is from the polling or isr context
            schedule_me(); // Plop us into the immediate queue.
        }
    }	
}

static void rpm_glink_tx_done_isr(void)
{
  //empty function for tx_done cb. Nothing required here for now since we are always in 
  //"single-threaded" operation of sending GLink requests
}

static void rpm_settling_handler(Handler *handler)
{
    handler->requeue_settling();
}

Handler::Handler(unsigned ee, unsigned rxbuflen, uint8_t priority)
    : Task(priority), glinkPort_(0), ee_(ee), haveMessage_(false), isIdle_(true),
      haveMessageLen_ (0), rxBuf_ (0), rxBufLen_ (rxbuflen), messageHeader_ (NULL), error_(0),
      resource_(0), state_(IDLE), isHandlerSettling_(false), isHandlerDispatching_(false),
      handlerStart_(0), handlerEnd_(0), immediateLatencyExceeded_(0)
{
    DALSYS_Malloc (rxbuflen, (void **)&rxBuf_);
    rxKvp_ = kvp_create(0);
    txKvp_ = kvp_create(64);

    for (unsigned i = 0; i<NUM_SETTLING_CONTEXTS; i++)
    {
        settlingMsg_[i].r = NULL;
        settlingMsg_[i].msg_id = 0;
        settlingMsg_[i].settling_time = 0;
    }
}

Handler::~Handler()
{
    kvp_destroy(rxKvp_);
    kvp_destroy(txKvp_);
}

void Handler::portOpen()
{
    glink_open_config_type glink_open_cfg = {0};
    glink_open_cfg.name = "rpm_requests";    
    glink_open_cfg.remote_ss = rpm->ees[ee_].remote_ss;    
    glink_open_cfg.notify_rxv = (glink_rxv_notification_cb)rpm_glink_handler;    
    glink_open_cfg.notify_tx_done = (glink_tx_notification_cb)rpm_glink_tx_done_isr;    
    glink_open_cfg.notify_state = (glink_state_notification_cb)rpm_glink_port_state_isr;    
    glink_open_cfg.priv = this;    

    CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_open(&glink_open_cfg, &glinkPort_));
}

void Handler::init()
{
    glink_link_id_type link_cfg = {1, NULL, rpm->ees[ee_].remote_ss, (glink_link_state_notif_cb)rpm_glink_link_state_isr, glinkLink_};
    CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_register_link_state_cb(&link_cfg, this));
}

void Handler::requeue_settling(void)
{
    if(isIdle_)
    {
        for(unsigned i = 0; i<NUM_SETTLING_CONTEXTS; i++)
        {
            if(settlingMsg_[i].msg_id)
            {
                SWEVENT(RPM_SETTLING_MESSAGE_REQUEUED, ee_);
                state_ = SETTLING;
                isIdle_ = false;
                resource_ = settlingMsg_[i].r;
                schedule_me(); // Plop us into the immediate queue.
                break;
            }
        }
    }
}

uint64_t Handler::get_length() const
{
    if(isIdle_)
        return 0;

    unsigned estimate = resource_estimate(resource_, theEstimator().currentOperatingPoint());
    if(disable_settling)
    {
        return (estimate + resource_settling_estimate(resource_));
    }
    return estimate;
}

bool Handler::hasImmediateWork() const
{
    return !isIdle_;
}

boolean Handler::register_settling_slot(unsigned msg_id, uint64 settling_time)
{
    boolean slot_found = FALSE;
    slot_found =  settling_timer_register((settling_callback)rpm_settling_handler, (void *)this, settling_time);
    if(slot_found)
    {
        slot_found = FALSE;
        for (unsigned i = 0; i < NUM_SETTLING_CONTEXTS; i++)
        {
            if(!settlingMsg_[i].msg_id)
            {
                slot_found = TRUE;
                settlingMsg_[i].msg_id = msg_id;
                settlingMsg_[i].r = resource_;
                settlingMsg_[i].settling_time = settling_time;
                return TRUE;
            }
        }
    }
    return FALSE;
}

/*===========================================================================
FUNCTION: Handler::execute_until

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void Handler::execute_until(volatile bool &preempt, uint64_t stop_time)
{
    uint64 settling_time = 0;
    INTLOCK();

    RPMMessageHeader *header = messageHeader_;

    // If we're dispatching NAS from here, it's because there's a rude wakeup.  Treat it as active set.
    if(RPM_NEXT_ACTIVE_SET == header->set)
        header->set = RPM_ACTIVE_SET;


    switch(state_)
    {
        case DISPATCH:
        {
            settling_time = processMessage (preempt, stop_time, header, true);
            isHandlerDispatching_ = false;
            haveMessage_ = false;
            if(!settling_time)
            {
                bool handler_settling = false;
                //if the current message was set up for prior settling, clear it
                for(unsigned i = 0; i<NUM_SETTLING_CONTEXTS; i++)
                {
                    if(settlingMsg_[i].msg_id == header->msg_id)
                    {
                        settlingMsg_[i].r = NULL;
                        settlingMsg_[i].msg_id = 0;
                        settlingMsg_[i].settling_time = 0;
                    }
                    else if(settlingMsg_[i].msg_id)
                    {
                        handler_settling = true;
                    }
                }

                isHandlerSettling_ = handler_settling;
                //no settling time for this message, but lets check if there are other resources settling
                if(isHandlerSettling_)
                    state_ = SETTLING;
                else
                    state_ = CLEANUP;
            }
            else
            {
                //make sure we have room for this and register a a settling timer
                CORE_VERIFY(register_settling_slot(header->msg_id, settling_time));
                SWEVENT(RPM_RESOURCE_SETTLING, ee_, (rpm_resource_type)header->resource_type, header->resource_id, header->msg_id);
                SWEVENT(RPM_RESOURCE_SETTLING_TIME, (uint32)settling_time, (uint32)(settling_time >> 32));

                //if there are other messages settling, go to settling, otherwise jump out
                if(isHandlerSettling_)
                {
                    state_ = SETTLING;
                }
                else
                {
                    //jump to cleanup, check for more messages
                    isHandlerSettling_ = true;
                    state_ = CLEANUP;
                }
            }
        }

        case SETTLING:
        {
            if(state_ == SETTLING)
            {
                uint64 current_time = time_service_now();
                uint64 new_time = 0;
                bool settling_flag = false;
                //try to handle anything that is currently settilng
                for(unsigned i = 0; i<NUM_SETTLING_CONTEXTS; i++)
                {
                    if(settlingMsg_[i].settling_time && (settlingMsg_[i].settling_time <= current_time))
                    {
                        //found a request that should be done settling. Re-call the apply function and get rid of the local data store
                        new_time = resource_ee_settling_apply(settlingMsg_[i].r, ee_, settlingMsg_[i].settling_time);
                        //if its settled, finish the message. Otherwise re-queue
                        if(!new_time)
                        {
                            settling_flag |= false;
                            SWEVENT(RPM_RESOURCE_SETTLING_COMPLETE, ee_, (rpm->classes[settlingMsg_[i].r->class_idx]).type,
                                                                   settlingMsg_[i].r->id, settlingMsg_[i].msg_id);
                            writeResponse(settlingMsg_[i].msg_id, 0, RPM_MESSAGE_ERROR_NONE, RPM_REQUEST_SERVICE);

                            settlingMsg_[i].r = NULL;
                            settlingMsg_[i].msg_id = 0;
                            settlingMsg_[i].settling_time = 0;

                        }
                        else
                        {
                            settlingMsg_[i].settling_time = new_time;
                            settling_flag = true;
                            CORE_VERIFY(settling_timer_register((settling_callback)rpm_settling_handler, (void *)this, new_time));

                            SWEVENT(RPM_RESOURCE_SETTLING, ee_, (rpm->classes[settlingMsg_[i].r->class_idx]).type, settlingMsg_[i].r->id, settlingMsg_[i].msg_id);
                            SWEVENT(RPM_RESOURCE_SETTLING_TIME, (uint32)new_time, (uint32)(new_time >> 32));
                        }
                    }
                }
                isHandlerSettling_ = settling_flag;
                state_ = CLEANUP;
            }
        }

        case CLEANUP:
        {
            // Check to see if we're done.
	        glink_rpm_rx_poll(glinkPort_);
                
            uint32 sig_value;
	        CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_sigs_remote_get(glinkPort_, &sig_value));
            if(!haveMessage_ || (header->set == RPM_NEXT_ACTIVE_SET && !sig_value))
            {
                isIdle_ = true;
                state_ = IDLE;
                CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_rpm_mask_rx_interrupt(glinkPort_, false, NULL));
            }
            else
            {
                CORE_VERIFY(!isIdle_);
                state_ = DISPATCH;
                isHandlerDispatching_ = true;
            }
        }
		
		case IDLE:
          break;
    }
    INTFREE();
}

void Handler::processCommand(RPMCommandHeader *header, char *data)
{
    unsigned               type, length, cmd_data;
    const char             *value_ptr;

    SWEVENT(RPM_COMMAND_RECEIVED, ee_, messageHeader_->msg_id);

    kvp_swapbuffer(rxKvp_, data, header->msg_size);
    if(!kvp_get( rxKvp_, &type, &length, &value_ptr ) || !value_ptr)
    {
        writeResponse(type, "Malformed command", RPM_MESSAGE_ERROR_MALFORMED_COMMAND, RPM_COMMAND_SERVICE);
        return;
    }

    switch(type)
    {
        case RPM_TRANSITION_COMMAND:
            cmd_data = *(unsigned *)value_ptr;
            rpm_spm_soft_transition(ee_, (rpm_spm_entry_reason)cmd_data);
            break;
        default:
            abort();
    }
}

const char *Handler::processHeader(RPMMessageHeader *header, rpm_message_error_type *v1_error, char *data)
{
    // Validate the incoming message, and ignore it if there is any "bad" data.
    if((header->set > RPM_NEXT_ACTIVE_SET) ||
     (header->data_len != ((header->msg_size - sizeof(RPMMessageHeader)) + offsetof(RPMMessageHeader, msg_id))))
    {
        *v1_error = RPM_MESSAGE_ERROR_INVALID_HEADER;	    
        return "invalid header";
    }

    // Try to find the target resource.
    resource_ = rpmserver_lookup_resource((rpm_resource_type)header->resource_type, header->resource_id);
    if(!resource_)
    {
        *v1_error = RPM_MESSAGE_ERROR_RESOURCE_DOES_NOT_EXIST;	    
        return "resource does not exist";
    }

    kvp_swapbuffer(rxKvp_, data, header->data_len);
    return 0;
}

void Handler::writeResponse(unsigned data, const char *error, rpm_message_error_type error_type, rpm_service_type service)
{
    unsigned data_key = MSG__KEY;

    if(service == RPM_COMMAND_SERVICE)
        data_key = TRNS__KEY;

    //intlock since txKvp_ is shared
    INTLOCK();

    // don't use bitpacked responses for commands for now
    if((messageVersion_ == 0) || (service != RPM_REQUEST_SERVICE))
    {
        // Build the response KVP's.
        kvp_clear(txKvp_);
        kvp_put(txKvp_, data_key, sizeof(unsigned), (char *)&(data));
        if(error)
            kvp_put(txKvp_, ERR_KEY, strlen(error), error);

        // Mark this message as a response to a request.
        RPMCommandHeader ack = {service, kvp_get_raw_size(txKvp_)};

        //copy the data into the transmit buffer
        memscpy_word_aligned((char *)rpm->tx_buf, sizeof(RPMCommandHeader), &ack, sizeof(RPMCommandHeader));
        memscpy_word_aligned(((char *)rpm->tx_buf) + sizeof(RPMCommandHeader), ack.msg_size, (void *)kvp_get_raw_bytes(txKvp_), ack.msg_size);

        SWEVENT(RPM_SEND_RESPONSE, ee_, service);

        // Write it out.
        CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_tx(glinkPort_, NULL, rpm->tx_buf, ack.msg_size + sizeof(RPMCommandHeader), false)); 
    }	
    else if (messageVersion_ == 1)
    {
        unsigned tx_size = 0;	    
        if(service != RPM_REQUEST_SERVICE)
        {
            //Shouldn't have v1 requests for any other request type
            abort();
        }		

        switch(error_type)
        {
            case RPM_MESSAGE_ERROR_NONE:
            {
                //send ACK
                RPMAckPacketV1 ack = {{}, data};  
                tx_size = sizeof(RPMAckPacketV1);
                ack.msg_header.size = sizeof(RPMAckPacketV1) - sizeof(unsigned);
                ack.msg_header.type = RPM_V1_ACK_SERVICE;
                ack.msg_header.version = 1;
                //copy the data into the transmit buffer
                memscpy_word_aligned((char *)rpm->tx_buf, tx_size, &ack, tx_size);
                break;		
            }	
	    case RPM_MESSAGE_ERROR_INVALID_MESSAGE:         
	    case RPM_MESSAGE_ERROR_MALFORMED_COMMAND:       
	    case RPM_MESSAGE_ERROR_INVALID_HEADER:          
	    case RPM_MESSAGE_ERROR_RESOURCE_DOES_NOT_EXIST:
	    {
                //send NACK
                RPMNackPacketV1 nack = {{}, data, error_type};  
                tx_size = sizeof(RPMNackPacketV1);
                nack.msg_header.size = sizeof(RPMNackPacketV1) - sizeof(unsigned);
                nack.msg_header.type = RPM_V1_NACK_SERVICE;
                nack.msg_header.version = 1;
                //copy the data into the transmit buffer
                memscpy_word_aligned((char *)rpm->tx_buf, tx_size, &nack, tx_size);
                break;		
	    }
	    default :
            {	    
	        abort();
            }
        }

        SWEVENT(RPM_SEND_RESPONSE, ee_, service);

        // Write it out.
        CORE_VERIFY(GLINK_STATUS_SUCCESS == glink_tx(glinkPort_, NULL, rpm->tx_buf, tx_size, false)); 
    }    
    else
    {
        //only 2 supported versions for now	
	abort();
    }	    

    handlerEnd_ = time_service_now();

    INTFREE();
}

bool Handler::loadMessageV0(unsigned msg_type)
{
    bool retval = true;    

    if((haveMessageLen_ < sizeof(RPMMessageHeader) && (msg_type != RPM_COMMAND_SERVICE)) ||
       (haveMessageLen_ < sizeof(RPMCommandHeader) && (msg_type == RPM_COMMAND_SERVICE)))
    {
        writeResponse(0, "invalid message", RPM_MESSAGE_ERROR_INVALID_MESSAGE, RPM_REQUEST_SERVICE);
        return false;
    }

    messageVersion_ = 0;

    switch (msg_type)
    {
        case RPM_REQUEST_SERVICE:
            messageHeader_ = (RPMMessageHeader *)rxBuf_;
            rxBufHeaderOffset_ = sizeof(RPMMessageHeader)/sizeof(unsigned);
            if (messageHeader_->set != RPM_NEXT_ACTIVE_SET)
            {
                rpm_message_error_type v1_error;		    
                const char *error = processHeader(messageHeader_, &v1_error, (char *)(rxBuf_ + rxBufHeaderOffset_));
                if(error)
                {
                    writeResponse(messageHeader_->msg_id, error, v1_error, RPM_REQUEST_SERVICE);
                    retval = false;
                }
            }
            break;

        case RPM_COMMAND_SERVICE:
            commandHeader_ = (RPMCommandHeader *)rxBuf_;
            rxBufHeaderOffset_ = sizeof(RPMMessageHeader)/sizeof(unsigned);
            processCommand(commandHeader_, (char*)(rxBuf_ + rxBufHeaderOffset_));
            retval = false;
            break;

        default:
            handleAlternateServiceMessage(rxBuf_[0], &rxBuf_[1], haveMessageLen_ - 4);
            retval = false;
            break;
    }
    return retval;
}

bool Handler::loadMessageV1(RPMMessageHeaderV1 *v1_header)
{
    bool retval = true;    
    unsigned msg_type = v1_to_v0_service((rpm_v1_service_type)(v1_header->msg_header.type));   

    messageVersion_ = 1;

    switch (msg_type)
    {
        case RPM_REQUEST_SERVICE:
            //put together the standard message header from the bitpacked V1 header		
	    //point the standard message header at a valid message header structure
	    messageHeader_ = &messageHeaderV1_;
	    messageHeader_->msg_type      = msg_type;
	    messageHeader_->msg_size      = v1_header->msg_header.size + (sizeof(RPMMessageHeader) - (sizeof(RPMMessageHeaderV1) + sizeof(unsigned)));
	    messageHeader_->msg_id        = v1_header->msg_id;
	    messageHeader_->set           = v1_header->request_details.set;
	    messageHeader_->resource_type = v1_header->resource_type;
	    messageHeader_->resource_id   = v1_header->request_details.resource_id;
	    messageHeader_->data_len      = v1_header->request_details.data_len;

	    //V1 bitpacked header is before the kvp buffer
	    rxBufHeaderOffset_ = sizeof(RPMMessageHeaderV1)/sizeof(unsigned);

            if (messageHeader_->set != RPM_NEXT_ACTIVE_SET)
            {
                rpm_message_error_type v1_error;		    
                const char *error = processHeader(messageHeader_, &v1_error, (char*)(rxBuf_ + rxBufHeaderOffset_));
                if(error)
                {
                    writeResponse(messageHeader_->msg_id, error, v1_error, RPM_REQUEST_SERVICE);
                    retval = false;
                }
            }
            break;

        case RPM_COMMAND_SERVICE:
            commandHeader_->msg_size = v1_header->msg_header.size;
            commandHeader_->msg_type = msg_type;

	    //Common header is the only header info before the kvp buffer
	    rxBufHeaderOffset_ = 1;

            processCommand(commandHeader_, (char*)(rxBuf_ + rxBufHeaderOffset_));
            retval = false;
            break;

        default:
            handleAlternateServiceMessage(rxBuf_[0], &rxBuf_[1], haveMessageLen_ - 4);
            retval = false;
            break;
    }
    return retval;
}

bool Handler::loadMessage()
{
    unsigned header = *(unsigned *)rxBuf_;
    bool retval = true;    
    unsigned msg_ver = MESSAGING_UNPACK_VERSION(header); 
    if(!msg_ver)
    {
        retval = loadMessageV0(header);
    }   
    else if(msg_ver == 1)
    {
        retval = loadMessageV1((RPMMessageHeaderV1*)rxBuf_);
    }	   
    else
    {
        //not a supported messaging version	    
        abort();
    }	    

    return retval;
}

void Handler::handleAlternateServiceMessage(unsigned service, void *data, unsigned length)
{
    INTLOCK();

    rpmserver_service_t *s = rpm_alt_service_list;

    for(; s; s = s->next)
    {
        if(service == s->service_id)
        {
            s->cb(ee_, data, length, s->context);
            break;
        }
    }

    INTFREE();
}

uint64 Handler::processMessage (volatile bool &preempt, uint64_t &stop_time, RPMMessageHeader *header, bool allow_settling)
{
    uint64 settling_time = 0;
    bool applied = false;
  // Temporarily commenting this section out - it is causing freezes on LA. Need to debug further.
#if 0
  if (preempt ||
      (time_service_now () + resource_estimate (resource_, theEstimator().currentOperatingPoint()) > stop_time))
  {
    return;
  }
#endif

    // Start timing how long this takes.
    Estimator  &estimator = theEstimator();
    Observation obs       = estimator.startObservation();
    uint64 observed_settling = 0;

    // Issue the request to the resource.
    SWEVENT(RPM_PROCESS_REQUEST, ee_, (rpm_resource_type)header->resource_type, header->resource_id);
    applied = resource_ee_request(resource_, ee_, (rpm_set_type)header->set, (kvp_eof(rxKvp_) ? NULL : rxKvp_), settling_time);

    if(settling_time)
    {
        uint64 now = time_service_now();
        if ((!allow_settling) || disable_settling)
        {
            while(settling_time)
                settling_time = resource_ee_settling_apply(resource_, ee_, settling_time);
            observed_settling = time_service_now() - now;
        }
        else if(settling_time <= now)
        {
            settling_time = resource_ee_settling_apply(resource_, ee_, settling_time);
        }
        else
        {
            observed_settling = settling_time - now;
        }
    }

    if(!settling_time)
    {
        writeResponse(header->msg_id, 0, RPM_MESSAGE_ERROR_NONE, RPM_REQUEST_SERVICE);
    }

    // Finish timing and record the observation.
    obs = estimator.completeObservation(obs);
    if ((!allow_settling) || disable_settling)
    {
        obs.time -= observed_settling;
    }

    if(applied)
    {
        resource_observe(resource_, theEstimator().currentOperatingPoint(), obs, observed_settling);
    }

    return settling_time;
}

void Handler::getNextNAS(void)
{
    RPMMessageHeaderV1 *v1_header;
    if(messageVersion_ == 0)
    {	    	    
        unsigned old_msg_size = messageHeader_->msg_size;
        messageHeader_ = (RPMMessageHeader *)((uint8 *)messageHeader_ + messageHeader_->msg_size +
                                          offsetof(RPMMessageHeader, msg_id));

        if ((uint8 *)messageHeader_ >= ((uint8 *)rxBuf_ + haveMessageLen_))
        {
            haveMessage_ = false;
            messageHeader_ = NULL;
            haveMessageLen_ = 0;
	    rxBufHeaderOffset_ = 0;
        }
        else
        {
            //Make sure all NAS messages in the given bundle use the same messaging protocol version	
            CORE_VERIFY(messageVersion_ == MESSAGING_UNPACK_VERSION(messageHeader_->msg_type));

	    //pointer to next data will be 1 header size + current message header offset
            //offset to the next kvp buffer is just + msg_size + two unsigned for the common msg_header not accounted for in msg_size
	    //rxBufHeaderOffset_ = ((((char *)messageHeader_ - (char*)rxBuf_) + sizeof(RPMMessageHeader))/sizeof(unsigned));
            rxBufHeaderOffset_ += (old_msg_size + sizeof(RPMCommandHeader))/sizeof(unsigned);
        }	    
    }	
    else if (messageVersion_ == 1)
    {
        //offset to the next kvp buffer is just + prior message data + one header
        rxBufHeaderOffset_ += (messageHeader_->data_len + sizeof(RPMMessageHeaderV1))/sizeof(unsigned);

	//rxBufHeaderOffset points to the next kvp_buffer. Back off the header size to get the next header 
        v1_header = (RPMMessageHeaderV1 *)((rxBuf_ + rxBufHeaderOffset_) - (sizeof(RPMMessageHeaderV1)/sizeof(unsigned)));

        if ((uint8 *)v1_header >= ((uint8 *)rxBuf_ + haveMessageLen_))
        {
            haveMessage_ = false;
            messageHeader_ = NULL;
            haveMessageLen_ = 0;
	    rxBufHeaderOffset_ = 0;
        }
        else
        {		
            //Make sure all NAS messages in the given bundle use the same messaging protocol version	
            CORE_VERIFY(messageVersion_ == v1_header->msg_header.version);    

            messageHeader_->msg_type      = v1_to_v0_service((rpm_v1_service_type)v1_header->msg_header.type);
            messageHeader_->msg_size      = v1_header->msg_header.size + (sizeof(RPMMessageHeader) - (sizeof(RPMMessageHeaderV1) + sizeof(unsigned)));
            messageHeader_->msg_id        = v1_header->msg_id;
            messageHeader_->set           = v1_header->request_details.set;
            messageHeader_->resource_type = v1_header->resource_type;
            messageHeader_->resource_id   = v1_header->request_details.resource_id;
            messageHeader_->data_len      = v1_header->request_details.data_len;
        }	
    }
}	

// Process from the queue until it is empty, or the next request is *not* a
// NAS request.  Returns true if completed successfully, or false if
// preempt becomes true or stop time is reached.
bool Handler::processNAS(volatile bool &preempt, uint64_t &stop_time)
{

    SWEVENT(RPM_NAS_START);
    while(!preempt && (time_service_now() < stop_time))
    {
        if(!haveMessage_)
        {
            glink_rpm_rx_poll(glinkPort_);
            if(!haveMessage_)
            {
                return true; // No messages to process   
            }		    
        }

        if(messageHeader_->set != RPM_NEXT_ACTIVE_SET)
            return true; // Found non-NAS message.

	//size validation is done in processHeader. In addition, this check is incorrect for V1 because 
	//V1 messages are expanded on receiving, so size might be > raw amount read
        //CORE_VERIFY (messageHeader_->msg_size <= haveMessageLen_);
        rpm_message_error_type v1_error;		    
        const char *error = processHeader(messageHeader_, &v1_error, (char *)(rxBuf_ + rxBufHeaderOffset_));
        if(error)
        {
            writeResponse(messageHeader_->msg_id, error, v1_error, RPM_REQUEST_SERVICE);
        }
        else if (preempt)
        {
            //loadMessage may have caused pre-emption from a soft transition command. Bail if that happened		
            return false;                        
        }		
        else
        {
            processMessage (preempt, stop_time, messageHeader_, false);
        }

        getNextNAS();
    }

    // Didn't hit a completion condition.
    return false;
}

