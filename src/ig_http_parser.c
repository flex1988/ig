#include <string.h>
#include <stdlib.h>
#include "ig_scheme.h"
#include "ig_http_parser.h"
#include "ig_connection.h"
#include "ig_response.h"
#include "http_parser.h"
#include "uv.h"

int parse_url(http_parser* parser, const char* p, size_t length)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    /*request->url = malloc(length + 1);*/
    strncat(request->request_url, p, length);
    return 0;
}

int parse_request_path(http_parser* parser, const char* p, size_t length)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    /*request->request_path = malloc(length + 1);*/
    strncat(request->request_path, p, length);
    return 0;
}

int parse_header_field(http_parser* parser, const char* p, size_t length)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    if (request->last_header_element != FIELD)
        request->num_headers++;

    /*request->fields[request->num_headers - 1] = malloc(length + 1);*/
    strncat(request->fields[request->num_headers - 1], p, length);

    request->last_header_element = FIELD;

    return 0;
}

int parse_header_value(http_parser* parser, const char* p, size_t length)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    /*request->values[request->num_headers - 1] = malloc(length + 1);*/
    strncat(request->values[request->num_headers - 1], p, length);
    request->last_header_element = VALUE;

    return 0;
}

int parse_body(http_parser* parser, const char* p, size_t length)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    /*request->body = malloc(length + 1);*/
    strncat(request->body, p, length);
    request->body_size += length;
    return 0;
}

int parse_message_begin(http_parser* parser)
{
    connection_t* conn = (connection_t*)parser->data;
    conn->request.message_begin = true;
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

void dump_http_request(http_request_t* request)
{
    printf("dump http request:\n");
    printf("response_status %s\n", request->response_status);
    printf("request_path %s\n", request->request_path);
    printf("request_url %s\n", request->request_url);
    printf("fragment %s\n", request->fragment);
    printf("query_string %s\n", request->query_string);
    printf("body %s\n", request->body);
    printf("body size %u\n", request->body_size);
    printf("status %d\n", request->status);
    printf("method %d\n", request->method);
}

int parse_message_complete(http_parser* parser)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    request->message_complete = true;
    request->method = parser->method;
    request->status_code = parser->status_code;
    dump_http_request(request);

    http_response_t response;
    response.body = NULL;
    response.body_size = 0;

    scheme_handler(request, &response);

    uv_write_t* req = malloc(sizeof(uv_write_t));
    uv_buf_t res;
    res.base = malloc(response.body_size);
    memcpy(res.base, response.body, response.body_size);
    res.len = response.body_size;
    req->data = res.base;
    // free response.body;
    uv_write(req, (uv_stream_t*)&conn->handle, &res, 1, message_clear);
    return 0;
}

int parse_headers_complete(http_parser* parser)
{
    connection_t* conn = (connection_t*)parser->data;
    http_request_t* request = &conn->request;
    request->method = parser->method;
    request->status_code = parser->status_code;
    return 0;
}
