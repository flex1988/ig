#include "ig_connection.h"
#include "ig_request.h"
#include "uv.h"
#include <stdlib.h>
#include <string.h>

extern uv_loop_t* UV;

void connection_handler(uv_stream_t* server, int status)
{
    if (status == -1)
        return;
    connection_t* conn = malloc(sizeof(connection_t));   
    uv_tcp_init(UV, &conn->handle);
    http_parser_init(&conn->parser, HTTP_REQUEST);
    conn->handle.data = conn;
    conn->parser.data = conn;
    if (uv_accept(server, (uv_stream_t*)&conn->handle) == 0)
    {
        uv_read_start((uv_stream_t*)&conn->handle, alloc_buffer, core_recv);
    }
    else
    {
        uv_close((uv_handle_t*)&conn->handle, NULL);
    }
}

void alloc_buffer(uv_handle_t* handle, size_t bufSize, uv_buf_t* buf)
{
    *buf = uv_buf_init((char*)malloc(bufSize), bufSize);
}



