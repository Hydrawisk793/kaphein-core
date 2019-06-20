#include "kaphein/math/Interval.h"

/* ******************************** */
/* Delcarations */

static
bool kaphein_x_isValueInInterval(
    const struct kaphein_math_Interval * interval
    , double value
);

/* ******************************** */

/* ******************************** */
/* Definitions */

//TODO : Implement this function.
enum kaphein_ErrorCode
kaphein_math_Interval_disjoin(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , double epsilon
    , bool mergePoints
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(intervals == KAPHEIN_NULL || outputCountInOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        intervalCount;
        outputs;
        epsilon;
        mergePoints;
        
        errorCode = kapheinErrorCodeNotImplemented;
    }

    return errorCode;
}

//TODO : Implement this function.
enum kaphein_ErrorCode
kaphein_math_Interval_findClosure(
    const struct kaphein_math_Interval * intervals
    , kaphein_SSize intervalCount
    , struct kaphein_math_Interval * outputs
    , kaphein_SSize * outputCountInOut
    , kaphein_SSize targetIndex
    , double epsilon
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(intervals == KAPHEIN_NULL || outputCountInOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        //kaphein_SSize i, j;
        //kaphein_SSize len;
        //bool * visitFlags;

        intervalCount;
        outputs;
        targetIndex;
        epsilon;

        //var sortedListSet = _createSortedIntervalListSet(intervals, arguments[2]);

        //len = sortedListSet.length;
        //visitFlags = (bool *)malloc(len * sizeof(bool));
        //for(i = len; i > 0; ) {
        //    --i;
        //    visitFlags[i] = false;
        //}

        //var closureStartIndex = targetIndex;
        //var closureInclusiveEndIndex = targetIndex;
        //var targetIndices = [targetIndex];
        //for(; targetIndices.length > 0; ) {
        //    i = targetIndices.pop();
        //    if(!visitFlags[i]) {
        //        visitFlags[i] = true;

        //        var lhs = sortedListSet[i];
        //        for(j = 0; j < len; ++j) {
        //            if(j != i && lhs.intersectsWith(sortedListSet[j])) {
        //                targetIndices.push(j);

        //                closureStartIndex = (closureStartIndex > j ? j : closureStartIndex);
        //                closureInclusiveEndIndex = (closureInclusiveEndIndex < j ? j : closureInclusiveEndIndex);
        //            }
        //        }
        //    }
        //}

        //var closure = [];
        //for(var i = closureStartIndex; i <= closureInclusiveEndIndex; ++i) {
        //    closure.push(sortedListSet[i]);
        //}

        //free(visitFlags);

        //return closure;

        errorCode = kapheinErrorCodeNotImplemented;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_Interval_intersectsWith(
    const struct kaphein_math_Interval * thisObj
    , const struct kaphein_math_Interval * rhs
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || rhs == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->u.m.minimum < rhs->u.m.minimum) {
            *truthOut = thisObj->u.m.maximum >= rhs->u.m.minimum && rhs->u.m.maximum >= thisObj->u.m.minimum;
        }
        else {
            *truthOut = rhs->u.m.maximum >= thisObj->u.m.minimum && thisObj->u.m.maximum >= rhs->u.m.minimum;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_Interval_containsInterval(
    const struct kaphein_math_Interval * thisObj
    , const struct kaphein_math_Interval * rhs
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || rhs == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->u.m.minimum < rhs->u.m.minimum) {
            *truthOut = kaphein_x_isValueInInterval(thisObj, rhs->u.m.minimum)
                && kaphein_x_isValueInInterval(thisObj, rhs->u.m.maximum)
            ;
        }
        else {
            *truthOut = kaphein_x_isValueInInterval(rhs, thisObj->u.m.minimum)
                && kaphein_x_isValueInInterval(rhs, thisObj->u.m.maximum)
            ;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_Interval_containsValue(
    const struct kaphein_math_Interval * thisObj
    , double value
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *truthOut = kaphein_x_isValueInInterval(thisObj, value);
    }

    return errorCode;
}

static
bool kaphein_x_isValueInInterval(
    const struct kaphein_math_Interval * interval
    , double value
)
{
    return (value >= interval->u.m.minimum && value <= interval->u.m.maximum);
};

/* ******************************** */
