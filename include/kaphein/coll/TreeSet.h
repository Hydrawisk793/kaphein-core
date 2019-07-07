#ifndef KAPHEIN_HGRD_kaphein_coll_TreeSet_h
#define KAPHEIN_HGRD_kaphein_coll_TreeSet_h

#include "../mem/Allocator.h"
#include "def.h"
#include "Iterator.h"

struct kaphein_coll_TreeSet;

struct kaphein_coll_TreeSet_Iterator;

struct kaphein_coll_TreeSet
{
    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_construct(
    struct kaphein_coll_TreeSet * thisObj
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_destruct(
    struct kaphein_coll_TreeSet * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_getCount(
    const struct kaphein_coll_TreeSet * thisObj
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_isEmpty(
    const struct kaphein_coll_TreeSet * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_getBeginConstIterator(
    const struct kaphein_coll_TreeSet * thisObj
    , struct kaphein_coll_TreeSet_Iterator * iterOut
);

enum kaphein_ErrorCode
kaphein_coll_TreeSet_getEndConstIterator(
    const struct kaphein_coll_TreeSet * thisObj
    , struct kaphein_coll_TreeSet_Iterator * iterOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_has(
    const struct kaphein_coll_TreeSet * thisObj
    , const void * element
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_add(
    struct kaphein_coll_TreeSet * thisObj
    , const void * element
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_remove(
    struct kaphein_coll_TreeSet * thisObj
    , const void * element
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_clear(
    struct kaphein_coll_TreeSet * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_toArray(
    const struct kaphein_coll_TreeSet * thisObj
    , void * elementsOut
    , kaphein_SSize elementsOutSize
);

struct kaphein_coll_TreeSet_Iterator
{
    struct kaphein_coll_Iterator parent;

    const struct kaphein_coll_TreeSet * treeSet_;

    const void * currentNode_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_copyConstruct(
    void * thisObj
    , const void * src
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_destruct(
    void * thisObj
);

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_copyAssign(
    void * thisObj
    , const void * src
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
const void *
kaphein_coll_TreeSet_Iterator_dereferenceConst(
    const void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
);

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_hasReachedBegin(
    const void * thisObj
    , bool * truthOut
);

enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_hasReachedEnd(
    const void * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_TreeSet_Iterator_reset(
    void * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool
kaphein_coll_TreeSet_Iterator_moveToNext(
    void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
);

bool
kaphein_coll_TreeSet_Iterator_moveToPrevious(
    void * thisObj
    , enum kaphein_ErrorCode * errorCodeOut
);

#endif
