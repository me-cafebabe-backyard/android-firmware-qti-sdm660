#include "npa_dump.h"
#include "npa_internal.h"
#include "time_service.h"
#include "CoreVerify.h"

#define NPA_DUMP_FORMAT_VERSION    0x1
#define NPA_UNKNOWN_KEY            0x4e574b55 /* UKNWN */


typedef struct
{
    uint32 version;         /* NPA dump format version */
    uint32 timestamp[2];    /* use uint32[2] instead of uint64 to avoid padding */
    uint32 size;            /* NPA dump size in bytes */
} npa_dump_header_t;

typedef struct
{
    uint32 unit;
    uint32 active_max;
    uint32 active_state;
    uint32 request_state;
} npa_dump_resource_state_t;

typedef struct
{
    uint32 name;
    uint32 type;
    uint32 state;
} npa_dump_resource_client_t;

typedef struct
{
    const char *str;
    uint32      key;
} npa_dump_str_to_key_t;

typedef struct
{
    npa_client_type type;
    uint32          key;
} npa_dump_client_type_to_key_t;


static npa_dump_str_to_key_t npa_dump_str_to_key_map[] =
{
    {"APSS"               , 0x53535041}, /* APSS */
    {"MPSS"               , 0x5353504d}, /* MPSS */
    {"LPASS"              , 0x5341504c}, /* LPAS */
    {"SSC"                , 0x00435353}, /* SSC */
    {"CDSP"               , 0x50534443}, /* CDSP */
    {"WCSS"               , 0x53534357}, /* WCSS */
    {"TZ"                 , 0x00005a54}, /* TZ */
    {"SPSS"               , 0x53535053}, /* SPSS */
    {"ClockRPM"           , 0x004b4c43}, /* CLK */
    {"ICB Driver"         , 0x00424349}, /* ICB */
    {"ICB Latency Driver" , 0x4c424349}, /* ICBL */
    {"debugger"           , 0x47554244}, /* DBUG */
    {"qdssrpm"            , 0x53534451}, /* QDSS */
    {"rpm_init"           , 0x494e4952}, /* RINI */
    {"rpm_internal"       , 0x544e4952}, /* RINT */
    {"rpm svs"            , 0x53565352}, /* RSVS */
    {"lpddr"              , 0x5244444c}, /* LDDR */
    {"ddr"                , 0x00524444}, /* DDR */
    {"KHz"                , 0x007a484b}, /* KHz */
    {"Enable"             , 0x62616e45}, /* Enab */
    {"STATE"              , 0x74617453}, /* Stat */
};

static npa_dump_client_type_to_key_t npa_dump_client_type_to_key_map[] =
{
    {NPA_CLIENT_RESERVED1          , 0x31565352}, /* RSV1 */
    {NPA_CLIENT_RESERVED2          , 0x32565352}, /* RSV2 */
    {NPA_CLIENT_CUSTOM1            , 0x31545343}, /* CST1 */
    {NPA_CLIENT_CUSTOM2            , 0x32545343}, /* CST2 */
    {NPA_CLIENT_CUSTOM3            , 0x33545343}, /* CST3 */
    {NPA_CLIENT_CUSTOM4            , 0x34545343}, /* CST4 */
    {NPA_CLIENT_REQUIRED           , 0x44514552}, /* REQD */
    {NPA_CLIENT_ISOCHRONOUS        , 0x434f5349}, /* ISOC */
    {NPA_CLIENT_IMPULSE            , 0x4c504d49}, /* IMPL */
    {NPA_CLIENT_LIMIT_MAX          , 0x58414d4c}, /* LMAX */
    {NPA_CLIENT_VECTOR             , 0x54434556}, /* VECT */
    {NPA_CLIENT_SUPPRESSIBLE       , 0x50505553}, /* SUPP */
    {NPA_CLIENT_SUPPRESSIBLE_VECTOR, 0x56505553}, /* SUPV */
};


/*******************************************************************************
 *
 * npa_dump_advance_buffer
 *
 */
static void npa_dump_advance_buffer(char** buffer, uint32 *buf_size, uint32 bytes)
{
    *buffer   += bytes;
    *buf_size -= bytes;
}

/*******************************************************************************
 *
 * npa_dump_write_string
 *
 */
static void npa_dump_write_string(char** dst_buf, uint32* dst_buf_size, const char* src_buf, uint32 src_buf_size)
{
    uint32 word_aligned_size = (src_buf_size + 3) & ~3;

    if(src_buf_size == word_aligned_size)
    {
        word_aligned_size += sizeof(uint32);
    }

    if(*dst_buf_size >= word_aligned_size)
    {
        memset(*dst_buf, 0, word_aligned_size);
        memcpy(*dst_buf, src_buf, src_buf_size);

        npa_dump_advance_buffer(dst_buf, dst_buf_size, word_aligned_size);
    }
}

/*******************************************************************************
 *
 * npa_dump_write_null
 *
 */
static void npa_dump_write_null(char** buffer, uint32* buf_size)
{
    if(*buf_size >= sizeof(uint32))
    {
        *((uint32*)*buffer) = 0;

        npa_dump_advance_buffer(buffer, buf_size, sizeof(uint32));
    }
}

/*******************************************************************************
 *
 * npa_dump_write_header
 *
 */
static void npa_dump_write_header(char* buffer, uint32 dump_size)
{
    npa_dump_header_t *header = (npa_dump_header_t*)buffer;

    header->version             = NPA_DUMP_FORMAT_VERSION;
    header->size                = dump_size;
    *(uint64*)header->timestamp = time_service_now();
}

/*******************************************************************************
 *
 * npa_dump_client_type_to_key
 *
 */
static uint32 npa_dump_client_type_to_key(npa_client_type type)
{
    uint32 key = NPA_UNKNOWN_KEY;
    uint32 i;

    for(i = 0; i < sizeof(npa_dump_client_type_to_key_map)/sizeof(npa_dump_client_type_to_key_t); i++)
    {
        if(type == npa_dump_client_type_to_key_map[i].type)
        {
            key = npa_dump_client_type_to_key_map[i].key;
            break;
        }
    }

    return key;
}

/*******************************************************************************
 *
 * npa_dump_string_to_key
 *
 */
static uint32 npa_dump_string_to_key(const char* str)
{
    uint32 key = NPA_UNKNOWN_KEY;
    uint32 i;

    for(i = 0; i < sizeof(npa_dump_str_to_key_map)/sizeof(npa_dump_str_to_key_t); i++)
    {
        if(0 == strcmp(npa_dump_str_to_key_map[i].str, str))
        {
            key = npa_dump_str_to_key_map[i].key;
            break;
        }
    }

    return key;
}

/*******************************************************************************
 *
 * npa_dump_resource_state
 *
 */
static void npa_dump_resource_state(char** buffer, uint32* buf_size, npa_resource *resource)
{
    npa_resource_definition *definition = resource->definition;
    npa_dump_resource_state_t *ptr;

    CORE_VERIFY((*buf_size % 4) == 0);

    npa_dump_write_string(buffer, buf_size, definition->name, strlen(definition->name));

    if(*buf_size >= sizeof(npa_dump_resource_state_t))
    {
        ptr = (npa_dump_resource_state_t*)*buffer;

        ptr->unit          = npa_dump_string_to_key(definition->units);
        ptr->active_max    = resource->active_max;
        ptr->active_state  = resource->active_state;
        ptr->request_state = resource->request_state;

        npa_dump_advance_buffer(buffer, buf_size, sizeof(npa_dump_resource_state_t));
    }
}


/*******************************************************************************
 *
 * npa_dump_resource_clients
 *
 */
static void npa_dump_resource_clients(char** buffer, uint32* buf_size, npa_resource *resource)
{
    npa_client *client = resource->clients;
    npa_dump_resource_client_t *ptr;

    CORE_VERIFY((*buf_size % 4) == 0);

    while(client)
    {
        if(*buf_size < sizeof(npa_dump_resource_client_t))
        {
            break;
        }

        ptr = (npa_dump_resource_client_t*)*buffer;

        ptr->name  = npa_dump_string_to_key(client->name);
        ptr->type  = npa_dump_client_type_to_key(client->type);
        ptr->state = client->work[client->index].state;

        npa_dump_advance_buffer(buffer, buf_size, sizeof(npa_dump_resource_client_t));

        client = client->next;
    }

    npa_dump_write_null(buffer, buf_size);
}

/*******************************************************************************
 *
 * npa_dump_resource
 *
 */
static void npa_dump_resource(char** buffer, uint32* buf_size, npa_resource *resource)
{
    CORE_VERIFY(resource->node_lock);

    DALSYS_SyncEnter(resource->node_lock);

    npa_dump_resource_state(buffer, buf_size, resource);
    npa_dump_resource_clients(buffer, buf_size, resource);

    DALSYS_SyncLeave(resource->node_lock);
}


/*******************************************************************************
 *
 * npa_dump_link
 *
 */
static void npa_dump_link(char** buffer, uint32* buf_size, npa_link *link)
{
    CORE_VERIFY_PTR(link->resource->definition);
    CORE_VERIFY(0 == strncmp(link->name, link->resource->definition->name, NPA_MAX_STR_LEN+1));

    npa_dump_resource(buffer, buf_size, link->resource);
}

/*******************************************************************************
 *
 * npa_dump
 *
 */
void npa_dump(char* buffer, uint32 buf_size)
{
    npa_link *link;
    char* buf_ptr = buffer;

    CORE_VERIFY_PTR(buffer);
    CORE_VERIFY(buf_size >= sizeof(npa_dump_header_t));

    npa_dump_advance_buffer(&buf_ptr, &buf_size, sizeof(npa_dump_header_t));

    DALSYS_SyncEnter(npa.graph_lock);

    for(link = npa.resources; link; link = link->next)
    {
        npa_dump_link(&buf_ptr, &buf_size, link);
    }

    DALSYS_SyncLeave(npa.graph_lock);

    npa_dump_write_null(&buf_ptr, &buf_size);
    npa_dump_write_header(buffer, buf_ptr - buffer - sizeof(npa_dump_header_t));
}

