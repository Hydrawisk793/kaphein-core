#ifndef KAPHEIN_HGRD_kaphein_thrd_ResetEvent_H
#define KAPHEIN_HGRD_kaphein_thrd_ResetEvent_H

#include "../def.h"
#include "../ErrorCode.h"

/**
 *  @brief Represents reset event objects that acts like manual or auto reset events in Microsoft Windows OS.
 */
struct kaphein_thrd_ResetEvent
{
    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_construct(
    struct kaphein_thrd_ResetEvent * thisObj
    , void * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_destruct(
    struct kaphein_thrd_ResetEvent * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_reset(
    struct kaphein_thrd_ResetEvent * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_set(
    struct kaphein_thrd_ResetEvent * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_waitOne(
    struct kaphein_thrd_ResetEvent * thisObj
    , int waiMilliseconds
);

#endif
