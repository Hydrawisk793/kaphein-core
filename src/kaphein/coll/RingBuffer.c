#include "kaphein/mem/utils.h"
#include "kaphein/coll/RingBuffer.h"

/* ******************************** */
/* Definitions */

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_construct(
    struct kaphein_coll_RingBuffer * thisObj
    , char * byteArray
    , kaphein_SSize byteArraySize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || byteArray == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(byteArraySize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        thisObj->byteArray_ = byteArray;
        thisObj->inPtr_ = thisObj->byteArray_;
        thisObj->outPtr_ = thisObj->byteArray_;
        thisObj->byteArraySize_ = byteArraySize;

        kaphein_mem_fill(thisObj->byteArray_, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM, 0xFF, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_destruct(
    struct kaphein_coll_RingBuffer * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        kaphein_mem_fill(thisObj->byteArray_, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM, 0xFF, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
        
        thisObj->byteArray_ = KAPHEIN_NULL;
        thisObj->inPtr_ = KAPHEIN_NULL;
        thisObj->outPtr_ = KAPHEIN_NULL;
        thisObj->byteArraySize_ = 0;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_isEmpty(
    const struct kaphein_coll_RingBuffer * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = thisObj->inPtr_ == thisObj->outPtr_
            && (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MINIMUM) == 0
        ;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_isFull(
    const struct kaphein_coll_RingBuffer * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = thisObj->inPtr_ == thisObj->outPtr_
            && (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MINIMUM) != 0
        ;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getCapacity(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * capacityOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || capacityOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *capacityOut = (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getAvailable(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * availableOut
)
{
    enum kaphein_ErrorCode errorCode;
    kaphein_SSize count;

    errorCode = kaphein_coll_RingBuffer_getCount(thisObj, &count);
    if(errorCode == kapheinErrorCodeNoError) {
        *availableOut = (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM) - count;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getCount(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * countOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || countOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const kaphein_PtrDiff diff = thisObj->inPtr_ - thisObj->outPtr_;
        kaphein_SSize count;

        if(diff == 0) {
            if((thisObj->byteArraySize_ & KAPHEIN_SSIZE_MINIMUM) != 0) {
                count = (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
            }
            else {
                count = 0;
            }
        }
        else {
            if(diff > 0) {
                count = (kaphein_SSize)diff;
            }
            else {
                count = (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM) + (kaphein_SSize)diff;
            }
        }

        *countOut = count;
    }
    
    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_enqueue(
    struct kaphein_coll_RingBuffer * thisObj
    , const char * src
    , kaphein_SSize srcSize
    , kaphein_SSize * countOut
)
{
    enum kaphein_ErrorCode errorCode;
    kaphein_SSize count = 0;

    if(thisObj == KAPHEIN_NULL || src == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(srcSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(thisObj->byteArray_ == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        if(
            thisObj->outPtr_ < thisObj->inPtr_
            || (thisObj->inPtr_ == thisObj->outPtr_ && (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MINIMUM) == 0)
        ) {
            char *const byteArrayEnd = thisObj->byteArray_ + (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
            const kaphein_SSize frontAvailable = (kaphein_SSize)(byteArrayEnd - thisObj->inPtr_);
            const kaphein_SSize frontCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, srcSize, frontAvailable);
            const kaphein_SSize rearAvailable = (kaphein_SSize)(thisObj->outPtr_ - thisObj->byteArray_);
            const kaphein_SSize rearCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, srcSize - frontCount, rearAvailable);

            kaphein_mem_copy(thisObj->inPtr_, frontCount, src, frontCount);
            kaphein_mem_copy(thisObj->byteArray_, rearCount, src + frontCount, rearCount);
            count = frontCount + rearCount;

            thisObj->inPtr_ += frontCount;
            if(thisObj->inPtr_ >= byteArrayEnd) {
                thisObj->inPtr_ = thisObj->byteArray_ + rearCount;
            }

            if(thisObj->inPtr_ == thisObj->outPtr_) {
                thisObj->byteArraySize_ |= KAPHEIN_SSIZE_MINIMUM;
            }
        }
        else {
            const kaphein_SSize rearAvailable = (kaphein_SSize)(thisObj->inPtr_ - thisObj->byteArray_);
            const kaphein_SSize rearCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, srcSize, rearAvailable);

            kaphein_mem_copy(thisObj->inPtr_, rearCount, src, rearCount);
            count = rearCount;

            thisObj->inPtr_ += rearCount;
        }

        if(count < srcSize) {
            errorCode = kapheinErrorCodeCollectionOverflow;
        }
        else {
            errorCode = kapheinErrorCodeNoError;
        }

        if(countOut != KAPHEIN_NULL) {
            *countOut = count;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_dequeue(
    struct kaphein_coll_RingBuffer * thisObj
    , char * dest
    , kaphein_SSize destSize
    , kaphein_SSize * countOut
)
{
    enum kaphein_ErrorCode errorCode;
    kaphein_SSize count = 0;

    if(thisObj == KAPHEIN_NULL || dest == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(destSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(thisObj->byteArray_ == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        if(
            thisObj->inPtr_ < thisObj->outPtr_
            || (thisObj->inPtr_ == thisObj->outPtr_ && (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MINIMUM) != 0)
        ) {
            char *const byteArrayEnd = thisObj->byteArray_ + (thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);
            const kaphein_SSize frontAvailable = (kaphein_SSize)(byteArrayEnd - thisObj->outPtr_);
            const kaphein_SSize frontCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, destSize, frontAvailable);
            const kaphein_SSize rearAvailable = (kaphein_SSize)(thisObj->inPtr_ - thisObj->byteArray_);
            const kaphein_SSize rearCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, destSize - frontCount, rearAvailable);

            kaphein_mem_copy(dest, frontCount, thisObj->outPtr_, frontCount);
            kaphein_mem_fill(thisObj->outPtr_, frontCount, 0xFF, frontCount);
            kaphein_mem_copy(dest + frontCount, rearCount, thisObj->byteArray_, rearCount);
            kaphein_mem_fill(thisObj->byteArray_ + frontCount, rearCount, 0xFF, rearCount);
            count = frontCount + rearCount;

            thisObj->outPtr_ += frontCount;
            if(thisObj->outPtr_ >= byteArrayEnd) {
                thisObj->outPtr_ = thisObj->byteArray_ + rearCount;
            }

            if(thisObj->inPtr_ == thisObj->outPtr_) {
                thisObj->byteArraySize_ &= (~KAPHEIN_SSIZE_MINIMUM);
            }
        }
        else {
            const kaphein_SSize rearAvailable = (kaphein_SSize)(thisObj->inPtr_ - thisObj->outPtr_);
            const kaphein_SSize rearCount = KAPHEIN_x_FIND_MINIMUM_SIGNED_INT(KAPHEIN_SSIZE_BITSIZE, destSize, rearAvailable);

            kaphein_mem_copy(dest, rearCount, thisObj->outPtr_, rearCount);
            count = rearCount;
            
            thisObj->outPtr_ += rearCount;
        }

        if(count < destSize) {
            errorCode = kapheinErrorCodeCollectionUnderflow;
        }
        else {
            errorCode = kapheinErrorCodeNoError;
        }

        if(countOut != KAPHEIN_NULL) {
            *countOut = count;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_RingBuffer_clear(
    struct kaphein_coll_RingBuffer * thisObj
)
{
    enum kaphein_ErrorCode errorCode;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(thisObj->byteArray_ == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        thisObj->outPtr_ = thisObj->inPtr_;
        thisObj->byteArraySize_ &= (~KAPHEIN_SSIZE_MINIMUM);

        kaphein_mem_fill(thisObj->byteArray_, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM, 0xFF, thisObj->byteArraySize_ & KAPHEIN_SSIZE_MAXIMUM);

        errorCode = kapheinErrorCodeNoError;
    }

    return errorCode;
}

/* ******************************** */
