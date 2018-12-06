#ifndef IG_CONNECTION_H
#define IG_CONNECTION_H

#include "ig_request.h"
#include "uv.h"
#include "http_parser.h"

void connection_handler(uv_stream_t* socket, int status);
void alloc_buffer(uv_handle_t* handle, size_t bufSize, uv_buf_t* buf);
void connection_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);

typedef struct
{
    uv_tcp_t handle;
    http_parser parser;
    http_request_t request;
} connection_t;

#endif
