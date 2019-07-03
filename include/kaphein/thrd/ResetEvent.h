#ifndef KAPHEIN_HGRD_kaphein_thrd_ResetEvent_H
#define KAPHEIN_HGRD_kaphein_thrd_ResetEvent_H

#include "../def.h"
#include "../ErrorCode.h"
#include "../mem/Allocator.h"

/**
 *  @brief Represents reset event objects that acts like manual or auto reset events in Microsoft Windows operating systems.
 */
struct kaphein_thrd_ResetEvent
{
    void * impl_;
};

enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_construct(
    struct kaphein_thrd_ResetEvent * thisObj
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_destruct(
    struct kaphein_thrd_ResetEvent * thisObj
);

enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_reset(
    struct kaphein_thrd_ResetEvent * thisObj
);

enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_set(
    struct kaphein_thrd_ResetEvent * thisObj
);

enum kaphein_ErrorCode
kaphein_thrd_ResetEvent_waitOne(
    struct kaphein_thrd_ResetEvent * thisObj
    , int waiMilliseconds
);

#endif
