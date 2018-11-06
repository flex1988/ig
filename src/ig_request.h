#ifndef IG_REQUEST_H
#include "uv.h"

void core_recv(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf);
#endif
