#include "ig_http_parser.h"
#include "ig_connection.h"
#include "http_parser.h"
#include <string.h>
#include "uv.h"

int parse_url(http_parser* parser, const char* url, size_t length)
{
    printf("parse_url\n");
    connection_t* conn = (connection_t*)parser->data;
    struct http_parser_url u;
    int ret = http_parser_parse_url(url, length, 0, &u);
    if (ret)
    {
        printf("parse url error\n");
        return ret;
    }
    else
    {
        if(u.field_set & (1<<UF_PATH))
        {
            const char* data = url + u.field_data[UF_PATH].off;
            //conn->path = 
        }
        else
        {
            printf("parse url error\n");
            return -1;
        }
    }
    return 0;
}

int parse_header_field(http_parser* parser, const char* at, size_t length)
{
    printf("parse header field\n");
    return 0;
}

int parse_header_value(http_parser* parser, const char* at, size_t length)
{
    printf("parse header field\n");
    return 0;
}

int parse_body(http_parser* parser, const char* at, size_t length)
{
    printf("body: %s\n", at);
    return 0;
}

int parse_message_begin(http_parser* parser)
{
    printf("parse_message_begin\n");
    return 0;
}

void message_clear(uv_write_t* req, int status)
{
    if (status == -1)
    {
        printf("write error\n");
    }
    char* base = (char*)req->data;
    free(base);
    free(req);
}

int parse_message_complete(http_parser* parser)
{
    printf("parse_message_complete\n");
    connection_t* conn = (connection_t*)parser->data;
    uv_write_t* req = malloc(sizeof(uv_write_t));
    uv_buf_t res;
    char* msg =  "<html><body>hello world!</body></html>\n";
    size_t len = strlen(msg)+1;
    res.base = malloc(len);
    memcpy(res.base, msg, len);
    res.len = len;
    req->data = res.base;
    uv_write(req, (uv_stream_t*)&conn->handle, &res, 1, message_clear);
    return 0;
}

int parse_headers_complete(http_parser* parser)
{
    printf("parse_headers_complete\n");
    return 0;
}
