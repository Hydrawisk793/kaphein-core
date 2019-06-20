#include "kaphein/mem/utils.h"
#include "kaphein/coll/List.h"

/* ******************************** */
/* Declarations */

struct kaphein_x_Node
{
    void * element_;
    
    struct kaphein_x_Node * prev_;

    struct kaphein_x_Node * next_;

    kaphein_SSize elementSize_;
};

static
enum kaphein_ErrorCode
kaphein_x_Node_create(
    struct kaphein_x_Node ** thisObjOut
    , const struct kaphein_coll_List * list
    , const void * element
    , kaphein_SSize elementSize
);

static
enum kaphein_ErrorCode
kaphein_x_Node_destroy(
    struct kaphein_x_Node * thisObj
    , const struct kaphein_coll_List * list
);

static
enum kaphein_ErrorCode
kaphein_x_Node_copyElement(
    const struct kaphein_x_Node * thisObj
    , const struct kaphein_coll_List * list
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_INLINE
static bool kaphein_coll_List_isFullInl(
    const struct kaphein_coll_List *obj
)
{
    return obj->count_ >= KAPHEIN_SSIZE_MAXIMUM;
}

KAPHEIN_ATTRIBUTE_INLINE
static bool kaphein_coll_List_isEmptyInl(
    const struct kaphein_coll_List *obj
)
{
    return obj->head_ == KAPHEIN_NULL
        && obj->tail_ == KAPHEIN_NULL
    ;
}

/* ******************************** */

/* ******************************** */
/* Definitions */

enum kaphein_ErrorCode
kaphein_coll_List_construct(
    struct kaphein_coll_List * thisObj
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObj->elementTrait_ = elementTrait;
        thisObj->allocator_ = allocator;
        thisObj->head_ = KAPHEIN_NULL;
        thisObj->tail_ = KAPHEIN_NULL;
        thisObj->count_ = 0;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_destruct(
    struct kaphein_coll_List * thisObj
)
{
    return kaphein_coll_List_clear(thisObj);
}

enum kaphein_ErrorCode
kaphein_coll_List_isEmpty(
    const struct kaphein_coll_List * thisObj
    , bool *truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = kaphein_coll_List_isEmptyInl(thisObj);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_isFull(
    const struct kaphein_coll_List * thisObj
    , bool *truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = kaphein_coll_List_isFullInl(thisObj);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_getCount(
    const struct kaphein_coll_List * thisObj
    , kaphein_SSize *countOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || countOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *countOut = thisObj->count_;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_pushFront(
    struct kaphein_coll_List * thisObj
    , const void * element
    , kaphein_SSize elementSize
)
{
    struct kaphein_x_Node * newNode;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isFullInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionOverflow;
    }
    else {
        errorCode = kaphein_x_Node_create(&newNode, thisObj, element, elementSize);
        if(errorCode == kapheinErrorCodeNoError) {
            if(thisObj->tail_ == KAPHEIN_NULL) {
                thisObj->tail_ = newNode;
            }

            if(thisObj->head_ != KAPHEIN_NULL) {
                ((struct kaphein_x_Node *)thisObj->head_)->prev_ = newNode;
                newNode->next_ = thisObj->head_;
            }
            thisObj->head_ = newNode;

            ++thisObj->count_;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_popFront(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
)
{
    struct kaphein_x_Node * nextOfHead;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isEmptyInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionUnderflow;
    }
    else {
        errorCode = kaphein_x_Node_copyElement(thisObj->head_, thisObj, elementOut, elementSizeInOut);
        if(errorCode == kapheinErrorCodeNoError) {
            nextOfHead = ((struct kaphein_x_Node *)thisObj->head_)->next_;

            errorCode = kaphein_x_Node_destroy(thisObj->head_, thisObj);
            if(errorCode == kapheinErrorCodeNoError) {
                if(nextOfHead != KAPHEIN_NULL) {
                   nextOfHead->prev_ = KAPHEIN_NULL;
                }

                thisObj->head_ = nextOfHead;

                if(thisObj->head_ == KAPHEIN_NULL) {
                    thisObj->tail_ = KAPHEIN_NULL;
                }

                --thisObj->count_;
            }
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_peekFront(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isEmptyInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionUnderflow;
    }
    else {
        errorCode = kaphein_x_Node_copyElement(thisObj->head_, thisObj, elementOut, elementSizeInOut);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_pushBack(
    struct kaphein_coll_List * thisObj
    , const void * element
    , kaphein_SSize elementSize
)
{
    struct kaphein_x_Node * newNode;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isFullInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionOverflow;
    }
    else {
        errorCode = kaphein_x_Node_create(&newNode, thisObj, element, elementSize);
        if(errorCode == kapheinErrorCodeNoError) {
            if(thisObj->head_ == KAPHEIN_NULL) {
                thisObj->head_ = newNode;
            }

            if(thisObj->tail_ != KAPHEIN_NULL) {
                ((struct kaphein_x_Node *)thisObj->tail_)->next_ = newNode;
                newNode->prev_ = thisObj->tail_;
            }
            thisObj->tail_ = newNode;

            ++thisObj->count_;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_popBack(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
)
{
    struct kaphein_x_Node * prevOfTail;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isEmptyInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionUnderflow;
    }
    else {
        errorCode = kaphein_x_Node_copyElement(thisObj->tail_, thisObj, elementOut, elementSizeInOut);
        if(errorCode == kapheinErrorCodeNoError) {
            prevOfTail = ((struct kaphein_x_Node *)thisObj->tail_)->prev_;

            errorCode = kaphein_x_Node_destroy(thisObj->tail_, thisObj);
            if(errorCode == kapheinErrorCodeNoError) {
                if(prevOfTail != KAPHEIN_NULL) {
                   prevOfTail->next_ = KAPHEIN_NULL;
                }

                thisObj->tail_ = prevOfTail;

                if(thisObj->tail_ == KAPHEIN_NULL) {
                    thisObj->head_ = KAPHEIN_NULL;
                }

                --thisObj->count_;
            }
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_peekBack(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(kaphein_coll_List_isEmptyInl(thisObj)) {
        errorCode = kapheinErrorCodeCollectionUnderflow;
    }
    else {
        errorCode = kaphein_x_Node_copyElement(thisObj->tail_, thisObj, elementOut, elementSizeInOut);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_coll_List_clear(
    struct kaphein_coll_List * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        for(; !kaphein_coll_List_isEmptyInl(thisObj); ) {
            kaphein_coll_List_popFront(thisObj, KAPHEIN_NULL, KAPHEIN_NULL);
        }
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_Node_create(
    struct kaphein_x_Node ** thisObjOut
    , const struct kaphein_coll_List * list
    , const void * element
    , kaphein_SSize elementSize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(element == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(elementSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        struct kaphein_x_Node * node = (struct kaphein_x_Node *)kaphein_mem_allocate(
            list->allocator_
            , KAPHEIN_ssizeof(*node)
            , KAPHEIN_NULL
            , &errorCode
        );
        if(errorCode == kapheinErrorCodeNoError) {
            node->element_ = kaphein_mem_allocate(
                list->allocator_
                , elementSize
                , KAPHEIN_NULL
                , &errorCode
            );

            if(errorCode != kapheinErrorCodeNoError) {
                kaphein_mem_deallocate(list->allocator_, node, KAPHEIN_ssizeof(*node));
                node = KAPHEIN_NULL;
            }
            else {
                node->prev_ = KAPHEIN_NULL;
                node->next_ = KAPHEIN_NULL;
                node->elementSize_ = elementSize;
            
                if(list->elementTrait_ != KAPHEIN_NULL && list->elementTrait_->copyConstruct != KAPHEIN_NULL) {
                    (*list->elementTrait_->copyConstruct)(
                        node->element_
                        , element
                        , list->allocator_
                    );
                }
                else {
                    kaphein_mem_copy(node->element_, node->elementSize_, element, elementSize);
                }
            }
        }

        *thisObjOut = node;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_Node_destroy(
    struct kaphein_x_Node * thisObj
    , const struct kaphein_coll_List * list
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj->element_ != KAPHEIN_NULL) {
        if(list->elementTrait_ != KAPHEIN_NULL && list->elementTrait_->destruct != KAPHEIN_NULL) {
            errorCode = (*list->elementTrait_->destruct)(
                thisObj->element_
            );
        }

        errorCode = kaphein_mem_deallocate(
            list->allocator_
            , thisObj->element_
            , thisObj->elementSize_
        );
    }

    if(errorCode == kapheinErrorCodeNoError) {
        errorCode = kaphein_mem_deallocate(
            list->allocator_
            , thisObj
            , KAPHEIN_ssizeof(*thisObj)
        );
    }
    
    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_Node_copyElement(
    const struct kaphein_x_Node * thisObj
    , const struct kaphein_coll_List * list
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(elementSizeInOut != KAPHEIN_NULL && elementOut != KAPHEIN_NULL) {
            if(*elementSizeInOut < thisObj->elementSize_) {
                errorCode = kapheinErrorCodeArgumentOutOfRange;
            }
            else {
                *elementSizeInOut = thisObj->elementSize_;

                if(list->elementTrait_ != KAPHEIN_NULL && list->elementTrait_->copyConstruct != KAPHEIN_NULL) {
                    (*list->elementTrait_->copyConstruct)(
                        elementOut
                        , thisObj->element_
                        , list->allocator_
                    );
                }
                else {
                    kaphein_mem_copy(elementOut, *elementSizeInOut, thisObj->element_, thisObj->elementSize_);
                }
            }
        }
    }

    return errorCode;
}

/* ******************************** */
