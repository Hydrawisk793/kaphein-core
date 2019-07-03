#ifndef KAPHEIN_HGRD_kaphein_math_IntervalInt32_h
#define KAPHEIN_HGRD_kaphein_math_IntervalInt32_h

#include "../def.h"
#include "../mem/Allocator.h"

struct kaphein_math_IntervalInt32
{
    union {
        kaphein_Int32 a[2];

        struct {
            kaphein_Int32 minimum;

            kaphein_Int32 maximum;
        } m;
    } u;
};

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_disjoin(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalsCount
    , struct kaphein_math_IntervalInt32 * resultsOut
    , kaphein_SSize * resultCountInOut
    , bool mergePoints
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_merge(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalsCount
    , struct kaphein_math_IntervalInt32 * resultsOut
    , kaphein_SSize * resultCountInOut
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_negate(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalsCount
    , struct kaphein_math_IntervalInt32 * resultsOut
    , kaphein_SSize * resultCountInOut
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_findClosure(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalsCount
    , struct kaphein_math_IntervalInt32 * resultsOut
    , kaphein_SSize * resultCountInOut
    , int targetIndex
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_IntervalInt32_intersectsWith(
    const struct kaphein_math_IntervalInt32 * thisObj
    , const struct kaphein_math_IntervalInt32 * other
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_IntervalInt32_contains(
    const struct kaphein_math_IntervalInt32 * thisObj
    , const struct kaphein_math_IntervalInt32 * other
    , bool * truthOut
);

#endif
