#ifndef KAPHEIN_HGRD_kaphein_coll_List_h
#define KAPHEIN_HGRD_kaphein_coll_List_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_coll_List
{
    const struct kaphein_coll_ElementTrait * elementTrait_;

    void * allocator_;

    void * head_;

    void * tail_;

    kaphein_SSize count_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_construct(
    struct kaphein_coll_List * thisObj
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_destruct(
    struct kaphein_coll_List * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_isEmpty(
    const struct kaphein_coll_List * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_isFull(
    const struct kaphein_coll_List * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_getCount(
    const struct kaphein_coll_List * thisObj
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_pushFront(
    struct kaphein_coll_List * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_popFront(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_peekFront(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_pushBack(
    struct kaphein_coll_List * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_popBack(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_peekBack(
    struct kaphein_coll_List * thisObj
    , void * elementOut
    , kaphein_SSize * elementSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_List_clear(
    struct kaphein_coll_List * thisObj
);

#endif
