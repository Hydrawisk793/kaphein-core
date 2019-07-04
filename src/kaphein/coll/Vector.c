#include "kaphein/mem/utils.h"
#include "kaphein/coll/Vector.h"

struct Vector_Impl
{
    char * begin_;

    struct kaphein_mem_Allocator * allocator_;

    const struct kaphein_coll_ElementTrait * elementTrait_;

    kaphein_SSize endIndex_;

    kaphein_SSize capacity_;
};

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
kaphein_SSize
getCount(
    const struct Vector_Impl * impl
)
{
    return impl->endIndex_;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
isEmpty(
    const struct Vector_Impl * impl
)
{
    return impl->endIndex_ < 1;
}

static
enum kaphein_ErrorCode
resizeContainer(
    struct Vector_Impl * impl
    , kaphein_SSize newCapacity
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(newCapacity < 0) {
        resultErrorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        char * newContainer = KAPHEIN_NULL;
        char * src;
        char * dest;
        const kaphein_SSize currentElementCount = getCount(impl);
        const kaphein_SSize elementSize = impl->elementTrait_->elementSize;
        kaphein_SSize newEndIndex = impl->endIndex_;
        kaphein_SSize i;
        int state;

        for(state = 5; kapheinErrorCodeNoError == resultErrorCode && state > 0; ) {
            switch(state) {
            case 5:
                newContainer = (char *)kaphein_mem_allocate(
                    impl->allocator_
                    , newCapacity * elementSize
                    , KAPHEIN_NULL
                    , &resultErrorCode
                );

                #if defined(_DEBUG)
                if(kapheinErrorCodeNoError == resultErrorCode) {
                    kaphein_mem_fill(
                        newContainer
                        , newCapacity * elementSize
                        , 0xFF
                        , newCapacity * elementSize
                    );
                }
                #endif
            break;
            case 4:
                if(KAPHEIN_NULL != impl->begin_) {
                    if(newCapacity < currentElementCount) {
                        i = newCapacity;
                        newEndIndex = newCapacity;
                    }
                    else {
                        i = currentElementCount;
                    }

                    for(
                        dest = newContainer, src = impl->begin_;
                        kapheinErrorCodeNoError == resultErrorCode && i > 0;
                        dest += elementSize, src += elementSize
                    ) {
                        --i;

                        resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                            dest
                            , src
                            , impl->allocator_
                        );
                    }
                }
            break;
            case 3:
                for(
                    src = impl->begin_, i = currentElementCount;
                    kapheinErrorCodeNoError == resultErrorCode && i > 0;
                    src += elementSize
                ) {
                    --i;
                    
                    resultErrorCode = (*impl->elementTrait_->destruct)(src);
                }
            break;
            case 2:
                if(KAPHEIN_NULL != impl->begin_) {
                    resultErrorCode = kaphein_mem_deallocate(
                        impl->allocator_
                        , impl->begin_
                        , impl->capacity_ * elementSize
                    );
                }
            break;
            case 1:
                impl->begin_ = newContainer;
                impl->capacity_ = newCapacity;
                impl->endIndex_ = newEndIndex;
            break;
            }

            if(kapheinErrorCodeNoError == resultErrorCode) {
                --state;
            }
        }
    }

    return resultErrorCode;
}

static
enum kaphein_ErrorCode
reserveCapacity(
    struct Vector_Impl * impl
    , kaphein_SSize newCapacity
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(newCapacity > impl->capacity_) {
        resultErrorCode = resizeContainer(impl, newCapacity);
    }

    return resultErrorCode;
}

static
enum kaphein_ErrorCode
expandContainerIfNeccesary(
    struct Vector_Impl * impl
    , kaphein_SSize minimumRequiredCapacity
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const kaphein_SSize originalCapacity = impl->capacity_;
    kaphein_SSize prevCapacity;
    kaphein_SSize newCapacity = impl->capacity_;
    
    while(
        newCapacity < KAPHEIN_SSIZE_MAXIMUM
        && newCapacity < minimumRequiredCapacity
    ) {
        prevCapacity = newCapacity;
        newCapacity <<= 1;

        if((newCapacity >> 1) != prevCapacity) {
            newCapacity = KAPHEIN_SSIZE_MAXIMUM;
        }
    }
    
    resultErrorCode = reserveCapacity(impl, newCapacity);
    if(kapheinErrorCodeNoError == resultErrorCode) {
        if(
            minimumRequiredCapacity > originalCapacity
            && originalCapacity >= impl->capacity_
        ) {
            resultErrorCode = kapheinErrorCodeCollectionOverflow;
        }
    }

    return resultErrorCode;
}

static
enum kaphein_ErrorCode
shiftElementLeft(
    struct Vector_Impl * impl
    , kaphein_SSize startIndex
    , kaphein_SSize endIndex
    , kaphein_SSize shiftAmount
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const kaphein_SSize elementSize = impl->elementTrait_->elementSize;
    kaphein_SSize elementCount;
    kaphein_SSize shiftOffset;
    kaphein_SSize i;
    char * dest;
    char * current;
    char * src;

    if(startIndex < shiftAmount) {
        startIndex += shiftAmount - startIndex;
    }

    if(startIndex > endIndex) {
        startIndex = endIndex;
    }

    shiftOffset = shiftAmount * elementSize;
    dest = impl->begin_ + (startIndex * elementSize - shiftOffset);
    elementCount = endIndex - startIndex;

    if(elementCount > 0) {
        for(
            current = dest, i = shiftAmount;
            i > 0;
            current += elementSize
        ) {
            --i;
        
            resultErrorCode = (*impl->elementTrait_->destruct)(current);
        }
    }

    for(
        current = dest, src = dest + shiftOffset, i = elementCount;
        i > 0;
        current += elementSize, src += elementSize
    ) {
        --i;

        resultErrorCode = (*impl->elementTrait_->copyConstruct)(
            current
            , src
            , impl->allocator_
        );

        resultErrorCode = (*impl->elementTrait_->destruct)(src);
    }

    return resultErrorCode;
}

static
enum kaphein_ErrorCode
shiftElementRight(
    struct Vector_Impl * impl
    , kaphein_SSize startIndex
    , kaphein_SSize endIndex
    , kaphein_SSize shiftAmount
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const kaphein_SSize elementSize = impl->elementTrait_->elementSize;
    const kaphein_SSize elementCount = endIndex - startIndex;
    const kaphein_SSize destEndIndex = endIndex + shiftAmount;
    const kaphein_SSize shiftOffset = shiftAmount * elementSize;
    kaphein_SSize i;
    char * dest;
    char * src;
    int state;

    for(state = 3; kapheinErrorCodeNoError == resultErrorCode && state > 0; ) {
        switch(state) {
        case 3:
            resultErrorCode = expandContainerIfNeccesary(impl, destEndIndex);
        break;
        case 2:
            if(elementCount > 0) {
                if(impl->endIndex_ < destEndIndex) {
                    i = impl->endIndex_ - endIndex;
                }
                else {
                    i = shiftAmount;
                }

                for(
                    dest = impl->begin_ + endIndex * elementSize;
                    kapheinErrorCodeNoError == resultErrorCode && i > 0;
                    dest += elementSize
                ) {
                    --i;
            
                    resultErrorCode = (*impl->elementTrait_->destruct)(dest);
                }
            }
        break;
        case 1:
            src = impl->begin_ + endIndex * elementSize;
            dest = src + shiftOffset;

            for(
                i = elementCount;
                kapheinErrorCodeNoError == resultErrorCode && i > 0;
                
            ) {
                --i;
                dest -= elementSize;
                src -= elementSize;

                resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                    dest
                    , src
                    , impl->allocator_
                );

                if(kapheinErrorCodeNoError == resultErrorCode) {
                    resultErrorCode = (*impl->elementTrait_->destruct)(src);
                }
            }
        break;
        }
        
        if(kapheinErrorCodeNoError == resultErrorCode) {
            --state;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_construct(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize initialCapacity
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == elementTrait
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    //else if(KAPHEIN_NULL != thisObj->impl_) {
    //    resultErrorCode = kapheinErrorCodeOperationInvalid;
    //}
    else {
        struct Vector_Impl * impl = KAPHEIN_NULL;
        int state;
        
        if(initialCapacity < 1) {
            initialCapacity = 8;
        }

        for(state = 2; state > 0 && kapheinErrorCodeNoError == resultErrorCode; ) {
            switch(state) {
            case 2:
                impl = thisObj->impl_ = (struct Vector_Impl *)kaphein_mem_allocate(
                    allocator
                    , KAPHEIN_ssizeof(struct Vector_Impl)
                    , KAPHEIN_NULL
                    , &resultErrorCode
                );
            break;
            case 1:
                impl->allocator_ = allocator;
                impl->elementTrait_ = elementTrait;
                impl->begin_ = KAPHEIN_NULL;
                impl->capacity_ = 0;
                impl->endIndex_ = 0;

                resultErrorCode = reserveCapacity(impl, initialCapacity);
            break;
            }

            if(kapheinErrorCodeNoError == resultErrorCode) {
                --state;
            }
        }

        if(kapheinErrorCodeNoError != resultErrorCode) {
            kaphein_coll_Vector_destruct(thisObj);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_destruct(
    struct kaphein_coll_Vector * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl * impl = KAPHEIN_NULL;
        int state;

        for(state = 4; state > 0; ) {
            switch(state) {
            case 4:
                resultErrorCode = kaphein_coll_Vector_clear(thisObj);
            break;
            case 3:
                impl = (struct Vector_Impl *)thisObj->impl_;
                
                if(KAPHEIN_NULL != impl) {
                    if(KAPHEIN_NULL != impl->begin_) {
                        resultErrorCode = kaphein_mem_deallocate(
                            impl->allocator_
                            , impl->begin_
                            , impl->capacity_ * impl->elementTrait_->elementSize
                        );
                    }
                }
            break;
            case 2:
                if(KAPHEIN_NULL != impl) {
                    impl->begin_ = KAPHEIN_NULL;

                    resultErrorCode = kaphein_mem_deallocate(
                        impl->allocator_
                        , impl
                        , KAPHEIN_ssizeof(*impl)
                    );
                }
            break;
            case 1:
                thisObj->impl_ = KAPHEIN_NULL;
            break;
            }

            if(kapheinErrorCodeNoError == resultErrorCode) {
                --state;
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_getCapacity(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * capacityOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == capacityOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct Vector_Impl *const impl = (const struct Vector_Impl *)thisObj->impl_;
        
        *capacityOut = impl->capacity_;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_resize(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        
        resultErrorCode = resizeContainer(impl, size);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_reserve(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
)
{
    enum kaphein_ErrorCode resultErrorCode;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultErrorCode = reserveCapacity((struct Vector_Impl *)thisObj->impl_, size);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_trim(
    struct kaphein_coll_Vector * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        
        resultErrorCode = resizeContainer(impl, getCount(impl));
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_getPointerToElements(
    const struct kaphein_coll_Vector * thisObj
    , void ** pointerOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == pointerOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct Vector_Impl *const impl = (const struct Vector_Impl *)thisObj->impl_;
        
        if(KAPHEIN_NULL == impl) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            *pointerOut = impl->begin_;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_isEmpty(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == truthOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = isEmpty((const struct Vector_Impl *)thisObj->impl_);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_isFull(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == truthOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct Vector_Impl *const impl = (const struct Vector_Impl *)thisObj->impl_;
        
        //TODO : What does 'isFull' mean on vectors?
        *truthOut = impl->capacity_ >= KAPHEIN_SSIZE_MAXIMUM
            && impl->endIndex_ >= impl->capacity_
        ;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_getCount(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * countOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == countOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct Vector_Impl *const impl = (const struct Vector_Impl *)thisObj->impl_;
        
        *countOut = getCount(impl);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_pushFront(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
)
{
    return kaphein_coll_Vector_insert(thisObj, 0, element, elementSize, 1);
}

enum kaphein_ErrorCode
kaphein_coll_Vector_popFront(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
)
{
    return kaphein_coll_Vector_remove(thisObj, 0, 1, elementOut, elementOutSize);
}

enum kaphein_ErrorCode
kaphein_coll_Vector_pushBack(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        
        if(elementSize < impl->elementTrait_->elementSize) {
            resultErrorCode = kapheinErrorCodeNotEnoughBufferSpace;
        }
        else {
            resultErrorCode = expandContainerIfNeccesary(impl, getCount(impl) + 1);
            if(kapheinErrorCodeNoError == resultErrorCode) {
                resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                    impl->begin_ + (impl->endIndex_ * impl->elementTrait_->elementSize)
                    , element
                    , impl->allocator_
                );

                if(kapheinErrorCodeNoError == resultErrorCode) {
                    ++impl->endIndex_;
                }
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_popBack(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        
        if(isEmpty(impl)) {
            resultErrorCode = kapheinErrorCodeCollectionUnderflow;
        }
        else if(
            KAPHEIN_NULL != elementOut
            && elementOutSize < impl->elementTrait_->elementSize
        ) {
            resultErrorCode = kapheinErrorCodeNotEnoughBufferSpace;
        }
        else {
            char *const src = impl->begin_ + ((impl->endIndex_ - 1) * impl->elementTrait_->elementSize);

            if(KAPHEIN_NULL != elementOut) {
                resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                    elementOut
                    , src
                    , impl->allocator_
                );
            }

            if(kapheinErrorCodeNoError == resultErrorCode) {
                resultErrorCode = (*impl->elementTrait_->destruct)(src);

                if(kapheinErrorCodeNoError == resultErrorCode) {
                    --impl->endIndex_;
                }
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_insert(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize startIndex
    , const void * elements
    , kaphein_SSize elementSize
    , kaphein_SSize elementCount
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;

        if(
            (startIndex < 0 || startIndex > getCount(impl))
            || elementCount < 0
            || elementSize < impl->elementTrait_->elementSize
        ) {
            resultErrorCode = kapheinErrorCodeArgumentOutOfRange;
        }
        else if(elementCount < 1 && KAPHEIN_NULL == elements) {
            resultErrorCode = kapheinErrorCodeArgumentNull;
        }
        else {
            resultErrorCode = shiftElementRight(impl, startIndex, impl->endIndex_, elementCount);
            
            if(kapheinErrorCodeNoError == resultErrorCode) {
                char * dest;
                const char * src;
                kaphein_SSize i;
            
                elementSize = impl->elementTrait_->elementSize;

                for(
                    dest = impl->begin_ + (startIndex * elementSize), src = (const char *)elements, i = elementCount;
                    kapheinErrorCodeNoError == resultErrorCode && i > 0;
                    dest += elementSize, src += elementSize, ++impl->endIndex_
                ) {
                    --i;

                    resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                        dest
                        , src
                        , impl->allocator_
                    );
                }
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_remove(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize index
    , kaphein_SSize count
    , void * elementsOut
    , kaphein_SSize elementsOutSize
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        const kaphein_SSize elementSize = impl->elementTrait_->elementSize;
        const kaphein_SSize currentElementCount = getCount(impl);
        kaphein_SSize i;
        char *const srcBegin = impl->begin_ + index * elementSize;
        char * src;
        char * dest;
        int state;

        for(state = 5; resultErrorCode == kapheinErrorCodeNoError && state > 0; ) {
            switch(state) {
            case 5:
                if(
                    (index < 0 || index >= currentElementCount)
                    || (count < 0 || index + count > currentElementCount)
                ) {
                    resultErrorCode = kapheinErrorCodeArgumentOutOfRange;
                }
            break;
            case 4:
                if(
                    KAPHEIN_NULL != elementsOut
                    && elementsOutSize <  count * elementSize
                ) {
                    resultErrorCode = kapheinErrorCodeNotEnoughBufferSpace;
                }
            break;
            case 3:
                if(KAPHEIN_NULL != elementsOut) {
                    for(
                        dest = (char *)elementsOut, src = srcBegin, i = count;
                        resultErrorCode == kapheinErrorCodeNoError && i > 0;
                        dest += elementSize, src += elementSize
                    ) {
                        --i;

                        resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                            dest
                            , src
                            , impl->allocator_
                        );
                    }
                }
            break;
            case 2:
                if(index + count < impl->endIndex_) {
                    resultErrorCode = shiftElementLeft(
                        impl
                        , index + count
                        , impl->endIndex_
                        , count
                    );
                }
                else {
                    for(
                        src = srcBegin, i = count;
                        resultErrorCode == kapheinErrorCodeNoError && i > 0;
                        src += elementSize
                    ) {
                        --i;

                        resultErrorCode = (*impl->elementTrait_->destruct)(src);
                    }
                }
            break;
            case 1:
                impl->endIndex_ -= count;
            break;
            }

            if(resultErrorCode == kapheinErrorCodeNoError) {
                --state;
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_clear(
    struct kaphein_coll_Vector * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Vector_Impl *const impl = (struct Vector_Impl *)thisObj->impl_;
        const kaphein_SSize elementSize = impl->elementTrait_->elementSize;
        kaphein_SSize i;
        char * current;

        for(
            i = getCount(impl), current = impl->begin_ + i * elementSize;
            resultErrorCode == kapheinErrorCodeNoError && i > 0;
        ) {
            --i;
            current -= elementSize;

            resultErrorCode = (*impl->elementTrait_->destruct)(current);

            if(kapheinErrorCodeNoError == resultErrorCode) {
                --impl->endIndex_;
            }
        }
    }

    return resultErrorCode;
}
