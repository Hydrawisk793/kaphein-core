#ifndef KAPHEIN_HGRD_kaphein_coll_Vector_h
#define KAPHEIN_HGRD_kaphein_coll_Vector_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_coll_Vector;

struct kaphein_coll_Vector_ElementTraits
{
    kaphein_SSize elementSize;
    
    kaphein_copyConstructFunction * copyConstruct;

    kaphein_destructFunction * destruct;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct kaphein_coll_Vector *
kaphein_coll_Vector_new(
    struct kaphein_mem_Allocator * allocator
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_delete(
    struct kaphein_coll_Vector * obj
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_construct(
    struct kaphein_coll_Vector * thisObj
    , const struct kaphein_coll_Vector_ElementTraits * elementTraits
    , kaphein_SSize initialCapacity
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
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

enum kaphein_ErrorCode
kaphein_coll_Vector_reserve(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

enum kaphein_ErrorCode
kaphein_coll_Vector_insert(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize index
    , const void * element
    , kaphein_SSize elementSize
);

enum kaphein_ErrorCode
kaphein_coll_Vector_remove(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize index
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_clear(
    struct kaphein_coll_Vector * thisObj
);

#endif
