#ifndef KAPHEIN_HGRD_kaphein_coll_Vector_h
#define KAPHEIN_HGRD_kaphein_coll_Vector_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_coll_Vector
{
    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_construct(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize initialCapacity
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_destruct(
    struct kaphein_coll_Vector * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_getPointerToElements(
    const struct kaphein_coll_Vector * thisObj
    , void ** pointerOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_isEmpty(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
);

enum kaphein_ErrorCode
kaphein_coll_Vector_isFull(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_getCapacity(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * capacityOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_getCount(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * countOut
);

enum kaphein_ErrorCode
kaphein_coll_Vector_resize(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_reserve(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

enum kaphein_ErrorCode
kaphein_coll_Vector_pushFront(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

enum kaphein_ErrorCode
kaphein_coll_Vector_popFront(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_pushBack(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_popBack(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_insert(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize startIndex
    , const void * elements
    , kaphein_SSize elementSize
    , kaphein_SSize elementCount
);

enum kaphein_ErrorCode
kaphein_coll_Vector_remove(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize index
    , kaphein_SSize count
    , void * elementsOut
    , kaphein_SSize elementsOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_clear(
    struct kaphein_coll_Vector * thisObj
);

#endif
