#include <stdlib.h>
#include "kaphein/mem/defAlloc.h"

void *
kaphein_mem_defaultAllocate(
    kaphein_SSize memorySize
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    void * memory = KAPHEIN_NULL;

    KAPHEIN_x_UNUSED_PARAMETER(hint)

    if(memorySize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        memory = malloc(memorySize);
        if(memory == NULL) {
            memory = KAPHEIN_NULL;
            errorCode = kapheinErrorCodeMemoryAllocationFailed;
        }
    }

    if(errorCodeOut != KAPHEIN_NULL) {
        *errorCodeOut = errorCode;
    }

    return memory;
}

enum kaphein_ErrorCode
kaphein_mem_defaultDeallocate(
    void * memory
    , kaphein_SSize memorySize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(memory == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(memorySize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        free(memory);
    }

    return errorCode;
}
