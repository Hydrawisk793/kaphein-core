#ifndef KAPHEIN_HGRD_kaphein_coll_TreeSet_h
#define KAPHEIN_HGRD_kaphein_coll_TreeSet_h

#include "def.h"

enum SearchTarget
{
    stNotGreater
    , stLess
    , stNotLess
    , stGreater
    , stEqual
};

struct RbTreeNode
{
    const void * pElement_;

    struct RbTreeNode * pParent_;

    union
    {
        struct RbTreeNode * ptrs_[2];

        struct {
            struct RbTreeNode * pLeft_;

            struct RbTreeNode * pRight_;
        } pair_;

    } child_;

    char red_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct RbTreeNode *
RbTreeNode_findLeftMost(
    struct RbTreeNode * pNode
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct RbTreeNode *
RbTreeNode_findRightMost(
    struct RbTreeNode * pNode
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct RbTreeNode *
RbTreeNode_findLess(
    struct RbTreeNode * pNode
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct RbTreeNode *
RbTreeNode_findGreater(
    struct RbTreeNode * pNode
);

struct kaphein_coll_TreeSet
{
    struct RbTreeNode * pRoot_;
    
    kaphein_SSize count_;
    
    kaphein_coll_compareFunction * pComparator_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_construct(
    struct kaphein_coll_TreeSet * thisObj
    , kaphein_coll_compareFunction * pComparator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void
kaphein_coll_TreeSet_destruct(
    struct kaphein_coll_TreeSet * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
kaphein_SSize
kaphein_coll_TreeSet_getCount(
    const struct kaphein_coll_TreeSet * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool
kaphein_coll_TreeSet_has(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
);

bool
kaphein_coll_TreeSet_findLessThan(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
    , void * foundElementsOut
    , kaphein_SSize * foundElementCountInOut
);

bool
kaphein_coll_TreeSet_findNotGreaterThan(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
    , void * foundElementsOut
    , kaphein_SSize * foundElementCountInOut
);

bool
kaphein_coll_TreeSet_findGreaterThan(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
    , void * foundElementsOut
    , kaphein_SSize * foundElementCountInOut
);

bool
kaphein_coll_TreeSet_findNotLessThan(
    const struct kaphein_coll_TreeSet* thisObj
    , const void * pElement
    , void * foundElementsOut
    , kaphein_SSize * foundElementCountInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct RbTreeNode *
kaphein_coll_TreeSet_add(
    struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool
kaphein_coll_TreeSet_remove(
    struct kaphein_coll_TreeSet * thisObj
    , const void * pElement
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void kaphein_coll_TreeSet_clear(
    struct kaphein_coll_TreeSet * thisObj
);

#endif
