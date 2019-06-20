#include "kaphein/ErrorCode.h"
#include "kaphein/mem/utils.h"
#include "kaphein/mem/SegmentPool.h"

static int kapheinCalcualtePaddedSize(
    int size
    , int alignSize
)
{
   const int r = size % alignSize;

   return size + (r > 0 ? alignSize - r : 0);
}

struct kapheinSegment
{
    struct kapheinSegment *prev_;

    struct kapheinSegment *next_;

    char *memoryEnd_;

    union {
        void *dummyForPadding_;
        struct {
            bool isAllocated_;
            uint8_t reserved_;
        } flags_;
    } attribute_;

    KAPHEIN_DECLARE_FAM(char, memory_)
};

KAPHEIN_ATTRIBUTE_INLINE
static int kapheinSegmentGetMemorySize(
    const struct kapheinSegment *thisObj
)
{
    return (int)(thisObj->memoryEnd_ - thisObj->memory_);
}

struct kapheinMemSegmentPool
{
    struct kapheinSegment *current_;
    
    char *memoryBegin_;

    char *memoryEnd_;
};

static struct kapheinSegment *kapheinSegmentPoolFindNextFit(
    const struct kapheinMemSegmentPool *thisObj
    , int size
);

static int kapheinSegmentPoolDoCompactionFrom(
    struct kapheinMemSegmentPool *thisObj
    , struct kapheinSegment *segment
);

int kapheinMemSegmentPoolGetSizeOf(void)
{
    return (int)sizeof(struct kapheinMemSegmentPool);
}

int kapheinMemSegmentPoolConstruct(
    struct kapheinMemSegmentPool *thisObjOut
    , void *memory
    , int memorySize
)
{
    int errorCode = kapheinErrorCodeNoError;
    
    if(thisObjOut == NULL || memory == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(memorySize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(memorySize < (int)sizeof(struct kapheinSegment)) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        thisObjOut->memoryBegin_ = memory;
        thisObjOut->memoryEnd_ = thisObjOut->memoryBegin_ + memorySize;
        kapheinMemFill(thisObjOut->memoryBegin_, memorySize, 0xFF, memorySize);
        
        thisObjOut->current_ = KAPHEIN_x_horrible_cast(struct kapheinSegment *, thisObjOut->memoryBegin_);
        thisObjOut->current_->prev_ = thisObjOut->current_;
        thisObjOut->current_->next_ = thisObjOut->current_;
        thisObjOut->current_->memoryEnd_ = thisObjOut->memoryEnd_;
        thisObjOut->current_->attribute_.flags_.isAllocated_ = false;
        thisObjOut->current_->attribute_.flags_.reserved_ = 0;
    }

    return errorCode;
}


int kapheinMemSegmentPoolDestruct(
    struct kapheinMemSegmentPool *thisObj
)
{
    int errorCode = kapheinErrorCodeNoError;
    
    if(thisObj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(
        thisObj->memoryBegin_ != (char *)((void *)thisObj->current_)
        ||thisObj->current_->prev_ != thisObj->current_->next_
    ) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        kapheinMemFill(thisObj->memoryBegin_, (int)(thisObj->memoryEnd_ - thisObj->memoryBegin_), 0xFF, (int)(thisObj->memoryEnd_ - thisObj->memoryBegin_));

        thisObj->current_ = NULL;
        thisObj->memoryBegin_ = NULL;
        thisObj->memoryEnd_ = 0;
    }

    return errorCode;
}

void *kapheinMemSegmentPoolAllocate(
    struct kapheinMemSegmentPool *thisObj
    , int size
    , void *hint
    , int *errorCodeOut
)
{
    struct kapheinSegment *segment;
    struct kapheinSegment *nextSegment;
    void *memory = NULL;
    int paddedSize;
    int errorCode = kapheinErrorCodeNoError;
    
    hint;

    if(thisObj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(size < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        segment = kapheinSegmentPoolFindNextFit(thisObj, size);
        if(segment == NULL) {
            errorCode = kapheinErrorCodeMemoryAllocationFailed;
        }
        else {
            segment->attribute_.flags_.isAllocated_ = true;
            paddedSize = kapheinCalcualtePaddedSize((int)sizeof(*segment) + size, (int)sizeof(void *));
            segment->memoryEnd_ = segment->memory_ + size;
            kapheinMemFill(segment->memory_, size, 0xAA, size);
            kapheinMemFill(segment->memoryEnd_, paddedSize - ((int)sizeof(*segment) + size), 0xDD, paddedSize - ((int)sizeof(*segment) + size));
            
            nextSegment = segment->next_;
            //TODO : 중간에 공간이 더 남았는지 조사.
            if(nextSegment == segment) {
                nextSegment = (struct kapheinSegment *)(KAPHEIN_x_horrible_cast(char *, segment) + paddedSize);
                if(KAPHEIN_x_horrible_cast(char *, nextSegment) + sizeof(*nextSegment) < thisObj->memoryEnd_) {
                    kapheinMemFill(nextSegment, (int)sizeof(*nextSegment), 0xFF, (int)sizeof(*nextSegment));
                    nextSegment->prev_ = segment;
                    nextSegment->next_ = nextSegment;
                    nextSegment->memoryEnd_ = thisObj->memoryEnd_;
                    nextSegment->attribute_.flags_.isAllocated_ = false;
                    nextSegment->attribute_.flags_.reserved_ = 0;

                    segment->next_ = nextSegment;

                    thisObj->current_ = nextSegment;
                }
            }

            memory = segment->memory_;
        }
    }
    if(errorCodeOut != NULL) {
        *errorCodeOut = errorCode;
    }

    return memory;
}

int kapheinMemSegmentPoolDeallocate(
    struct kapheinMemSegmentPool *thisObj
    , void *memory
    , int size
)
{
    struct kapheinSegment *segment = NULL;
    int errorCode = kapheinErrorCodeNoError;
    
    if(memory == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(
        segment = (struct kapheinSegment *)((char *)memory - (int)sizeof(struct kapheinSegment))
        , (segment->memory_ != memory || (int)(segment->memoryEnd_ - segment->memory_) != size)
    ) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(!segment->attribute_.flags_.isAllocated_) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        segment->attribute_.flags_.isAllocated_ = false;

        kapheinSegmentPoolDoCompactionFrom(thisObj, segment);
    }
    
    return errorCode;
}

static struct kapheinSegment *kapheinSegmentPoolFindNextFit(
    const struct kapheinMemSegmentPool *thisObj
    , int size
)
{
    struct kapheinSegment *segment = NULL;
    struct kapheinSegment *candidate = thisObj->current_;

    do {
        if(!candidate->attribute_.flags_.isAllocated_ && (int)(candidate->memoryEnd_ - candidate->memory_) >= size) {
            segment = candidate;
        }

        candidate = (candidate->next_ != candidate ? candidate->next_ : KAPHEIN_x_horrible_cast(struct kapheinSegment *, thisObj->memoryBegin_));
    }
    while(segment == NULL && candidate != thisObj->current_);

    return segment;
}

static int kapheinSegmentPoolDoCompactionFrom(
    struct kapheinMemSegmentPool *thisObj
    , struct kapheinSegment *segment
)
{
    struct kapheinSegment * beginOfMerged;
    struct kapheinSegment * endOfMerged;

    for(
        beginOfMerged = segment;
        beginOfMerged->prev_ != beginOfMerged && !beginOfMerged->prev_->attribute_.flags_.isAllocated_;
        beginOfMerged = beginOfMerged->prev_
    );
    for(
        endOfMerged = beginOfMerged;
        endOfMerged->next_ != endOfMerged && !endOfMerged->next_->attribute_.flags_.isAllocated_;
        endOfMerged = endOfMerged->next_
    );

    if(endOfMerged->next_ != endOfMerged) {
        endOfMerged->next_->prev_ = beginOfMerged;
        beginOfMerged->next_ = endOfMerged->next_;
        beginOfMerged->memoryEnd_ = KAPHEIN_x_horrible_cast(char *, endOfMerged->next_);
    }
    else {
        beginOfMerged->next_ = beginOfMerged;
        beginOfMerged->memoryEnd_ = thisObj->memoryEnd_;
    }
    beginOfMerged->attribute_.flags_.isAllocated_ = false;

    kapheinMemFill(beginOfMerged->memory_, kapheinSegmentGetMemorySize(beginOfMerged), 0xFF, kapheinSegmentGetMemorySize(beginOfMerged));

    thisObj->current_ = beginOfMerged;

    return 0;
}
