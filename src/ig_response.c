#include "ig_response.h"
#include "ig_connection.h"
#include <stdlib.h>

void on_close(uv_handle_t* handle)
{
    connection_t* conn = (connection_t*)handle->data;
    free(conn);
}

