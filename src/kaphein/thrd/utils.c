#include "kaphein/ErrorCode.h"
#include "kaphein/thrd/internal.h"
#include "kaphein/thrd/utils.h"

int kapheinThrdSleep(
    int milliseconds
)
{
    int errorCode = kapheinErrorCodeNoError;
    
    if(milliseconds < 0) {
        milliseconds = 0;
    }
    
#if KAPHEIN_THREAD_MODEL != KAPHEIN_THREAD_MODEL_UNKNOWN
    #if defined(KAPHEIN_PLATFORM_WINDOWS)
        Sleep((DWORD)milliseconds);
    #elif defined(KAPHEIN_PLATFORM_UNIX) || defined(KAPHEIN_PLATFORM_LINUX)
        usleep((useconds_t)(milliseconds * 1000));
    #else
        errorCode = kapheinErrorCodeNotSupported;
    #endif
#else
    errorCode = kapheinErrorCodeNotSupported;
#endif

    return errorCode;
}
