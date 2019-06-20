#ifdef _DEBUG
    #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include "kaphein/coll/List.h"
#include "kaphein/coll/TreeSet.h"

typedef bool (* NodeTraversalHandlerPtr) (
    void *
    , struct RbTreeNode *
);

enum RotationDirection
{
    rdLeft = 0
    , rdRight = 1
};

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static bool RbTreeNode_isNil(
    const struct RbTreeNode * pNode
)
{
    return pNode->pElement_ == KAPHEIN_NULL;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static bool RbTreeNode_isNullOrNil(
    const struct RbTreeNode * pNode
)
{
    return pNode == KAPHEIN_NULL || RbTreeNode_isNil(pNode);
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static bool RbTreeNode_hasNonNilLeftChild(
    const struct RbTreeNode * pNode
)
{
    return pNode->child_.pair_.pLeft_ != KAPHEIN_NULL
        && !RbTreeNode_isNil(pNode->child_.pair_.pLeft_)
    ;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static bool RbTreeNode_hasNonNilRightChild(
    const struct RbTreeNode * pNode
)
{
    return pNode->child_.pair_.pRight_ != KAPHEIN_NULL
        && !RbTreeNode_isNil(pNode->child_.pair_.pRight_)
    ;
}

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static bool RbTreeNode_isNonNilLeaf(
    const struct RbTreeNode * pNode
)
{
    return !RbTreeNode_hasNonNilLeftChild(pNode)
        && !RbTreeNode_hasNonNilRightChild(pNode)
    ;
}

static struct RbTreeNode * RbTreeNode_getRoot(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pRoot = pNode;
    for(; pRoot->pParent_ != KAPHEIN_NULL; pRoot = pRoot->pParent_);

    return pRoot;
}

KAPHEIN_ATTRIBUTE_INLINE
static struct RbTreeNode * RbTreeNode_getTheOtherChild(
    struct RbTreeNode * pParent,
    struct RbTreeNode * pNode
)
{
    return (
        pParent != KAPHEIN_NULL
        ? (
            pNode == pParent->child_.pair_.pLeft_
            ? pParent->child_.pair_.pRight_
            : pParent->child_.pair_.pLeft_
        )
        : KAPHEIN_NULL
    );
}

KAPHEIN_ATTRIBUTE_INLINE
static struct RbTreeNode * RbTreeNode_getLastChild(
    struct RbTreeNode * pNode
)
{
    return (
        !RbTreeNode_isNullOrNil(pNode->child_.pair_.pRight_)
        ? pNode->child_.pair_.pRight_
        : pNode->child_.pair_.pLeft_
    );
}

KAPHEIN_ATTRIBUTE_INLINE
static struct RbTreeNode * RbTreeNode_getSibling(
    struct RbTreeNode * pNode
)
{
    return RbTreeNode_getTheOtherChild(pNode->pParent_, pNode);
}

KAPHEIN_ATTRIBUTE_INLINE
static struct RbTreeNode ** RbTreeNode_getChildSlot(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * const pParent = pNode->pParent_;
    return (
        pParent != KAPHEIN_NULL
        ? (
            pNode == pParent->child_.pair_.pLeft_
            ? &(pParent->child_.pair_.pLeft_)
            : &(pParent->child_.pair_.pRight_)
        )
        : KAPHEIN_NULL
    );
}

struct RbTreeNode * RbTreeNode_findLeftMost(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pCurrent = pNode;
    for(
        ;
        pCurrent != KAPHEIN_NULL && RbTreeNode_hasNonNilLeftChild(pCurrent);
        pCurrent = pCurrent->child_.pair_.pLeft_
    );

    return pCurrent;
}

struct RbTreeNode * RbTreeNode_findRightMost(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pCurrent = pNode;
    for(
        ;
        pCurrent != KAPHEIN_NULL && RbTreeNode_hasNonNilRightChild(pCurrent);
        pCurrent = pCurrent->child_.pair_.pRight_
    );

    return pCurrent;
}

static struct RbTreeNode * RbTreeNode_findLeftSubTreeRoot(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pCurrent = pNode;
    struct RbTreeNode * pParent;
    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->pParent_;
        if(pParent == KAPHEIN_NULL || pCurrent == pParent->child_.pair_.pLeft_) {
            break;
        }

        pCurrent = pParent;
    }

    return pCurrent;
}

static struct RbTreeNode * RbTreeNode_findRightSubTreeRoot(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pCurrent = pNode;
    struct RbTreeNode * pParent;
    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->pParent_;
        if(pParent == KAPHEIN_NULL || pCurrent == pParent->child_.pair_.pRight_) {
            break;
        }

        pCurrent = pParent;
    }

    return pCurrent;
}

struct RbTreeNode * RbTreeNode_findLess(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pLess = KAPHEIN_NULL;
    struct RbTreeNode * pRstRoot = KAPHEIN_NULL;
    
    if(RbTreeNode_hasNonNilLeftChild(pNode)) {
        pLess = RbTreeNode_findRightMost(pNode->child_.pair_.pLeft_);
    }
    else {
        pRstRoot = RbTreeNode_findRightSubTreeRoot(pNode);
        if(pRstRoot != KAPHEIN_NULL) {
            pLess = pRstRoot->pParent_;
        }
    }

    return pLess;
}

struct RbTreeNode * RbTreeNode_findGreater(
    struct RbTreeNode * pNode
)
{
    struct RbTreeNode * pGreater = KAPHEIN_NULL;

    if(!RbTreeNode_isNil(pNode->child_.pair_.pRight_)) {
        pGreater = RbTreeNode_findLeftMost(pNode->child_.pair_.pRight_);
    }
    else if(pNode->pParent_ != KAPHEIN_NULL) {
        if(pNode == pNode->pParent_->child_.pair_.pLeft_) {
            pGreater = pNode->pParent_;
        }
        else {
            pGreater = RbTreeNode_findLeftSubTreeRoot(pNode)->pParent_;
        }
    }

    return pGreater;
}

static int RbTreeNode_traverseByPostorder(
    struct RbTreeNode * pNode,
    NodeTraversalHandlerPtr pHandler,
    void* pContext
)
{
    struct RbTreeNode * pCurrent;
    struct RbTreeNode * pLastTraversed = KAPHEIN_NULL;
    struct kaphein_coll_List nodeStack;
    bool truth;
    bool stopTraversal = false;
    //int childCount;
    kaphein_UIntPtr listElement;
    kaphein_SSize listElementSize = 0;

    kaphein_coll_List_construct(&nodeStack, KAPHEIN_NULL, KAPHEIN_NULL);

    listElement = (kaphein_UIntPtr)pNode;
    kaphein_coll_List_pushBack(&nodeStack, &listElement, KAPHEIN_ssizeof(listElement));

    while(!stopTraversal && !(kaphein_coll_List_isEmpty(&nodeStack, &truth), truth)) {
        listElementSize = KAPHEIN_ssizeof(listElement);
        kaphein_coll_List_peekBack(&nodeStack, &listElement, &listElementSize);
        pCurrent = (struct RbTreeNode *)listElement;
        
        //childCount = 0;
        if(
            !RbTreeNode_isNonNilLeaf(pCurrent)
            && RbTreeNode_getLastChild(pCurrent) != pLastTraversed
        ) {
            if(!RbTreeNode_isNullOrNil(pCurrent->child_.pair_.pRight_)) {
                listElement = (kaphein_UIntPtr)pCurrent->child_.pair_.pRight_;
                kaphein_coll_List_pushBack(&nodeStack, &listElement, KAPHEIN_ssizeof(listElement));
                //++childCount;
            }

            if(!RbTreeNode_isNullOrNil(pCurrent->child_.pair_.pLeft_)) {
                listElement = (kaphein_UIntPtr)pCurrent->child_.pair_.pLeft_;
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

static void RbTreeNode_rotate(
    struct RbTreeNode * pNode,
    enum RotationDirection direction
)
{
    const int dirNdx = direction & 0x01;
    const int otherDirNdx = ~dirNdx & 0x01;
    struct RbTreeNode ** pChildSlot = RbTreeNode_getChildSlot(pNode);
    struct RbTreeNode * const pParent = pNode->pParent_;
    struct RbTreeNode * const pLeftChildOfRightChild = pNode->child_.ptrs_[otherDirNdx]->child_.ptrs_[dirNdx];

    pNode->child_.ptrs_[otherDirNdx]->child_.ptrs_[dirNdx] = pNode;
    pNode->pParent_ = pNode->child_.ptrs_[otherDirNdx];

    pNode->child_.ptrs_[otherDirNdx]->pParent_ = pParent;
    if(pChildSlot != KAPHEIN_NULL) {
        *pChildSlot = pNode->child_.ptrs_[otherDirNdx];
    }

    pNode->child_.ptrs_[otherDirNdx] = pLeftChildOfRightChild;
    if(!RbTreeNode_isNil(pLeftChildOfRightChild)) {
        pLeftChildOfRightChild->pParent_ = pNode;
    }
}

static const struct RbTreeNode nilNode = {
    KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , 0
};

static struct RbTreeNode * kaphein_coll_TreeSet_createNode(
    struct RbTreeNode * pParent,
    const void * pElement
)
{
    struct RbTreeNode * const newNode = (struct RbTreeNode *)malloc(sizeof(struct RbTreeNode));
    if(newNode != KAPHEIN_NULL) {
        newNode->pElement_ = pElement;
        newNode->pParent_ = pParent;
        newNode->child_.pair_.pLeft_ = (struct RbTreeNode *)&nilNode;
        newNode->child_.pair_.pRight_ = (struct RbTreeNode *)&nilNode;
        newNode->red_ = 1;
    }

    return newNode;
}

static struct RbTreeNode * kaphein_coll_TreeSet_findNode(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
    , enum SearchTarget searchTarget
)
{
    struct RbTreeNode * pPrevious = KAPHEIN_NULL;
    struct RbTreeNode * pCurrent = thisObj->pRoot_;
    int cmpResult;
    int found = 0;

    while(!found && !RbTreeNode_isNullOrNil(pCurrent)) {
        cmpResult = (*thisObj->pComparator_)(pElement, pCurrent->pElement_);
        if(cmpResult < 0) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->child_.pair_.pLeft_;
        }
        else if(cmpResult > 0) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->child_.pair_.pRight_;
        }
        else {
            found = 1;
        }
    }

    switch(searchTarget) {
    case stNotGreater:
        if(!RbTreeNode_isNullOrNil(pCurrent)) {
            break;
        }

    case stLess:
        if(RbTreeNode_isNullOrNil(pCurrent)) {
            pCurrent = pPrevious;
        }
        
        while(
            !RbTreeNode_isNullOrNil(pCurrent)
            && (*thisObj->pComparator_)(pCurrent->pElement_, pElement) >= 0
        ) {
            pCurrent = RbTreeNode_findLess(pCurrent);
        }
    break;
    case stNotLess:
        if(!RbTreeNode_isNullOrNil(pCurrent)) {
            break;
        }

    case stGreater:
        if(RbTreeNode_isNullOrNil(pCurrent)) {
            pCurrent = pPrevious;
        }
        
        while(
            !RbTreeNode_isNullOrNil(pCurrent)
            && (*thisObj->pComparator_)(pElement, pCurrent->pElement_) >= 0
        ) {
            pCurrent = RbTreeNode_findGreater(pCurrent);
        }
    break;
    case stEqual:
    default:
        pCurrent = (
            (pCurrent != KAPHEIN_NULL && !RbTreeNode_isNil(pCurrent))
            ? pCurrent
            : KAPHEIN_NULL
        );
    }

    return pCurrent;
}

static void kaphein_coll_TreeSet_rebalanceAfterInsertion(
    struct kaphein_coll_TreeSet * thisObj,
    struct RbTreeNode * pTarget
)
{
    struct RbTreeNode * pParent;
    struct RbTreeNode * pUncle;
    struct RbTreeNode * pGrandParent;
    struct RbTreeNode * pCurrent = pTarget;

    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->pParent_;
        if(pParent == KAPHEIN_NULL) {
            pCurrent->red_ = 0;

            pCurrent = KAPHEIN_NULL;
        }
        else if(pParent->red_) {
            pGrandParent = pParent->pParent_;
            pUncle = RbTreeNode_getTheOtherChild(pGrandParent, pParent);
            if(pUncle != KAPHEIN_NULL && pUncle->red_) {
                pUncle->red_ = 0;
                pParent->red_ = 0;
                
                pCurrent = pGrandParent;
                if(pCurrent != KAPHEIN_NULL) {
                    pCurrent->red_ = 1;
                }
            }
            else {
                if(
                    pCurrent == pParent->child_.pair_.pRight_
                    && pParent == pGrandParent->child_.pair_.pLeft_
                ) {
                    RbTreeNode_rotate(pParent, rdLeft);
                    pCurrent = pCurrent->child_.pair_.pLeft_;
                }
                else if(
                    pCurrent == pParent->child_.pair_.pLeft_
                    && pParent == pGrandParent->child_.pair_.pRight_
                ) {
                    RbTreeNode_rotate(pParent, rdRight);
                    pCurrent = pCurrent->child_.pair_.pRight_;
                }
                
                pParent = pCurrent->pParent_;
                pParent->red_ = 0;
                pGrandParent->red_ = 1;
                RbTreeNode_rotate(
                    pGrandParent,
                    (enum RotationDirection)(pCurrent == pParent->child_.pair_.pLeft_)
                );

                pCurrent = pGrandParent;
                pParent = pGrandParent->pParent_;
                if(pParent->pParent_ == KAPHEIN_NULL) {
                    thisObj->pRoot_ = pParent;
                }

                pCurrent = KAPHEIN_NULL;
            }
        }
        else {
            pCurrent = KAPHEIN_NULL;
        }
    }
}

static void kaphein_coll_TreeSet_rebalanceAfterRemoval(
    struct kaphein_coll_TreeSet * thisObj,
    struct RbTreeNode * pReplacement
)
{
    struct RbTreeNode * pSibling;
    struct RbTreeNode * pParent;
    struct RbTreeNode * pCurrent = pReplacement;
    
    while(pCurrent != KAPHEIN_NULL) {
        pParent = pCurrent->pParent_;
        if(pParent == KAPHEIN_NULL) {
            thisObj->pRoot_ = pCurrent;

            pCurrent = KAPHEIN_NULL;
        }
        else {
            pSibling = RbTreeNode_getSibling(pCurrent);
            if(pSibling->red_) {
                pParent->red_ = 1;
                pSibling->red_ = 0;

                RbTreeNode_rotate(
                    pParent,
                    (enum RotationDirection)(pCurrent != pParent->child_.pair_.pLeft_)
                );
                if(pSibling->pParent_ == KAPHEIN_NULL) {
                    thisObj->pRoot_ = pSibling;
                }

                pSibling = RbTreeNode_getSibling(pCurrent);
            }

            if(!pSibling->red_) {
                const int caseNumber = (pSibling->child_.pair_.pRight_->red_ ? 0x02 : 0x00)
                    | (pSibling->child_.pair_.pLeft_->red_ ? 0x01 : 0x00)
                ;

                if(caseNumber == 0) {
                    if(!pParent->red_) {
                        pSibling->red_ = 1;

                        pCurrent = pParent;
                    }
                    else {
                        pSibling->red_ = 1;
                        pParent->red_ = 0;

                        pCurrent = KAPHEIN_NULL;
                    }
                }
                else {
                    switch(caseNumber) {
                    case 0:
                    break;
                    case 1:
                        if(pCurrent == pParent->child_.pair_.pLeft_) {
                            pSibling->red_ = 1;
                            pSibling->child_.pair_.pLeft_->red_ = 0;
                            RbTreeNode_rotate(pSibling, rdRight);

                            pSibling = RbTreeNode_getSibling(pCurrent);
                        }
                    break;
                    case 2:
                        if(pCurrent == pParent->child_.pair_.pRight_) {
                            pSibling->red_ = 1;
                            pSibling->child_.pair_.pRight_->red_ = 0;
                            RbTreeNode_rotate(pSibling, rdLeft);
                            
                            pSibling = RbTreeNode_getSibling(pCurrent);
                        }
                    break;
                    case 3:
                    break;
                    }

                    if(!pSibling->red_) {
                        const int childNdx = (pCurrent != pParent->child_.pair_.pLeft_ ? 1 : 0);

                        pSibling->red_ = pParent->red_;
                        pParent->red_ = 0;
                        
                        pSibling->child_.ptrs_[~childNdx & 0x01]->red_ = 0;
                        RbTreeNode_rotate(pParent, (enum RotationDirection)childNdx);
                        if(pSibling->pParent_ == KAPHEIN_NULL) {
                            thisObj->pRoot_ = pSibling;
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
    struct kaphein_coll_TreeSet * thisObj,
    kaphein_coll_compareFunction * pComparator
)
{
    if(thisObj == KAPHEIN_NULL || pComparator == KAPHEIN_NULL) {
        return kapheinErrorCodeArgumentNull;
    }

    thisObj->pComparator_ = pComparator;
    thisObj->pRoot_ = KAPHEIN_NULL;
    thisObj->count_ = 0;

    return kapheinErrorCodeNoError;
}

void kaphein_coll_TreeSet_destruct(
    struct kaphein_coll_TreeSet * thisObj
)
{
    kaphein_coll_TreeSet_clear(thisObj);
}

kaphein_SSize kaphein_coll_TreeSet_getCount(
    const struct kaphein_coll_TreeSet * thisObj
)
{
    return thisObj->count_;
}

bool kaphein_coll_TreeSet_has(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
)
{
    return kaphein_coll_TreeSet_findNode(thisObj, pElement, stEqual) != KAPHEIN_NULL;
}

struct RbTreeNode * kaphein_coll_TreeSet_add(
    struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
)
{
    struct RbTreeNode * newNode = KAPHEIN_NULL;
    struct RbTreeNode * pCurrent;
    int cmpResult;

    if(thisObj->pRoot_ == KAPHEIN_NULL) {
        newNode = kaphein_coll_TreeSet_createNode(KAPHEIN_NULL, pElement);
        thisObj->pRoot_ = newNode;
    }
    else for(
        pCurrent = thisObj->pRoot_;
        !RbTreeNode_isNil(pCurrent);
    ) {
        cmpResult = (*thisObj->pComparator_)(pElement, pCurrent->pElement_);
        if(cmpResult < 0) {
            if(RbTreeNode_isNil(pCurrent->child_.pair_.pLeft_)) {
                newNode = kaphein_coll_TreeSet_createNode(pCurrent, pElement);
                pCurrent->child_.pair_.pLeft_ = newNode;
                
                pCurrent = (struct RbTreeNode *)&nilNode;
            }
            else {
                pCurrent = pCurrent->child_.pair_.pLeft_;
            }
        }
        else if(cmpResult > 0) {
            if(RbTreeNode_isNil(pCurrent->child_.pair_.pRight_)) {
                newNode = kaphein_coll_TreeSet_createNode(pCurrent, pElement);
                pCurrent->child_.pair_.pRight_ = newNode;
                
                pCurrent = (struct RbTreeNode *)&nilNode;
            }
            else {
                pCurrent = pCurrent->child_.pair_.pRight_;
            }
        }
        else {
            pCurrent = (struct RbTreeNode *)&nilNode;
        }
    }
    
    if(newNode != KAPHEIN_NULL) {
        kaphein_coll_TreeSet_rebalanceAfterInsertion(thisObj, newNode);
        ++thisObj->count_;

        thisObj->pRoot_ = RbTreeNode_getRoot(thisObj->pRoot_);
    }

    return newNode;
}

bool kaphein_coll_TreeSet_remove(
    struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
)
{
    struct RbTreeNode ** pChildSlot;
    struct RbTreeNode * pMaxOfLeftSubTree;
    struct RbTreeNode * pChildOfRemoved = KAPHEIN_NULL;
    struct RbTreeNode * removedNode = kaphein_coll_TreeSet_findNode(thisObj, pElement, stEqual);
    int isRemovedNodeRed;
    bool loop = true;

    if(removedNode != KAPHEIN_NULL) {
        while(loop) {
            const int caseNumber = (RbTreeNode_isNullOrNil(removedNode->child_.pair_.pRight_) ? 0x01 : 0x00)
                | (RbTreeNode_isNullOrNil(removedNode->child_.pair_.pLeft_) ? 0x02 : 0x00)
            ;
            switch(caseNumber) {
            case 0: //Has two non-nil children.
                pMaxOfLeftSubTree = RbTreeNode_findRightMost(removedNode->child_.pair_.pLeft_);
                removedNode->pElement_ = pMaxOfLeftSubTree->pElement_;
                removedNode = pMaxOfLeftSubTree;
            break;
            case 1: //Has left non-nil child.
            case 2: //Has right non-nil child.
                pChildOfRemoved = removedNode->child_.ptrs_[caseNumber - 1];
                pChildOfRemoved->pParent_ = removedNode->pParent_;

                pChildSlot = RbTreeNode_getChildSlot(removedNode);
                if(pChildSlot != KAPHEIN_NULL) {
                    *pChildSlot = pChildOfRemoved;
                }
                
                if(!removedNode->red_) {
                    if(pChildOfRemoved->red_) {
                        pChildOfRemoved->red_ = 0;

                        thisObj->pRoot_ = RbTreeNode_getRoot(pChildOfRemoved);
                    }
                    else {
                        kaphein_coll_TreeSet_rebalanceAfterRemoval(thisObj, pChildOfRemoved);
                    }
                }
                else {
                    thisObj->pRoot_ = RbTreeNode_getRoot(pChildOfRemoved);
                }

                loop = false;
            break;
            case 3: //Has no non-nil children.
                isRemovedNodeRed = removedNode->red_;
                if(!isRemovedNodeRed) {
                    kaphein_coll_TreeSet_rebalanceAfterRemoval(thisObj, removedNode);
                }
                
                pChildSlot = RbTreeNode_getChildSlot(removedNode);
                if(pChildSlot != KAPHEIN_NULL) {
                    *pChildSlot = (struct RbTreeNode *)&nilNode;
                    thisObj->pRoot_ = RbTreeNode_getRoot(removedNode->pParent_);
                }
                else {
                    thisObj->pRoot_ = KAPHEIN_NULL;
                }

                loop = false;
            break;
            }
        }

        free(removedNode);

        --thisObj->count_;
    }
    
    return removedNode != KAPHEIN_NULL;
}

static bool kaphein_coll_TreeSet_removeAllHandler(
    void* pContext,
    struct RbTreeNode * pNode
)
{
    kaphein_UIntPtr listElement;
    
    listElement = (kaphein_UIntPtr)pNode;
    kaphein_coll_List_pushBack((struct kaphein_coll_List *)pContext, &listElement, KAPHEIN_ssizeof(listElement));

    return false;
}

void kaphein_coll_TreeSet_clear(
    struct kaphein_coll_TreeSet * thisObj
)
{
    if(thisObj->pRoot_ != KAPHEIN_NULL) {
        kaphein_UIntPtr listElement;
        struct kaphein_coll_List nodeStack;
        kaphein_SSize listElementSize;
        bool truth;

        kaphein_coll_List_construct(&nodeStack, KAPHEIN_NULL, KAPHEIN_NULL);

        RbTreeNode_traverseByPostorder(
            thisObj->pRoot_,
            kaphein_coll_TreeSet_removeAllHandler,
            (void*)&nodeStack
        );

        while(!(kaphein_coll_List_isEmpty(&nodeStack, &truth), truth)) {
            listElementSize = KAPHEIN_ssizeof(listElement);
            kaphein_coll_List_popBack(&nodeStack, &listElement, &listElementSize);
            free((void *)listElement);
        }

        kaphein_coll_List_destruct(&nodeStack);

        thisObj->pRoot_ = KAPHEIN_NULL;
        thisObj->count_ = 0;
    }

    #ifdef _DEBUG
    if(thisObj->pRoot_ == KAPHEIN_NULL && thisObj->count_ > 0) {
        system("pause");
    }
    #endif
}
