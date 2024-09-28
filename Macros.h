#ifndef _MACROS_
#define _MACROS_

#include <stdio.h>
#include <stdlib.h>

#define CHECK_NULL(ptr, return_val) \
    if ((ptr) == NULL) { \
        return return_val; \
    }

#define ALLOCATE(type, num) (type*) malloc((num) * sizeof(type))

#define SAFE_FREE(ptr) do { if(ptr) { free(ptr); (ptr) = NULL; } } while(0)

#endif