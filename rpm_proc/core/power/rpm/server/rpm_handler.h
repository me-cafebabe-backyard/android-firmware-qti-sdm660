/*===========================================================================

  rpm_handler.h - objects for incoming request handling

  Copyright (c) 2012 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#ifndef RPM_HANDLER_H
#define RPM_HANDLER_H

#include <stdint.h>

#include "rpm_task.h"
#include "rpm_resources.h"
#include "kvp.h"
#include "glink.h"

//number of resources per master that are allowed to settle at a given time
#define NUM_SETTLING_CONTEXTS 2

//V1 Message header unpack macros
//
//  V0 protocol                ver  service
//    unsigned msg_header -> 0x00   000000
//
//  V1 protocol                ver  type  size
//    unsigned msg_header -> 0x01   00    0000
#define MESSAGING_UNPACK_VERSION(x) (x >> 24)

typedef struct
{
    unsigned short size    :16;
    unsigned short type    :8;
    unsigned short version :8;
} RPMRequestHeaderV1;

typedef struct
{
    unsigned short data_len   :16;
    unsigned short resource_id :12;
    unsigned short set        :4;
} RPMRequestDetailsV1;

typedef struct
{
    unsigned msg_type;
    unsigned msg_size;
    unsigned msg_id;
    unsigned set;
    unsigned resource_type;
    unsigned resource_id;
    unsigned data_len;
} RPMMessageHeader;

typedef struct
{
    unsigned msg_type;
    unsigned msg_size;
} RPMCommandHeader;

typedef struct
{
    RPMRequestHeaderV1  msg_header;
    unsigned            msg_id;
    unsigned            resource_type;
    RPMRequestDetailsV1 request_details;
} RPMMessageHeaderV1;

typedef struct
{
    RPMRequestHeaderV1 msg_header;
    unsigned           msg_id; 
} RPMAckPacketV1;

typedef struct
{
    RPMRequestHeaderV1     msg_header;
    unsigned               msg_id; 
    rpm_message_error_type msg_err; 
} RPMNackPacketV1;


typedef struct
{
    ResourceData     *r;
    uint32_t         msg_id;
    uint64_t         settling_time;
} SettlingInfo;

class Handler : public Task
{
public:
  Handler(unsigned ee, unsigned rxbuflen, uint8_t priority = 127);
    virtual ~Handler();

    void init();


    void requeue_settling(void);

    virtual uint64_t get_length() const;

    virtual bool hasImmediateWork() const;

    // Process from the queue until it is empty, or the next request is *not* a
    // NAS request.  Returns true if completed successfully, or false if
    // preempt becomes true or stop time is reached.
    bool processNAS(volatile bool &preempt, uint64_t &stop_time);

    void writeResponse(unsigned data, const char *error, rpm_message_error_type, rpm_service_type service);

    uint32_t getMsgID(void) { return (messageHeader_) ? messageHeader_->msg_id : 0; };

    void rpm_glink_enqueue(glink_handle_type port, void *unused_open_data,
                         void *buffer, size_t size, size_t intent_used, 
                         glink_buffer_provider_fn vprovider, glink_buffer_provider_fn pprovider);

    void portOpen(void);

    glink_handle_type glinkPort_;
    glink_link_handle_type glinkLink_;

protected:
    // Prepares, dispatches, and finalizes the request handling.
    virtual void execute_until(volatile bool &preempt, uint64_t stop_time);

private:
    enum execution_state
    {
        IDLE,
        DISPATCH,
        SETTLING,
        CLEANUP,
    };

    const char *processHeader(RPMMessageHeader *header, rpm_message_error_type *v1_error, char *data);
    void handleAlternateServiceMessage(unsigned service, void *data, unsigned length);
    boolean register_settling_slot(unsigned msg_id, uint64_t settling_time);

    void getNextNAS(void);
    bool loadMessageV0(unsigned msg_type);
    bool loadMessageV1(RPMMessageHeaderV1 *msg_header);
    bool loadMessage();
    uint64 processMessage (volatile bool &preempt, uint64_t &stop_time, RPMMessageHeader *header, bool allow_settling);
    void processCommand(RPMCommandHeader *header, char *data);

    unsigned         ee_;

    bool             haveMessage_;
    bool             isIdle_;

    uint32_t         haveMessageLen_; // in bytes
    uint32_t        *rxBuf_;
    unsigned         rxBufLen_; // in bytes
    RPMMessageHeader *messageHeader_; // points to the next message to process
    RPMMessageHeader messageHeaderV1_; // points to the next message to process
    unsigned         messageVersion_; // indicates the protocol used for this message
    uint32_t         rxBufHeaderOffset_; // offset in rxBuf_ to get to the kvp buffer
    RPMCommandHeader *commandHeader_; // points to the next command to process
    kvp_t           *rxKvp_;
    const char      *error_;
    ResourceData    *resource_;

    kvp_t           *txKvp_;

    execution_state  state_;
    bool             isHandlerSettling_;
    bool             isHandlerDispatching_;

    SettlingInfo     settlingMsg_[NUM_SETTLING_CONTEXTS];

    // Profiling data.
    uint64_t handlerStart_;
    uint64_t handlerEnd_;
    uint32_t immediateLatencyExceeded_;
};

#endif // RPM_HANDLER_H

