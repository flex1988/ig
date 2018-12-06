#include "stdio.h"
#include "uv.h"
#include "ig_connection.h"
#include "ig_http_parser.h"

uv_loop_t* UV;
http_parser_settings parser_settings;
static uv_tcp_t server;
static int DEFAULT_PORT = 8081;

#define MAX_WRITE_HANDLES 1024

int ig_scheme_run(char* ip, int port)
{
    int ret;
    parser_settings.on_url = parse_url;
    parser_settings.on_message_begin = parse_message_begin;
    parser_settings.on_headers_complete = parse_headers_complete;
    parser_settings.on_message_complete = parse_message_complete;

    parser_settings.on_header_field = parse_header_field;
    parser_settings.on_header_value = parse_header_value;
    parser_settings.on_body = parse_body;

    UV = uv_default_loop();
    if (UV == NULL)
    {
        printf("init default loop error\n");
        return -1;
    }
    ret = uv_tcp_init(UV, &server);
    struct sockaddr_in address;
    ret = uv_ip4_addr(ip, port, &address);
    ret = uv_tcp_bind(&server, (const struct sockaddr*)&address, 0);
    ret = uv_listen((uv_stream_t*)&server, MAX_WRITE_HANDLES, connection_handler);
    if (ret != 0)
    {
        printf("Add listener failed: %s\n",uv_strerror(ret));
        return -1;
    }
    printf("Listening on port %d\n", port);
    uv_run(UV, UV_RUN_DEFAULT);
    printf("Server exiting\n");
    return 0;

}

typedef char* (*ig_handle_t)(const char* request_header, const char* path_info, const char* payload);

int ig_scheme_set(ig_handle_t req, ig_handle_t res)
{
    printf("ig_scheme_set\n");
    return 0;
}

char* ig_scheme_response(int status, char* type, char* path, char* query)
{
    return "hello world!";
}

int main()
{
    int ret;
    parser_settings.on_message_begin = parse_message_begin;
    parser_settings.on_header_field = parse_header_field;
    parser_settings.on_header_value = parse_header_value;
    parser_settings.on_url = parse_url;
    parser_settings.on_headers_complete = parse_headers_complete;
    parser_settings.on_body = parse_body;
    parser_settings.on_message_complete = parse_message_complete;

    UV = uv_default_loop();
    if (UV == NULL)
    {
        printf("init default loop error\n");
        return -1;
    }
    ret = uv_tcp_init(UV, &server);
    struct sockaddr_in address;
    ret = uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &address);
    ret = uv_tcp_bind(&server, (const struct sockaddr*)&address, 0);
    ret = uv_listen((uv_stream_t*)&server, MAX_WRITE_HANDLES, connection_handler);
    if (ret != 0)
    {
        printf("Add listener failed: %s\n",uv_strerror(ret));
        return -1;
    }
    printf("Listening on port %d\n", DEFAULT_PORT);
    uv_run(UV, UV_RUN_DEFAULT);
    printf("Server exiting\n");
    return 0;
}
