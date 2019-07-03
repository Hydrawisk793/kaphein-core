#include <string.h>
#include "kaphein/ErrorCode.h"
#include "kaphein/mem/defAlloc.h"
#include "kaphein/mem/utils.h"

enum kaphein_ErrorCode
kaphein_mem_copy(
    void * dest
    , kaphein_SSize destSize
    , const void * src
    , kaphein_SSize count
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(destSize < 0 || count < 0 || count > destSize) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        memcpy(dest, src, count);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_mem_fillZero(
    void * dest
    , kaphein_SSize destSize
    , kaphein_SSize count
)
{
    return kaphein_mem_fill(dest, destSize, 0, count);
}

enum kaphein_ErrorCode
kaphein_mem_fill(
    void * dest
    , kaphein_SSize destSize
    , int value
    , kaphein_SSize count
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(destSize < 0 || count < 0 || count > destSize) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        memset(dest, value & 0xFF, count);
    }

    return errorCode;
}

int
kaphein_mem_compare(
    const void * lhs
    , kaphein_SSize lhsSize
    , const void * rhs
    , kaphein_SSize rhsSize
)
{
    const kaphein_SSize clampedLhsSize = lhsSize & KAPHEIN_SSIZE_MAXIMUM;
    const kaphein_SSize clampedRhsSize = rhsSize & KAPHEIN_SSIZE_MAXIMUM;
    const kaphein_SSize minSize = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, clampedLhsSize, clampedRhsSize);

    return memcmp(lhs, rhs, minSize);
}

void *
kaphein_mem_allocate(
    struct kaphein_mem_Allocator * allocator
    , kaphein_SSize memorySize
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    void * memory = KAPHEIN_NULL;

    if(allocator == KAPHEIN_NULL) {
        memory = kaphein_mem_defaultAllocate(
            memorySize
            , hint
            , errorCodeOut
        );
    }
    else {
        if(memorySize < 0) {
            errorCode = kapheinErrorCodeArgumentOutOfRange;
        }
        else {
            memory = (*allocator->vTable->allocate)(
                allocator->thisObj
                , memorySize
                , hint
                , errorCodeOut
            );
        }
    }

    return memory;
}

enum kaphein_ErrorCode
kaphein_mem_deallocate(
    struct kaphein_mem_Allocator * allocator
    , void * memory
    , kaphein_SSize memorySize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(allocator == KAPHEIN_NULL) {
        errorCode = kaphein_mem_defaultDeallocate(
            memory
            , memorySize
        );
    }
    else {
        if(memory == KAPHEIN_NULL) {
            errorCode = kapheinErrorCodeArgumentNull;
        }
        else if(memorySize < 0) {
            errorCode = kapheinErrorCodeArgumentOutOfRange;
        }
        else {
            errorCode = (*allocator->vTable->deallocate)(
                allocator->thisObj
                , memory
                , memorySize
            );
        }
    }

    return errorCode;
}
