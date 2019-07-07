#if defined(_DEBUG)
    #include <stdlib.h>
    #include <stdio.h>
#endif
#include "kaphein/mem/utils.h"
#include "kaphein/coll/List.h"
#include "kaphein/coll/TreeSet.h"

/* **************************************************************** */
/* TreeSet_Node */

struct TreeSet_Impl
{
    struct kaphein_mem_Allocator * allocator_;

    const struct kaphein_coll_ElementTrait * elementTrait_;

    struct TreeSet_Node * root_;

    kaphein_SSize elementCount_;
};

struct TreeSet_Node
{
    struct TreeSet_Node * parent_;
    
    void * element_;

    union
    {
        struct TreeSet_Node * children_[2];

        struct {
            struct TreeSet_Node * left_;

            struct TreeSet_Node * right_;
        } pair_;
    } child_;

    bool isRed_;
};

enum TreeSet_Node_RotationDirection
{
    rdLeft = 0
    , rdRight = 1
};

typedef
bool
TreeSet_Node_TraversalHandler(
    void *
    , struct TreeSet_Node *
);

static
const struct TreeSet_Node nilNode = {
    KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , false
};

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
TreeSet_Node_isNil(
    const struct TreeSet_Node * pNode
)
{
    return pNode->element_ == KAPHEIN_NULL;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
TreeSet_Node_isNullOrNil(
    const struct TreeSet_Node * pNode
)
{
    return pNode == KAPHEIN_NULL || TreeSet_Node_isNil(pNode);
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
TreeSet_Node_hasNonNilLeftChild(
    const struct TreeSet_Node * pNode
)
{
    return pNode->child_.pair_.left_ != KAPHEIN_NULL
        && !TreeSet_Node_isNil(pNode->child_.pair_.left_)
    ;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
TreeSet_Node_hasNonNilRightChild(
    const struct TreeSet_Node * pNode
)
{
    return pNode->child_.pair_.right_ != KAPHEIN_NULL
        && !TreeSet_Node_isNil(pNode->child_.pair_.right_)
    ;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
TreeSet_Node_isNonNilLeaf(
    const struct TreeSet_Node * pNode
)
{
    return !TreeSet_Node_hasNonNilLeftChild(pNode)
        && !TreeSet_Node_hasNonNilRightChild(pNode)
    ;
}

static
struct TreeSet_Node *
TreeSet_Node_getRoot(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pRoot;

    for(pRoot = pNode; pRoot->parent_ != KAPHEIN_NULL; pRoot = pRoot->parent_);

    return pRoot;
}

KAPHEIN_ATTRIBUTE_INLINE
static
struct TreeSet_Node *
TreeSet_Node_getTheOtherChild(
    struct TreeSet_Node * pParent
    , struct TreeSet_Node * pNode
)
{
    return (
        pParent != KAPHEIN_NULL
        ? (
            pNode == pParent->child_.pair_.left_
            ? pParent->child_.pair_.right_
            : pParent->child_.pair_.left_
        )
        : KAPHEIN_NULL
    );
}

KAPHEIN_ATTRIBUTE_INLINE
static
struct TreeSet_Node *
TreeSet_Node_getLastChild(
    struct TreeSet_Node * pNode
)
{
    return (
        !TreeSet_Node_isNullOrNil(pNode->child_.pair_.right_)
        ? pNode->child_.pair_.right_
        : pNode->child_.pair_.left_
    );
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
struct TreeSet_Node *
TreeSet_Node_getSibling(
    struct TreeSet_Node * pNode
)
{
    return TreeSet_Node_getTheOtherChild(pNode->parent_, pNode);
}

KAPHEIN_ATTRIBUTE_INLINE
static
struct TreeSet_Node **
TreeSet_Node_getChildSlot(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * const pParent = pNode->parent_;

    return (
        pParent != KAPHEIN_NULL
        ? (
            pNode == pParent->child_.pair_.left_
            ? &(pParent->child_.pair_.left_)
            : &(pParent->child_.pair_.right_)
        )
        : KAPHEIN_NULL
    );
}

struct TreeSet_Node *
TreeSet_Node_findLeftMost(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pCurrent;

    for(
        pCurrent = pNode;
        pCurrent != KAPHEIN_NULL && TreeSet_Node_hasNonNilLeftChild(pCurrent);
        pCurrent = pCurrent->child_.pair_.left_
    );

    return pCurrent;
}

struct TreeSet_Node *
TreeSet_Node_findRightMost(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pCurrent;

    for(
        pCurrent = pNode;
        pCurrent != KAPHEIN_NULL && TreeSet_Node_hasNonNilRightChild(pCurrent);
        pCurrent = pCurrent->child_.pair_.right_
    );

    return pCurrent;
}

static
struct TreeSet_Node *
TreeSet_Node_findLeftSubTreeRoot(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pCurrent = pNode;
    struct TreeSet_Node * pParent;

    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->parent_;
        if(pParent == KAPHEIN_NULL || pCurrent == pParent->child_.pair_.left_) {
            break;
        }

        pCurrent = pParent;
    }

    return pCurrent;
}

static
struct TreeSet_Node *
TreeSet_Node_findRightSubTreeRoot(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pCurrent = pNode;
    struct TreeSet_Node * pParent;

    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->parent_;
        if(pParent == KAPHEIN_NULL || pCurrent == pParent->child_.pair_.right_) {
            break;
        }

        pCurrent = pParent;
    }

    return pCurrent;
}

struct
TreeSet_Node *
TreeSet_Node_findLess(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pLess = KAPHEIN_NULL;
    struct TreeSet_Node * pRstRoot = KAPHEIN_NULL;
    
    if(TreeSet_Node_hasNonNilLeftChild(pNode)) {
        pLess = TreeSet_Node_findRightMost(pNode->child_.pair_.left_);
    }
    else {
        pRstRoot = TreeSet_Node_findRightSubTreeRoot(pNode);
        if(pRstRoot != KAPHEIN_NULL) {
            pLess = pRstRoot->parent_;
        }
    }

    return pLess;
}

struct
TreeSet_Node *
TreeSet_Node_findGreater(
    struct TreeSet_Node * pNode
)
{
    struct TreeSet_Node * pGreater = KAPHEIN_NULL;

    if(!TreeSet_Node_isNil(pNode->child_.pair_.right_)) {
        pGreater = TreeSet_Node_findLeftMost(pNode->child_.pair_.right_);
    }
    else if(pNode->parent_ != KAPHEIN_NULL) {
        if(pNode == pNode->parent_->child_.pair_.left_) {
            pGreater = pNode->parent_;
        }
        else {
            pGreater = TreeSet_Node_findLeftSubTreeRoot(pNode)->parent_;
        }
    }

    return pGreater;
}

static
int
TreeSet_Node_traverseByPostorder(
    struct TreeSet_Node * pNode
    , TreeSet_Node_TraversalHandler * pHandler
    , void * pContext
)
{
    struct TreeSet_Node * pCurrent;
    struct TreeSet_Node * pLastTraversed = KAPHEIN_NULL;
    struct kaphein_coll_List nodeStack;
    kaphein_UIntPtr listElement;
    kaphein_SSize listElementSize = 0;
    //int childCount;
    bool truth;
    bool stopTraversal = false;

    kaphein_coll_List_construct(&nodeStack, KAPHEIN_NULL, KAPHEIN_NULL);

    listElement = (kaphein_UIntPtr)pNode;
    kaphein_coll_List_pushBack(&nodeStack, &listElement, KAPHEIN_ssizeof(listElement));

    while(!stopTraversal && !(kaphein_coll_List_isEmpty(&nodeStack, &truth), truth)) {
        listElementSize = KAPHEIN_ssizeof(listElement);
        kaphein_coll_List_peekBack(&nodeStack, &listElement, &listElementSize);
        pCurrent = (struct TreeSet_Node *)listElement;
        
        //childCount = 0;
        if(
            !TreeSet_Node_isNonNilLeaf(pCurrent)
            && TreeSet_Node_getLastChild(pCurrent) != pLastTraversed
        ) {
            if(!TreeSet_Node_isNullOrNil(pCurrent->child_.pair_.right_)) {
                listElement = (kaphein_UIntPtr)pCurrent->child_.pair_.right_;
                kaphein_coll_List_pushBack(&nodeStack, &listElement, KAPHEIN_ssizeof(listElement));
                //++childCount;
            }

            if(!TreeSet_Node_isNullOrNil(pCurrent->child_.pair_.left_)) {
                listElement = (kaphein_UIntPtr)pCurrent->child_.pair_.left_;
                kaphein_coll_List_pushBack(&nodeStack, &listElement, KAPHEIN_ssizeof(listElement));
                //++childCount;
            }
        }
        else {
            stopTraversal = (*pHandler)(pContext, pCurrent);
            pLastTraversed = pCurrent;
            listElementSize = KAPHEIN_ssizeof(listElement);
            kaphein_coll_List_popBack(&nodeStack, &listElement, &listElementSize);
        }
    }

    kaphein_coll_List_destruct(&nodeStack);

    return stopTraversal;
}

static
void
TreeSet_Node_rotate(
    struct TreeSet_Node * pNode
    , enum TreeSet_Node_RotationDirection direction
)
{
    const int dirNdx = direction & 0x01;
    const int otherDirNdx = ~dirNdx & 0x01;
    struct TreeSet_Node ** pChildSlot = TreeSet_Node_getChildSlot(pNode);
    struct TreeSet_Node * const pParent = pNode->parent_;
    struct TreeSet_Node * const pLeftChildOfRightChild = pNode->child_.children_[otherDirNdx]->child_.children_[dirNdx];

    pNode->child_.children_[otherDirNdx]->child_.children_[dirNdx] = pNode;
    pNode->parent_ = pNode->child_.children_[otherDirNdx];

    pNode->child_.children_[otherDirNdx]->parent_ = pParent;
    if(pChildSlot != KAPHEIN_NULL) {
        *pChildSlot = pNode->child_.children_[otherDirNdx];
    }

    pNode->child_.children_[otherDirNdx] = pLeftChildOfRightChild;
    if(!TreeSet_Node_isNil(pLeftChildOfRightChild)) {
        pLeftChildOfRightChild->parent_ = pNode;
    }
}

/* **************************************************************** */

/* **************************************************************** */
/* kaphein_coll_TreeSet_Iterator */

static
const struct kaphein_coll_Iterator_VTable iteratorParentVTable = {
    kaphein_coll_TreeSet_Iterator_copyConstruct
    , kaphein_coll_TreeSet_Iterator_destruct
    , kaphein_coll_TreeSet_Iterator_copyAssign
    , KAPHEIN_NULL
    , kaphein_coll_TreeSet_Iterator_dereferenceConst
    , KAPHEIN_NULL
    , kaphein_coll_TreeSet_Iterator_hasReachedBegin
    , kaphein_coll_TreeSet_Iterator_hasReachedEnd
    , kaphein_coll_TreeSet_Iterator_reset
    , kaphein_coll_TreeSet_Iterator_moveToNext
    , kaphein_coll_TreeSet_Iterator_moveToPrevious
    , KAPHEIN_NULL
};

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_copyConstruct(
    void * thisObj
    , const void * src
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    KAPHEIN_x_UNUSED_PARAMETER(allocator)

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == src
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;
        struct kaphein_coll_TreeSet_Iterator *const srcPtr = (struct kaphein_coll_TreeSet_Iterator *)src;

        srcPtr->parent.thisObj = srcPtr;
        srcPtr->parent.vTable = thisPtr->parent.vTable;
        srcPtr->treeSet_ = thisPtr->treeSet_;
        srcPtr->currentNode_ = thisPtr->currentNode_;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_destruct(
    void * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;

        thisPtr->treeSet_ = KAPHEIN_NULL;
        thisPtr->currentNode_ = KAPHEIN_NULL;
        thisPtr->parent.thisObj = KAPHEIN_NULL;
        thisPtr->parent.vTable = KAPHEIN_NULL;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_copyAssign(
    void * thisObj
    , const void * src
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;

        //TODO : 内靛 累己
    }

    return resultErrorCode;
}

const void *
kaphein_coll_TreeSet_Iterator_dereferenceConst(
    const void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const void * element = KAPHEIN_NULL;

    if(KAPHEIN_NULL == thisObj ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct kaphein_coll_TreeSet_Iterator *const thisPtr = (const struct kaphein_coll_TreeSet_Iterator *)thisObj;
        
        if(KAPHEIN_NULL == thisPtr->treeSet_) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            const struct TreeSet_Node *const node = (const struct TreeSet_Node *)thisPtr->currentNode_;

            if(KAPHEIN_NULL == node) {
                resultErrorCode = kapheinErrorCodeOperationInvalid;
            }
            else {
                element = node->element_;
            }
        }
    }

    if(KAPHEIN_NULL != errorCodeOut) {
        *errorCodeOut = resultErrorCode;
    }

    return element;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_hasReachedBegin(
    const void * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;

        //TODO : 内靛 累己
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_hasReachedEnd(
    const void * thisObj
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
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;

        *truthOut = KAPHEIN_NULL != thisPtr->treeSet_
            && KAPHEIN_NULL == thisPtr->currentNode_
        ;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_reset(
    void * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;
        
        if(KAPHEIN_NULL == thisPtr->treeSet_) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisPtr->treeSet_->impl_;

            if(KAPHEIN_NULL == impl) {
                resultErrorCode = kapheinErrorCodeOperationInvalid;
            }
            else {
                thisPtr->currentNode_ = (const void *)TreeSet_Node_findLeftMost(impl->root_);
            }
        }
    }

    return resultErrorCode;
}

bool
kaphein_coll_TreeSet_Iterator_moveToNext(
    void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    bool hasReachedEnd = false;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;
        
        if(KAPHEIN_NULL != thisPtr->currentNode_) {
            thisPtr->currentNode_ = (const void *)TreeSet_Node_findGreater((struct TreeSet_Node *)((void *)thisPtr->currentNode_));
        }
    }

    if(KAPHEIN_NULL != errorCodeOut) {
        *errorCodeOut = resultErrorCode;
    }

    return hasReachedEnd;
}

bool
kaphein_coll_TreeSet_Iterator_moveToPrevious(
    void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    bool hasReachedBegin = false;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct kaphein_coll_TreeSet_Iterator *const thisPtr = (struct kaphein_coll_TreeSet_Iterator *)thisObj;
        
        if(KAPHEIN_NULL == thisPtr->currentNode_) {
            thisPtr->currentNode_ = (const void *)TreeSet_Node_findRightMost((struct TreeSet_Node *)((void *)thisPtr->currentNode_));
        }
        else {
            thisPtr->currentNode_ = (const void *)TreeSet_Node_findLess((struct TreeSet_Node *)((void *)thisPtr->currentNode_));
        }
    }

    if(KAPHEIN_NULL != errorCodeOut) {
        *errorCodeOut = resultErrorCode;
    }

    return hasReachedBegin;
}

/* **************************************************************** */

/* **************************************************************** */
/* TreeSet_Impl */

enum TreeSet_Impl_SearchTarget
{
    stNotGreater = 0
    , stLess
    , stNotLess
    , stGreater
    , stEqual
};

static
bool
TreeSet_Impl_removeAllHandler(
    void * pContext
    , struct TreeSet_Node * pNode
)
{
    const kaphein_UIntPtr listElement = (kaphein_UIntPtr)pNode;
    
    kaphein_coll_List_pushBack((struct kaphein_coll_List *)pContext, &listElement, KAPHEIN_ssizeof(listElement));

    return false;
}

static
struct TreeSet_Node *
TreeSet_Impl_createNode(
    const struct TreeSet_Impl * impl
    , struct TreeSet_Node * pParent
    , const void * srcElement
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    struct TreeSet_Node * newNode = (struct TreeSet_Node *)kaphein_mem_allocate(
        impl->allocator_
        , KAPHEIN_ssizeof(*newNode)
        , KAPHEIN_NULL
        , &resultErrorCode
    );
    void * element = KAPHEIN_NULL;

    if(KAPHEIN_NULL != newNode) {
        element = kaphein_mem_allocate(
            impl->allocator_
            , impl->elementTrait_->elementSize
            , KAPHEIN_NULL
            , &resultErrorCode
        );
        
        if(kapheinErrorCodeNoError == resultErrorCode) {
            resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                element
                , srcElement
                , impl->allocator_
            );

            if(kapheinErrorCodeNoError != resultErrorCode) {
                kaphein_mem_deallocate(impl->allocator_, element, impl->elementTrait_->elementSize);
                kaphein_mem_deallocate(impl->allocator_, newNode, KAPHEIN_ssizeof(*newNode));
                
                newNode = KAPHEIN_NULL;
            }
            else {
                newNode->element_ = element;
                newNode->parent_ = pParent;
                newNode->child_.pair_.left_ = (struct TreeSet_Node *)&nilNode;
                newNode->child_.pair_.right_ = (struct TreeSet_Node *)&nilNode;
                newNode->isRed_ = true;
            }
        }
    }

    if(KAPHEIN_NULL != errorCodeOut) {
        *errorCodeOut = resultErrorCode;
    }

    return newNode;
}

static
enum kaphein_ErrorCode
TreeSet_Impl_destroyNode(
    struct TreeSet_Impl * impl
    , struct TreeSet_Node * node
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(KAPHEIN_NULL != node->element_) {
        resultErrorCode = (*impl->elementTrait_->destruct)(node->element_);

        if(kapheinErrorCodeNoError == resultErrorCode) {
            resultErrorCode = kaphein_mem_deallocate(
                impl->allocator_
                , node->element_
                , impl->elementTrait_->elementSize
            );
        }
    }

    if(kapheinErrorCodeNoError == resultErrorCode) {
        resultErrorCode = kaphein_mem_deallocate(impl->allocator_, node, KAPHEIN_ssizeof(*node));
    }

    return resultErrorCode;
}

static
struct TreeSet_Node *
TreeSet_Impl_findNode(
    const struct TreeSet_Impl * impl
    , const void * element
    , enum TreeSet_Impl_SearchTarget searchTarget
)
{
    struct TreeSet_Node * pPrevious = KAPHEIN_NULL;
    struct TreeSet_Node * pCurrent = impl->root_;
    int cmpResult;
    bool isNodeFound = false;

    while(!isNodeFound && !TreeSet_Node_isNullOrNil(pCurrent)) {
        cmpResult = (*impl->elementTrait_->compare)(element, pCurrent->element_);
        if(cmpResult < 0) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->child_.pair_.left_;
        }
        else if(cmpResult > 0) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->child_.pair_.right_;
        }
        else {
            isNodeFound = true;
        }
    }

    switch(searchTarget) {
    case stNotGreater:
        if(!TreeSet_Node_isNullOrNil(pCurrent)) {
            break;
        }

    case stLess:
        if(TreeSet_Node_isNullOrNil(pCurrent)) {
            pCurrent = pPrevious;
        }
        
        while(
            !TreeSet_Node_isNullOrNil(pCurrent)
            && (*impl->elementTrait_->compare)(pCurrent->element_, element) >= 0
        ) {
            pCurrent = TreeSet_Node_findLess(pCurrent);
        }
    break;
    case stNotLess:
        if(!TreeSet_Node_isNullOrNil(pCurrent)) {
            break;
        }

    case stGreater:
        if(TreeSet_Node_isNullOrNil(pCurrent)) {
            pCurrent = pPrevious;
        }
        
        while(
            !TreeSet_Node_isNullOrNil(pCurrent)
            && (*impl->elementTrait_->compare)(element, pCurrent->element_) >= 0
        ) {
            pCurrent = TreeSet_Node_findGreater(pCurrent);
        }
    break;
    case stEqual:
    default:
        pCurrent = (
            (pCurrent != KAPHEIN_NULL && !TreeSet_Node_isNil(pCurrent))
            ? pCurrent
            : KAPHEIN_NULL
        );
    }

    return pCurrent;
}

static
struct TreeSet_Node *
TreeSet_Impl_insertNodeInBst(
    struct TreeSet_Impl * impl
    , const void * element
    , enum kaphein_ErrorCode * errorCodeOut
)
{
    struct TreeSet_Node * newNode = KAPHEIN_NULL;

    if(KAPHEIN_NULL == impl->root_) {
        newNode = TreeSet_Impl_createNode(impl, KAPHEIN_NULL, element, errorCodeOut);
        impl->root_ = newNode;
    }
    else {
        struct TreeSet_Node * pCurrent;
        
        for(
            pCurrent = impl->root_;
            !TreeSet_Node_isNil(pCurrent);
        ) {
            const int cmpResult = (*impl->elementTrait_->compare)(element, pCurrent->element_);

            if(cmpResult < 0) {
                if(TreeSet_Node_isNil(pCurrent->child_.pair_.left_)) {
                    newNode = TreeSet_Impl_createNode(impl, pCurrent, element, errorCodeOut);
                    pCurrent->child_.pair_.left_ = newNode;
                        
                    pCurrent = (struct TreeSet_Node *)&nilNode;
                }
                else {
                    pCurrent = pCurrent->child_.pair_.left_;
                }
            }
            else if(cmpResult > 0) {
                if(TreeSet_Node_isNil(pCurrent->child_.pair_.right_)) {
                    newNode = TreeSet_Impl_createNode(impl, pCurrent, element, errorCodeOut);
                    pCurrent->child_.pair_.right_ = newNode;
                
                    pCurrent = (struct TreeSet_Node *)&nilNode;
                }
                else {
                    pCurrent = pCurrent->child_.pair_.right_;
                }
            }
            else {
                pCurrent = (struct TreeSet_Node *)&nilNode;
            }
        }
    }

    return newNode;
}

static
void
TreeSet_Impl_rebalanceAfterInsertion(
    struct TreeSet_Impl * impl
    , struct TreeSet_Node * pTarget
)
{
    struct TreeSet_Node * pParent;
    struct TreeSet_Node * pUncle;
    struct TreeSet_Node * pGrandParent;
    struct TreeSet_Node * pCurrent = pTarget;

    while(KAPHEIN_NULL != pCurrent) {
        pParent = pCurrent->parent_;
        if(KAPHEIN_NULL == pParent) {
            pCurrent->isRed_ = false;

            pCurrent = KAPHEIN_NULL;
        }
        else if(pParent->isRed_) {
            pGrandParent = pParent->parent_;
            pUncle = TreeSet_Node_getTheOtherChild(pGrandParent, pParent);
            if(KAPHEIN_NULL != pUncle && pUncle->isRed_) {
                pUncle->isRed_ = false;
                pParent->isRed_ = false;
                
                pCurrent = pGrandParent;
                if(KAPHEIN_NULL != pCurrent) {
                    pCurrent->isRed_ = true;
                }
            }
            else {
                if(
                    pCurrent == pParent->child_.pair_.right_
                    && pParent == pGrandParent->child_.pair_.left_
                ) {
                    TreeSet_Node_rotate(pParent, rdLeft);
                    pCurrent = pCurrent->child_.pair_.left_;
                }
                else if(
                    pCurrent == pParent->child_.pair_.left_
                    && pParent == pGrandParent->child_.pair_.right_
                ) {
                    TreeSet_Node_rotate(pParent, rdRight);
                    pCurrent = pCurrent->child_.pair_.right_;
                }
                
                pParent = pCurrent->parent_;
                pParent->isRed_ = false;
                pGrandParent->isRed_ = true;
                TreeSet_Node_rotate(
                    pGrandParent,
                    (enum TreeSet_Node_RotationDirection)(pCurrent == pParent->child_.pair_.left_)
                );

                pCurrent = pGrandParent;
                pParent = pGrandParent->parent_;
                if(KAPHEIN_NULL == pParent->parent_) {
                    impl->root_ = pParent;
                }

                pCurrent = KAPHEIN_NULL;
            }
        }
        else {
            pCurrent = KAPHEIN_NULL;
        }
    }
}

static
void
TreeSet_Impl_rebalanceAfterRemoval(
    struct TreeSet_Impl * impl
    , struct TreeSet_Node * pReplacement
)
{
    struct TreeSet_Node * pSibling;
    struct TreeSet_Node * pParent;
    struct TreeSet_Node * pCurrent = pReplacement;
    
    while(KAPHEIN_NULL != pCurrent) {
        pParent = pCurrent->parent_;
        if(KAPHEIN_NULL == pParent) {
            impl->root_ = pCurrent;

            pCurrent = KAPHEIN_NULL;
        }
        else {
            pSibling = TreeSet_Node_getSibling(pCurrent);
            if(pSibling->isRed_) {
                pParent->isRed_ = true;
                pSibling->isRed_ = false;

                TreeSet_Node_rotate(
                    pParent,
                    (enum TreeSet_Node_RotationDirection)(pCurrent != pParent->child_.pair_.left_)
                );
                if(KAPHEIN_NULL == pSibling->parent_) {
                    impl->root_ = pSibling;
                }

                pSibling = TreeSet_Node_getSibling(pCurrent);
            }

            if(!pSibling->isRed_) {
                const int caseNumber = (pSibling->child_.pair_.right_->isRed_ ? 0x02 : 0x00)
                    | (pSibling->child_.pair_.left_->isRed_ ? 0x01 : 0x00)
                ;

                if(caseNumber == 0) {
                    if(!pParent->isRed_) {
                        pSibling->isRed_ = true;

                        pCurrent = pParent;
                    }
                    else {
                        pSibling->isRed_ = true;
                        pParent->isRed_ = false;

                        pCurrent = KAPHEIN_NULL;
                    }
                }
                else {
                    switch(caseNumber) {
                    case 0:
                    break;
                    case 1:
                        if(pCurrent == pParent->child_.pair_.left_) {
                            pSibling->isRed_ = true;
                            pSibling->child_.pair_.left_->isRed_ = false;
                            TreeSet_Node_rotate(pSibling, rdRight);

                            pSibling = TreeSet_Node_getSibling(pCurrent);
                        }
                    break;
                    case 2:
                        if(pCurrent == pParent->child_.pair_.right_) {
                            pSibling->isRed_ = true;
                            pSibling->child_.pair_.right_->isRed_ = false;
                            TreeSet_Node_rotate(pSibling, rdLeft);
                            
                            pSibling = TreeSet_Node_getSibling(pCurrent);
                        }
                    break;
                    case 3:
                    break;
                    }

                    if(!pSibling->isRed_) {
                        const int childNdx = (pCurrent != pParent->child_.pair_.left_ ? 1 : 0);

                        pSibling->isRed_ = pParent->isRed_;
                        pParent->isRed_ = false;
                        
                        pSibling->child_.children_[~childNdx & 0x01]->isRed_ = false;
                        TreeSet_Node_rotate(pParent, (enum TreeSet_Node_RotationDirection)childNdx);
                        if(KAPHEIN_NULL == pSibling->parent_) {
                            impl->root_ = pSibling;
                        }
                    }

                    pCurrent = KAPHEIN_NULL;
                }
            }
            else {
                pCurrent = KAPHEIN_NULL;
            }
        }
    }
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_construct(
    struct kaphein_coll_TreeSet * thisObj
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
    else {
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)kaphein_mem_allocate(
            allocator
            , KAPHEIN_ssizeof(*impl)
            , KAPHEIN_NULL
            , &resultErrorCode
        );

        if(kapheinErrorCodeNoError == resultErrorCode) {
            impl->allocator_ = allocator;
            impl->elementTrait_ = elementTrait;
            impl->root_ = KAPHEIN_NULL;
            impl->elementCount_ = 0;
            thisObj->impl_ = impl;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_destruct(
    struct kaphein_coll_TreeSet * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisObj->impl_;
        
        if(KAPHEIN_NULL == impl) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            resultErrorCode = kaphein_coll_TreeSet_clear(thisObj);

            if(kapheinErrorCodeNoError == resultErrorCode) {
                resultErrorCode = kaphein_mem_deallocate(
                    impl->allocator_
                    , impl
                    , KAPHEIN_ssizeof(*impl)
                );

                if(kapheinErrorCodeNoError == resultErrorCode) {
                    thisObj->impl_ = KAPHEIN_NULL;
                }
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_getCount(
    const struct kaphein_coll_TreeSet * thisObj
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
        const struct TreeSet_Impl *const impl = (const struct TreeSet_Impl *)thisObj->impl_;

        *countOut = impl->elementCount_;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_isEmpty(
    const struct kaphein_coll_TreeSet * thisObj
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
        const struct TreeSet_Impl *const impl = (const struct TreeSet_Impl *)thisObj->impl_;

        *truthOut = impl->elementCount_ < 1;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_getBeginConstIterator(
    const struct kaphein_coll_TreeSet * thisObj
    , struct kaphein_coll_TreeSet_Iterator * iterOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == iterOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct TreeSet_Impl *const impl = (const struct TreeSet_Impl *)thisObj->impl_;

        iterOut->parent.thisObj = iterOut;
        iterOut->parent.vTable = &iteratorParentVTable;
        iterOut->treeSet_ = thisObj;
        iterOut->currentNode_ = (const void *)TreeSet_Node_findLeftMost((struct TreeSet_Node *)impl->root_);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_has(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * element
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
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisObj->impl_;

        if(KAPHEIN_NULL == impl) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            *truthOut = KAPHEIN_NULL != TreeSet_Impl_findNode(impl, element, stEqual);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_add(
    struct kaphein_coll_TreeSet * thisObj
    , const void * element
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == element
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisObj->impl_;
        struct TreeSet_Node *const newNode = TreeSet_Impl_insertNodeInBst(impl, element, &resultErrorCode);
        
        if(
            kapheinErrorCodeNoError == resultErrorCode
            && KAPHEIN_NULL != newNode
        ) {
            TreeSet_Impl_rebalanceAfterInsertion(impl, newNode);
            ++impl->elementCount_;

            //TODO : Figure out why i wrote this line...
            //impl->root_ = TreeSet_Node_getRoot(impl->root_);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_remove(
    struct kaphein_coll_TreeSet * thisObj
    , const void * element
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == element
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisObj->impl_;
        struct TreeSet_Node * removedNode = TreeSet_Impl_findNode(impl, element, stEqual);

        if(KAPHEIN_NULL == removedNode) {
            resultErrorCode = kapheinErrorCodeNoSuchElement;
        }
        else {
            struct TreeSet_Node ** pChildSlot;
            struct TreeSet_Node * pMaxOfLeftSubTree;
            struct TreeSet_Node * pChildOfRemoved = KAPHEIN_NULL;
            bool isRemovedNodeRed;
            bool isLooping = true;

            while(isLooping) {
                const int caseNumber = (TreeSet_Node_isNullOrNil(removedNode->child_.pair_.right_) ? 0x01 : 0x00)
                    | (TreeSet_Node_isNullOrNil(removedNode->child_.pair_.left_) ? 0x02 : 0x00)
                ;
                switch(caseNumber) {
                //Has two non-nil children.
                case 0:
                    pMaxOfLeftSubTree = TreeSet_Node_findRightMost(removedNode->child_.pair_.left_);
                    
                    resultErrorCode = (*impl->elementTrait_->destruct)(removedNode->element_);
                    resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                        removedNode->element_
                        , pMaxOfLeftSubTree->element_
                        , impl->allocator_
                    );

                    if(kapheinErrorCodeNoError == resultErrorCode) {
                        removedNode = pMaxOfLeftSubTree;
                    }
                    else {
                        isLooping = false;
                    }
                break;
                //Has a non-nil left child.
                case 1:
                //Has a non-nil right child.
                case 2:
                    pChildOfRemoved = removedNode->child_.children_[caseNumber - 1];
                    pChildOfRemoved->parent_ = removedNode->parent_;

                    pChildSlot = TreeSet_Node_getChildSlot(removedNode);
                    if(pChildSlot != KAPHEIN_NULL) {
                        *pChildSlot = pChildOfRemoved;
                    }
                
                    if(!removedNode->isRed_) {
                        if(pChildOfRemoved->isRed_) {
                            pChildOfRemoved->isRed_ = false;

                            impl->root_ = TreeSet_Node_getRoot(pChildOfRemoved);
                        }
                        else {
                            TreeSet_Impl_rebalanceAfterRemoval(impl, pChildOfRemoved);
                        }
                    }
                    else {
                        impl->root_ = TreeSet_Node_getRoot(pChildOfRemoved);
                    }

                    isLooping = false;
                break;
                //Has no non-nil children.
                case 3:
                    isRemovedNodeRed = removedNode->isRed_;
                    if(!isRemovedNodeRed) {
                        TreeSet_Impl_rebalanceAfterRemoval(impl, removedNode);
                    }
                    
                    pChildSlot = TreeSet_Node_getChildSlot(removedNode);
                    if(pChildSlot != KAPHEIN_NULL) {
                        *pChildSlot = (struct TreeSet_Node *)&nilNode;
                        impl->root_ = TreeSet_Node_getRoot(removedNode->parent_);
                    }
                    else {
                        impl->root_ = KAPHEIN_NULL;
                    }

                    isLooping = false;
                break;
                }
            }

            if(kapheinErrorCodeNoError == resultErrorCode) {
                --impl->elementCount_;

                resultErrorCode = TreeSet_Impl_destroyNode(impl, removedNode);
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_clear(
    struct kaphein_coll_TreeSet * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct TreeSet_Impl *const impl = (struct TreeSet_Impl *)thisObj->impl_;
        struct kaphein_coll_List nodeStack;
        kaphein_UIntPtr listElement;
        kaphein_SSize listElementSize;
        bool truth;

        if(KAPHEIN_NULL != impl->root_) {
            kaphein_coll_List_construct(&nodeStack, KAPHEIN_NULL, KAPHEIN_NULL);

            TreeSet_Node_traverseByPostorder(
                impl->root_
                , TreeSet_Impl_removeAllHandler
                , (void *)&nodeStack
            );

            while(
                kapheinErrorCodeNoError == resultErrorCode
                && !(kaphein_coll_List_isEmpty(&nodeStack, &truth), truth)
            ) {
                listElementSize = KAPHEIN_ssizeof(listElement);
                kaphein_coll_List_popBack(&nodeStack, &listElement, &listElementSize);

                resultErrorCode = TreeSet_Impl_destroyNode(impl, (struct TreeSet_Node *)((void *)listElement));
            }

            kaphein_coll_List_destruct(&nodeStack);

            if(resultErrorCode == kapheinErrorCodeNoError) {
                impl->root_ = KAPHEIN_NULL;
                impl->elementCount_ = 0;
            }
        }

        #ifdef _DEBUG
        if(KAPHEIN_NULL == impl->root_ && impl->elementCount_ > 0) {
            system("pause");
        }
        #endif
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_TreeSet_toArray(
    const struct kaphein_coll_TreeSet * thisObj
    , void * elementsOut
    , kaphein_SSize elementsOutSize
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == elementsOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct TreeSet_Impl *const impl = (const struct TreeSet_Impl *)thisObj->impl_;

        if(KAPHEIN_NULL == impl) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
        else if(elementsOutSize < impl->elementTrait_->elementSize * impl->elementCount_) {
            resultErrorCode = kapheinErrorCodeNotEnoughBufferSpace;
        }
        else {
            struct TreeSet_Node * pCurrent;
            char * dest = (char *)elementsOut;
            kaphein_SSize i;
            
            for(
                pCurrent = TreeSet_Node_findLeftMost(impl->root_), i = impl->elementCount_;
                kapheinErrorCodeNoError == resultErrorCode && KAPHEIN_NULL != pCurrent && i > 0;
                dest += impl->elementTrait_->elementSize, pCurrent = TreeSet_Node_findGreater(pCurrent)
            ) {
                --i;

                resultErrorCode = (*impl->elementTrait_->copyConstruct)(
                    dest
                    , pCurrent->element_
                    , impl->allocator_
                );
            }
        }
    }

    return resultErrorCode;
}

/* **************************************************************** */
