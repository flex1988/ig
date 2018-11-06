#include "ig_request.h"
#include "ig_response.h"
#include "ig_connection.h"
#include "uv.h"
#include <stdlib.h>
#include <string.h>

extern http_parser_settings parser_settings;

void core_recv(uv_stream_t* socket, ssize_t nread, const uv_buf_t* buf)
{
    ssize_t parsed;
    connection_t* conn = socket->data;

    if (nread >= 0)
    {
        parsed = http_parser_execute(&conn->parser, &parser_settings, buf->base, nread);
        if (parsed < nread)
        {
            uv_close((uv_handle_t*)&conn->handle, on_close);
        }
    }
    else
    {
        uv_close((uv_handle_t*)&conn->handle, on_close);
    }
}
