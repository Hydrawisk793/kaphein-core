#ifndef KAPHEIN_HGRD_kaphein_mem_SegmentPool_h
#define KAPHEIN_HGRD_kaphein_mem_SegmentPool_h

#include "../def.h"
#include "../ErrorCode.h"

struct kaphein_mem_SegmentPool;

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
struct kaphein_mem_SegmentPool *
kaphein_mem_SegmentPool_new(
    enum kaphein_ErrorCode * errorCodeOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_mem_SegmentPool_delete(
    void * mem
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_mem_SegmentPool_construct(
    struct kaphein_mem_SegmentPool * thisObjOut
    , void * memory
    , kaphein_SSize memorySize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_mem_SegmentPool_destruct(
    struct kaphein_mem_SegmentPool * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void *
kaphein_mem_SegmentPool_allocate(
    void * thisObj
    , kaphein_SSize size
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_mem_SegmentPool_deallocate(
    void * thisObj
    , void * memory
    , kaphein_SSize size
);

#endif
