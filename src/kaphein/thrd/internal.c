#include "kaphein/def.h"
#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
    #include <time.h>
    #include "kaphein/ErrorCode.h"
#endif
#include "kaphein/thrd/internal.h"

#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
int kapheinThrdMillisecondsToTimespec(
    int milliseconds
    , struct timespec *tsOut
)
{
    struct timespec ts;
    time_t restMs;

    int errorCode = kapheinErrorCodeNoError;
    
    if(tsOut == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        ts.tv_sec = milliseconds / 1000;
        restMs = milliseconds - (ts.tv_sec * 1000);
        ts.tv_nsec = (long)(restMs > 0 ? restMs * 1000000 : 0);
    }
    
    return errorCode;
}
#endif

typedef int kapheinSuppressEmptyFileWarning;
