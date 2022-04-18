/*===========================================================================

  Copyright (c) 2013-2015 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include <alloca.h>

#include "coredump.h"
#include "rpm_sched.h"

#include "rpm_config.h"
#include "rpmserver_internal.h"
#include "rpm_spm_handshake.h"
#include "CoreVerify.h"
#include "Chipinfo.h"
#include "rpm_resources.h"
#include "DALSys.h"

extern void rpm_test_resource_init();

void rpm_register_resource
(
    rpm_resource_type resource,
    unsigned          num_supported,
    unsigned          inrep_size,
    rpm_translate_cb  xlate_cb,
    rpm_apply_cb      apply_cb,
    void             *cb_data
)
{
    unsigned *ids = (unsigned *)alloca(num_supported * sizeof(unsigned));

    for(unsigned i = 0; i < num_supported; ++i)
        ids[i] = i;

    rpm_register_named_resource(resource, num_supported, ids, inrep_size, xlate_cb, apply_cb, cb_data);
}

static int rpm_find_resource_class(rpm_resource_type resource, unsigned inrep_size, rpm_translate_cb xlate_cb, rpm_apply_cb apply_cb, void *cb_data)
{
    for(unsigned i = 0; i < rpm->supported_classes; i++)
    {
        const ResourceClassData *rc = &rpm->classes[i];
        if((rc->type       == resource)   &&
           (rc->inrep_size == inrep_size) &&
           (rc->xlate      == xlate_cb)   &&
           (rc->apply      == apply_cb)   &&
           (rc->cb_data    == cb_data))
        {
            return i;
        }
    }

    return -1;
}

static int rpm_create_resource_class(rpm_resource_type resource, unsigned inrep_size, rpm_translate_cb xlate_cb, rpm_apply_cb apply_cb, void *cb_data)
{
    int class_idx = -1;
    for(unsigned i = 0; i < rpm->supported_classes; ++i)
    {
        // Check if this is a valid slot to drop a new class, if we need to.
        if(class_idx < 0 && !rpm->classes[i].type)
        {
            // Found a free slot for this class to be created.
            class_idx = i;
            break;
        }
    }

    // If we've run out of place to put new classes, we'll need to increase the
    // number of supported classes in the rpmserver configuration data.
    CORE_VERIFY(class_idx >= 0);

    ResourceClassData *rc = &(rpm->classes[class_idx]);
    rc->type              = resource;
    rc->inrep_size        = inrep_size;
    rc->xlate             = xlate_cb;
    rc->apply             = apply_cb;
    rc->cb_data           = cb_data;
    rc->internal_types    = 0;
    return class_idx;
}

void rpm_register_named_resource
(
    rpm_resource_type resource,
    unsigned          num_supported,
    unsigned const   *ids,
    unsigned          inrep_size,
    rpm_translate_cb  xlate_cb,
    rpm_apply_cb      apply_cb,
    void             *cb_data
)
{
    // Check for duplicate re-registration of resources and skip it if so.
    if(rpm_find_resource_class(resource, inrep_size, xlate_cb, apply_cb, cb_data) >= 0)
        return;

    // Create a resource class for these resources.
    int class_idx = rpm_create_resource_class(resource, inrep_size, xlate_cb, apply_cb, cb_data);
    if(class_idx < 0)
        return;

    for(unsigned i = 0; i < num_supported; ++i)
    {
        // Check to see if this resource already exists - if so, we have a problem (should not have duplicates).
        ResourceData *r = rpmserver_lookup_resource(resource, ids[i]);

        CORE_VERIFY(!r);
        
        r = rpmserver_insert_resource(resource, ids[i]);
        resource_init(r, class_idx, ids[i]);
    }
}

void rpm_send_init_proxy_vote(rpm_resource_type resource, unsigned id, unsigned ee, kvp_t *data)
{
    uint64 settling_time = 0;
    CORE_VERIFY(ee < rpm->num_ees);

    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    resource_ee_request(r, ee, RPM_ACTIVE_SET, data, settling_time);
}

void rpm_send_init_sleep_proxy_vote(rpm_resource_type resource, unsigned id, unsigned ee, kvp_t *data)
{
    uint64 settling_time = 0;
    CORE_VERIFY(ee < rpm->num_ees);

    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    resource_ee_request(r, ee, RPM_SLEEP_SET, data, settling_time);
}

unsigned rpm_get_num_ees()
{
    return rpm->num_ees;
}

unsigned rpm_get_num_clients(const struct ResourceData* resource_handle)
{
    CORE_VERIFY(resource_handle);
    return resource_num_clients(resource_handle);
}

void rpm_get_current_request(const struct ResourceData* resource_handle, unsigned client, unsigned *client_type, const void **request)
{
    CORE_VERIFY(resource_handle);
    resource_get_request(resource_handle, client, client_type, request);
}

void rpm_get_aggregated_request_buffer(rpm_resource_type resource, unsigned id, const void **request)
{
    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    *request = r->current_state;
}

void rpm_register_internal_client_type
(
    rpm_resource_type resource,
    unsigned          id,
    unsigned          client_type,
    unsigned          inrep_size
)
{
    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);

    ResourceClassData *rc = &(rpm->classes[r->class_idx]);
    CORE_VERIFY(rc);

    resource_class_add_client_type(rc, client_type, inrep_size);
}

unsigned rpm_create_client(rpm_resource_type resource, unsigned id, unsigned client_type)
{
    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    return resource_create_client(r, client_type);
}

void rpm_issue_request(rpm_resource_type resource, unsigned id, unsigned client, unsigned size, void *data)
{
    uint64 settling_time = 0;
    ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    do
    {
      settling_time = resource_client_request(r, client, size, data, settling_time);
    } while(settling_time);
}

const struct ResourceData* rpm_get_resource_handle(rpm_resource_type resource, unsigned id)
{
    const ResourceData *r = rpmserver_lookup_resource(resource, id);
    CORE_VERIFY(r);
    return r;
}

rpmserver_service_t *rpm_alt_service_list = 0;

void rpmserver_register_handler(rpm_service_type service, rpmserver_service_cb cb, void *context)
{
    INTLOCK();

    rpmserver_service_t *s = rpm_alt_service_list;

    for(; s; s = s->next)
    {
        CORE_VERIFY(s->service_id != service);
    }

    s = new rpmserver_service_t;
    s->next       = rpm_alt_service_list;
    s->service_id = service;
    s->cb         = cb;
    s->context    = context;
    rpm_alt_service_list = s;

    INTFREE();
}

__attribute__((section("rpmserver_cram_reclaim_pool")))
void rpmserver_init()
{
    rpm_core_dump.rpmserver_state = rpm;
    rpm_core_dump.scheduler_state = &theSchedule();

    for(unsigned ee = 0; ee < rpm->num_ees; ++ee)
    {
        EEData *ee_data = &rpm->ees[ee];
        Handler *h = NULL;

        if(ee_data->ee_buflen > 0)
        {
            h = new Handler(ee, ee_data->ee_buflen, ee_data->priority * 2);
            h->init();
        }

        ee_data->handler = h;

        // no changer for any EE that doesn't have a dedicated core
        if (ee_data->spm.numCores == 0)
        {
          ee_data->changer = NULL;
        }
        else
        {
          SetChanger *c = new SetChanger(ee, h, ee_data->priority * 2 + 1);
          ee_data->changer = c;
          ee_data->stats = message_ram_master_stats (ee);
        }
    }

    //memory optimization: allocate a common tx buffer of 128 bytes (instead of per handler)
    DALSYS_Malloc (128, (void **)&(rpm->tx_buf));

    rpm_spm_init();

    rpm_test_resource_init();
}

