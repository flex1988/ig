#include <stdlib.h>
#include "/usr/lib/csv9.5.1/a6le/scheme.h"

#define ABNORMAL_EXIT ((void (*)(void))0)
#define CUSTOM_INIT ((void (*)(void))0)

int scheme_exec_script(char* script)
{
    Sscheme_init(ABNORMAL_EXIT);
    Sbuild_heap("scheme", CUSTOM_INIT);
    return Sscheme_script(script, 0, NULL);
}
