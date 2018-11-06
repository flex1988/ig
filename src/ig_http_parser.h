#ifndef IG_HTTP_PARSER_H
#define IG_HTTP_PARSER_H

#include "http_parser.h"
#include <stdlib.h>
#include "uv.h"

int parse_url(http_parser* parser, const char* url, size_t length);
int parse_header_field(http_parser* parser, const char* at, size_t length);
int parse_header_value(http_parser* parser, const char* at, size_t length);
int parse_body(http_parser* parser, const char* at, size_t length);
int parse_message_begin(http_parser* parser);
int parse_message_complete(http_parser* parser);
int parse_headers_complete(http_parser* parser);

void message_clear(uv_write_t *req, int status);

#endif
