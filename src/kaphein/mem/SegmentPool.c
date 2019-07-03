#include <stdlib.h>
#include "kaphein/ErrorCode.h"
#include "kaphein/mem/SegmentPool.h"
#include "kaphein/mem/Allocator.h"

#define KAPHEIN_x_align_offset(ptr, alignSize) \
    (alignSize - (KAPHEIN_x_horrible_cast(kaphein_UIntPtr, ptr) & (alignSize - 1)))

union kaphein_x_MaximumAlignment
{
    void * (* pf);
    void * p;
    long double ld;
    long long ll;
    double d;
    float f;
    long l;
    short s;
};

struct kaphein_x_SegmentHeader
{
    struct kaphein_x_SegmentHeader * prevHeader_;
    
    struct kaphein_x_SegmentHeader * nextHeader_;
    
    char * memoryBegin_;

    kaphein_SSize memorySize_;
};

static kaphein_SSize kaphein_x_SegmentHeader_getMemorySize(
    struct kaphein_x_SegmentHeader *thisObj
)
{
    return thisObj->memorySize_;
}

struct kaphein_mem_SegmentPool
{
    struct kaphein_mem_Allocator parent;
    
    struct kaphein_x_SegmentHeader * begin_;
    
    struct kaphein_x_SegmentHeader * current_;

    char * memoryBegin_;
    
    char * memoryEnd_;
};

static struct kaphein_x_SegmentHeader * kaphein_mem_SegmentPool_findNextAvailableSegment(
    struct kaphein_mem_SegmentPool * thisObj
    , kaphein_SSize size
)
{
    struct kaphein_x_SegmentHeader *const start = thisObj->current_;
    struct kaphein_x_SegmentHeader * current = thisObj->current_;
    
    do {
        if(kaphein_x_SegmentHeader_getMemorySize(thisObj->current_) >= size) {
            
        }
        else {
            
        }
    }
    while(start != current);

    return current;
}

static const struct kaphein_mem_Allocator_VTable parentVTable = {
    KAPHEIN_NULL
    , kaphein_mem_SegmentPool_allocate
    , KAPHEIN_NULL
};

struct kaphein_mem_SegmentPool *
kaphein_mem_SegmentPool_new(
    enum kaphein_ErrorCode * errorCodeOut
)
{
    struct kaphein_mem_SegmentPool *const mem = (struct kaphein_mem_SegmentPool *)malloc(sizeof(struct kaphein_mem_SegmentPool));
    if(mem == NULL && errorCodeOut != KAPHEIN_NULL) {
        *errorCodeOut = kapheinErrorCodeMemoryAllocationFailed;
    }

    return mem;
}

enum kaphein_ErrorCode
kaphein_mem_SegmentPool_delete(
    void * mem
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(mem == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        free(mem);
    }
    
    return errorCode;
}

enum kaphein_ErrorCode
kaphein_mem_SegmentPool_construct(
    struct kaphein_mem_SegmentPool * thisObjOut
    , void * memory
    , kaphein_SSize memorySize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(
        thisObjOut == KAPHEIN_NULL
        || memory == KAPHEIN_NULL
    ) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(memorySize < KAPHEIN_ssizeof(struct kaphein_x_SegmentHeader)) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        thisObjOut->parent.vTable = &parentVTable;
        
        thisObjOut->memoryBegin_ = (char *)memory;
        thisObjOut->memoryEnd_ = thisObjOut->memoryBegin_ + memorySize;
        thisObjOut->begin_ = KAPHEIN_x_horrible_cast(struct kaphein_x_SegmentHeader *, thisObjOut->memoryBegin_ + KAPHEIN_x_align_offset(thisObjOut->memoryBegin_, sizeof(struct kaphein_x_SegmentHeader) / 4));

        if(KAPHEIN_x_horrible_cast(char *, thisObjOut->begin_) + KAPHEIN_ssizeof(struct kaphein_x_SegmentHeader) >= thisObjOut->memoryBegin_ + memorySize) {
            errorCode = kapheinErrorCodeArgumentInvalid;
        }
        else {
            thisObjOut->current_ = thisObjOut->begin_;
            thisObjOut->current_->prevHeader_ = thisObjOut->current_;
            thisObjOut->current_->nextHeader_ = thisObjOut->current_;
            thisObjOut->current_->memoryBegin_ = KAPHEIN_x_horrible_cast(char *, thisObjOut->current_) + KAPHEIN_ssizeof(*thisObjOut->current_);
            thisObjOut->current_->memorySize_ = (kaphein_SSize)(thisObjOut->memoryEnd_ - thisObjOut->current_->memoryBegin_);
        }
    }
    
    return errorCode;
}

void *
kaphein_mem_SegmentPool_allocate(
    void * thisObj
    , kaphein_SSize size
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    struct kaphein_mem_SegmentPool * const thisPtr = (struct kaphein_mem_SegmentPool *)thisObj;
    void * memory = KAPHEIN_NULL;
    
    KAPHEIN_x_UNUSED_PARAMETER(hint)

    if(KAPHEIN_NULL == thisPtr) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(size < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        struct kaphein_x_SegmentHeader *const next = kaphein_mem_SegmentPool_findNextAvailableSegment(thisPtr, size);
        if(next != thisPtr->current_) {
            
        }
        else {
            errorCode = kapheinErrorCodeMemoryAllocationFailed;
        }
    }

    if(KAPHEIN_NULL != errorCodeOut) {
        *errorCodeOut = errorCode;
    }

    return memory;
}
