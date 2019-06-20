#include "kaphein/def.h"
#if !defined(KAPHEIN_x_PORTABLE_C_STRING_FUNCTIONS)
    #include <string.h>
#endif
#include "kaphein/ErrorCode.h"
#include "kaphein/internal.h"

size_t kapheinStrlen(
    const char *str
)
{
#if !defined(KAPHEIN_x_PORTABLE_C_STRING_FUNCTIONS)
    return (str != NULL ? strlen(str) : 0);
#else
    size_t c = 0;

    if(str != NULL) {
        for(; *str != '\0'; ++c, ++str);
    }

    return c;
#endif
}

int kapheinMemcpyS(
    void *dest
    , int destSize
    , const void *src
    , int count
)
{
    int errorCode = kapheinErrorCodeNoError;
    
    if(dest == NULL || src == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(count < 0 || destSize < count) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        #if !defined(KAPHEIN_x_PORTABLE_C_STRING_FUNCTIONS)
            memcpy(dest, src, count);
        #else
            char *d = (char *)dest;
            const char *s = (const char *)src;

            while(count > 0) {
                --count;
                *d++ = *s++;
            }
        #endif
    }

    return errorCode;
}

int kapheinMemsetS(
    void *dest
    , int destSize
    , int value
    , int count
)
{
    int errorCode = kapheinErrorCodeNoError;

    if(dest == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(count < 0 || destSize < count) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
    #if !defined(KAPHEIN_x_PORTABLE_C_STRING_FUNCTIONS)
        memset(dest, value, count);
    #else
        const unsigned char c = (unsigned char)value;

        while(count > 0) {
            --count;
            *dest++ = c;
        }
    #endif
    }

    return errorCode;
}
