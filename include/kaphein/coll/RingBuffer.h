#ifndef KAPHEIN_HGRD_kaphein_coll_RingBuffer_h
#define KAPHEIN_HGRD_kaphein_coll_RingBuffer_h

#include "def.h"

struct kaphein_coll_RingBuffer
{
    char * inPtr_;

    char * outPtr_;
    
    char * byteArray_;
    
    kaphein_SSize byteArraySize_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_construct(
    struct kaphein_coll_RingBuffer * thisObj
    , char * byteArray
    , kaphein_SSize byteArraySize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_destruct(
    struct kaphein_coll_RingBuffer * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_isEmpty(
    const struct kaphein_coll_RingBuffer * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_isFull(
    const struct kaphein_coll_RingBuffer * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getCapacity(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * capacityOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getAvailable(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * availableOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_getCount(
    const struct kaphein_coll_RingBuffer * thisObj
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_enqueue(
    struct kaphein_coll_RingBuffer * thisObj
    , const char * src
    , kaphein_SSize srcSize
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_dequeue(
    struct kaphein_coll_RingBuffer * thisObj
    , char * dest
    , kaphein_SSize destSize
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_RingBuffer_clear(
    struct kaphein_coll_RingBuffer * thisObj
);

#endif
