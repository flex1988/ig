#ifndef IG_REQUEST_H
#define IG_REQUEST_H
#include "uv.h"
#include <stdbool.h>
#include <stdint.h>

#define FIELD 0
#define VALUE 1
#define MAX_FIELDS 13
#define MAX_ELEMENT_SIZE 2048
#define MAX_CHUNKS 16

typedef struct
{
    char response_status[MAX_ELEMENT_SIZE];
    char request_path[MAX_ELEMENT_SIZE];
    char request_url[MAX_ELEMENT_SIZE];
    char fragment[MAX_ELEMENT_SIZE];
    char query_string[MAX_ELEMENT_SIZE];
    char body[MAX_ELEMENT_SIZE];
    uint32_t body_size;
    char fields[MAX_FIELDS][MAX_ELEMENT_SIZE];
    char values[MAX_FIELDS][MAX_ELEMENT_SIZE];
    int num_headers;
    int last_header_element;
    int status;
    int method;
    int status_code;
    bool message_begin : 1;
    bool message_complete : 1;
    bool parse_error : 1;
} http_request_t;

void core_recv(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);
#endif
