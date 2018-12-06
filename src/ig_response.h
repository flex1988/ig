#ifndef IG_RESPONSE_H
#define IG_RESPONSE_H
#include "uv.h"

void on_close(uv_handle_t* handle);

typedef struct
{
    char* body;
    uint32_t body_size;
} http_response_t;
#endif
