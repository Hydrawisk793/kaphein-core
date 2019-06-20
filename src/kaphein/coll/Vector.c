#include "kaphein/mem/utils.h"
#include "kaphein/coll/Vector.h"

struct kaphein_coll_Vector
{
    kaphein_SSize endIndex_;

    kaphein_SSize capacity_;

    char * begin_;

    struct kaphein_mem_Allocator * allocator_;

    struct kaphein_coll_Vector_ElementTraits elementTraits_;
};

static
enum kaphein_ErrorCode
kaphein_x_shiftElementLeft(
    struct kaphein_coll_Vector * obj
    , kaphein_SSize endIndex
    , kaphein_SSize shiftAmount
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    const kaphein_SSize elementSize = obj->elementTraits_.elementSize;
    const kaphein_SSize shiftOffset = shiftAmount * elementSize;
    const kaphein_SSize elementCount = endIndex - shiftAmount;
    kaphein_SSize i;
    char * dest = obj->begin_;
    char * src = dest + shiftOffset;

    for(i = elementCount; i > 0; dest += elementSize, src += elementSize) {
        --i;

        if(obj->elementTraits_.destruct != KAPHEIN_NULL) {
            errorCode = (*obj->elementTraits_.destruct)(dest);
        }

        if(obj->elementTraits_.copyConstruct != KAPHEIN_NULL) {
            errorCode = (*obj->elementTraits_.copyConstruct)(
                dest
                , src
                , obj->allocator_
            );
        }
    }

    if(obj->elementTraits_.destruct != KAPHEIN_NULL) {
        for(i = shiftAmount; i > 0; dest += elementSize) {
            --i;
            
            errorCode = (*obj->elementTraits_.destruct)(dest);
        }
    }

    return errorCode;
}

//TODO : Implement this function.
static
enum kaphein_ErrorCode
kaphein_x_shiftElementRight(
    struct kaphein_coll_Vector * obj
    , kaphein_SSize beginIndex
    , kaphein_SSize shiftAmount
)
{
    obj;
    beginIndex;
    shiftAmount;

    return kapheinErrorCodeNotImplemented;
}

struct kaphein_coll_Vector *
kaphein_coll_Vector_new(
    struct kaphein_mem_Allocator * allocator
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    struct kaphein_coll_Vector *const obj = (struct kaphein_coll_Vector *)kaphein_mem_allocate(
        allocator
        , KAPHEIN_ssizeof(*obj)
        , hint
        , errorCodeOut
    );

    if(obj != KAPHEIN_NULL) {
        obj->endIndex_ = 0;
        obj->capacity_ = 0;
        obj->begin_ = KAPHEIN_NULL;
        obj->allocator_ = KAPHEIN_NULL;
        obj->elementTraits_.copyConstruct = KAPHEIN_NULL;
        obj->elementTraits_.destruct = KAPHEIN_NULL;
    }

    return obj;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_delete(
    struct kaphein_coll_Vector * obj
    , struct kaphein_mem_Allocator * allocator
)
{
    return kaphein_mem_deallocate(
        allocator
        , obj
        , KAPHEIN_ssizeof(*obj)
    );
}

enum kaphein_ErrorCode
kaphein_coll_Vector_construct(
    struct kaphein_coll_Vector * thisObj
    , const struct kaphein_coll_Vector_ElementTraits * elementTraits
    , kaphein_SSize initialCapacity
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || elementTraits == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(elementTraits->elementSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        kaphein_mem_copy(
            &thisObj->elementTraits_
            , KAPHEIN_ssizeof(thisObj->elementTraits_)
            , elementTraits
            , KAPHEIN_ssizeof(*elementTraits)
        );
        
        if(initialCapacity < 0) {
            initialCapacity = 4 * KAPHEIN_ssizeof(void *);
        }

        thisObj->begin_ = (char *)kaphein_mem_allocate(
            allocator
            , initialCapacity * elementTraits->elementSize
            , KAPHEIN_NULL
            , &errorCode
        );
        if(thisObj->begin_ == KAPHEIN_NULL) {
            goto endOfInit;
        }
        thisObj->endIndex_ = 0;
        thisObj->capacity_ = initialCapacity;
        
        thisObj->allocator_ = allocator;

    endOfInit:
        ;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_destruct(
    struct kaphein_coll_Vector * thisObj
)
{
    enum kaphein_ErrorCode errorCode;

    errorCode = kaphein_coll_Vector_clear(thisObj);
    if(errorCode != kapheinErrorCodeNoError) {
        goto endOfFunc;
    }

    errorCode = kaphein_mem_deallocate(
        thisObj->allocator_
        , thisObj->begin_
        , (kaphein_SSize)(thisObj->capacity_ * thisObj->elementTraits_.elementSize)
    );
    if(errorCode != kapheinErrorCodeNoError) {
        goto endOfFunc;
    }
    
    thisObj->endIndex_ = 0;
    thisObj->capacity_ = 0;
    thisObj->begin_ = KAPHEIN_NULL;
    thisObj->allocator_ = KAPHEIN_NULL;
    thisObj->elementTraits_.copyConstruct = KAPHEIN_NULL;
    thisObj->elementTraits_.destruct = KAPHEIN_NULL;

endOfFunc:

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_isEmpty(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = thisObj->endIndex_ == 0;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_getCapacity(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * capacityOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || capacityOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *capacityOut = thisObj->capacity_;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_getCount(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * countOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || countOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *countOut = thisObj->endIndex_;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_Vector_clear(
    struct kaphein_coll_Vector * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {;
        kaphein_destructFunction *const destructFunction = thisObj->elementTraits_.destruct;
        const kaphein_SSize elementSize = thisObj->elementTraits_.elementSize;
        kaphein_SSize i;
        char * element;

        for(
            i = thisObj->endIndex_, element = thisObj->begin_ + i * elementSize;
            errorCode == kapheinErrorCodeNoError && i > 0;
        ) {
            --i;
            element -= thisObj->elementTraits_.elementSize;

            if(destructFunction != KAPHEIN_NULL) {
                errorCode = (*destructFunction)(element);
            }
        }
    }

    return errorCode;
}
