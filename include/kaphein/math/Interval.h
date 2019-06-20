#ifndef KAPHEIN_HGRD_kaphein_math_Interval_h
#define KAPHEIN_HGRD_kaphein_math_Interval_h

#include "../ErrorCode.h"

struct kaphein_math_Interval
{
    union {
        double a[2];

        struct {
            double minimum;

            double maximum;
        } m;
    } u;
};

enum kaphein_ErrorCode
kaphein_math_Interval_disjoin(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , double epsilon
    , bool mergePoints
);

enum kaphein_ErrorCode
kaphein_math_Interval_merge(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , double minimum
    , double maximum
    , double epsilon
);

enum kaphein_ErrorCode
kaphein_math_Interval_negate(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , double minimum
    , double maximum
    , double epsilon
);

enum kaphein_ErrorCode
kaphein_math_Interval_findClosure(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , kaphein_SSize targetIndex
    , double epsilon
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_Interval_intersectsWith(
    const struct kaphein_math_Interval * thisObj
    , const struct kaphein_math_Interval * rhs
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_Interval_containsInterval(
    const struct kaphein_math_Interval * thisObj
    , const struct kaphein_math_Interval * rhs
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_Interval_containsValue(
    const struct kaphein_math_Interval * thisObj
    , double value
    , bool * truthOut
);

#endif
