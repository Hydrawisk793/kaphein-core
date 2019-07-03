#include "kaphein/mem/utils.h"
#include "kaphein/math/IntervalInt32.h"

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
isValueInInterval(
    const struct kaphein_math_IntervalInt32 * thisObj
    , kaphein_Int32 value
)
{
    return (value >= thisObj->u.m.minimum && value <= thisObj->u.m.maximum);
}

static
int
_insertIfNotExistAndSort(
    struct kaphein_mem_Allocator * allocator
)
{
    //TODO : 코드 작성
}

static
struct kaphein_math_IntervalInt32 *
_createSortedIntervalListSet(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_mem_Allocator * allocator
)
{
    //TODO : 코드 작성
    //enum kapheinErrorCode resultErrorCode = kapheinErrorCodeNoError;
    //struct kaphein_math_IntervalInt32 *const sortedIntervals = (struct kaphein_math_IntervalInt32 *)kaphein_mem_allocate(
    //    allocator
    //    , KAPHEIN_ssizeof(*intervals) * intervalCount
    //    , KAPHEIN_NULL
    //    , &resultErrorCode
    //);

    //if(kapheinErrorCodeNoError == resultErrorCode) {
    //    kaphein_SSize i, len;
    //    
    //    for(i = 0, len = intervalCount; i < len; ++i) {
    //        _insertIfNotExistAndSort(
    //            sortedIntervals,
    //            intervals[i],
    //            _intervalComparatorForSort,
    //            comparatorParams
    //        );
    //    }
    //}

    //return sortedIntervals;
}

static
kaphein_SSize
_findEndOfClosureIndex(
    const struct kaphein_math_IntervalInt32 * sortedArraySet
    , kaphein_SSize sortedArraySetSize
    , kaphein_SSize startIndex
)
{
    kaphein_SSize endOfClosureIndex = startIndex + 1;
    kaphein_SSize i, len;

    for(
        i = startIndex, len = sortedArraySetSize;
        i < endOfClosureIndex && i < len;
        ++i
    ) {
        const struct kaphein_math_IntervalInt32 * current = sortedArraySet + i;
        kaphein_SSize endOfNeighborIndex = i + 1;
        kaphein_SSize j;
        bool loopJ = true;

        for(j = endOfNeighborIndex; loopJ && j < len; ) {
            const struct kaphein_math_IntervalInt32 * other = sortedArraySet + j;

            if(current->u.m.maximum < other->u.m.minimum) {
                endOfNeighborIndex = j;
                loopJ = false;
            }
            else {
                ++j;
            }
        }
        if(loopJ) {
            endOfNeighborIndex = len;
        }

        endOfClosureIndex = (
            endOfClosureIndex < endOfNeighborIndex
            ? endOfNeighborIndex
            : endOfClosureIndex
        );
    }

    return endOfClosureIndex;
}

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_disjoin(
    const struct kaphein_math_IntervalInt32 * intervals
    , kaphein_SSize intervalsCount
    , struct kaphein_math_IntervalInt32 * resultsOut
    , kaphein_SSize * resultCountInOut
    , bool mergePoints
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(
        KAPHEIN_NULL == intervals
        || KAPHEIN_NULL == resultCountInOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else if(
        intervalsCount < 0
        || (KAPHEIN_NULL != resultsOut && *resultCountInOut < 0)
    ) {
        resultErrorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        switch(intervalsCount) {
        case 0:
            *resultCountInOut = 0;
        break;
        case 1:
            if(KAPHEIN_NULL != resultsOut) {
                resultsOut[0].u.m.minimum = intervals[0].u.m.minimum;
                resultsOut[0].u.m.maximum = intervals[0].u.m.maximum;
            }
            
            *resultCountInOut = 1;
        break;
        default:
        //TODO : 코드 작성
        //{
        //    var disjoinedIntervals = [];
		    
        //    kaphein_SSize j = 0, sortedPointMaxIndex = 0, endOfClosureIndex = 0;
        //    kaphein_SSize i, len;
        //    var neighbor = null;
        //    var sortedPoints = [];
        //    struct kaphein_math_IntervalInt32 * sortedListSet = _createSortedIntervalListSet(intervals, intervalsCount, allocator);
        //    for(i = 0, len = sortedListSet.length; i < len; ) {
        //        j = 0;

        //        endOfClosureIndex = _findEndOfClosureIndex(sortedListSet, i);
        //        sortedPoints.length = 0;
        //        for(j = i; j < endOfClosureIndex; ++j) {
        //            neighbor = sortedListSet[j];
        //            _insertIfNotExistAndSort(
        //                sortedPoints,
        //                neighbor._min
        //            );
        //            _insertIfNotExistAndSort(
        //                sortedPoints,
        //                neighbor._max
        //            );
        //        }

        //        sortedPointMaxIndex = sortedPoints.length - 1;
        //        if(mergePoints) {
        //            disjoinedIntervals.push(new Interval(sortedPoints[0], sortedPoints[sortedPointMaxIndex]));
        //        }
        //        else {
        //            //TODO : 안전성 검사(e.g. Interval이 1개인 경우)
        //            j = 0;
        //            do {
        //                disjoinedIntervals.push(new Interval(sortedPoints[j], sortedPoints[j + 1]));
        //                ++j;
        //            }
        //            while(j < sortedPointMaxIndex);
        //        }

        //        i = endOfClosureIndex;
        //    }
        //}
        break;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_intersectsWith(
    const struct kaphein_math_IntervalInt32 * thisObj
    , const struct kaphein_math_IntervalInt32 * other
    , bool * truthOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == other
        || KAPHEIN_NULL == truthOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->u.m.minimum < other->u.m.minimum) {
            *truthOut = thisObj->u.m.maximum >= other->u.m.minimum && other->u.m.maximum >= thisObj->u.m.minimum;
        }
        else {
            *truthOut = other->u.m.maximum >= thisObj->u.m.minimum && thisObj->u.m.maximum  >= other->u.m.minimum;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_IntervalInt32_contains(
    const struct kaphein_math_IntervalInt32 * thisObj
    , const struct kaphein_math_IntervalInt32 * other
    , bool * truthOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == other
        || KAPHEIN_NULL == truthOut
    ) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->u.m.minimum < other->u.m.minimum) {
            *truthOut = isValueInInterval(thisObj, other->u.m.minimum)
                && isValueInInterval(thisObj, other->u.m.maximum)
            ;
        }
        else {
            *truthOut = isValueInInterval(other, thisObj->u.m.minimum)
                && isValueInInterval(other, thisObj->u.m.maximum)
            ;
        }
    }

    return resultErrorCode;
}
