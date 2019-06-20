#include "kaphein/coll/sort.h"

static
enum kaphein_ErrorCode
testSortFunctionArguments(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeUnknownError;

    if(elementTrait == KAPHEIN_NULL || elements == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else if(
        elementTrait->compare == KAPHEIN_NULL
        || elementTrait->swap == KAPHEIN_NULL
        || elementTrait->elementSize < 0
    ) {
        resultErrorCode = kapheinErrorCodeArgumentInvalid;
    }
    else if(elementCount < 0) {
        resultErrorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        resultErrorCode = kapheinErrorCodeNoError;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_sortBySelection(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
)
{
    enum kaphein_ErrorCode resultErrorCode = testSortFunctionArguments(
        elementTrait
        , elements
        , elementCount
    );

    if(resultErrorCode == kapheinErrorCodeNoError) {
        char * lhs, * rhs;
        kaphein_SSize l, r;

        lhs = (char *)elements;

        for(l = 1; l < elementCount; lhs += elementTrait->elementSize, ++l) {
            for(rhs = lhs + elementTrait->elementSize, r = l; r < elementCount; rhs += elementTrait->elementSize, ++r) {
                if((*elementTrait->compare)(lhs, rhs) > 0) {
                    (*elementTrait->swap)(lhs, rhs);
                }
            };
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_sortByBubble(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
)
{
    enum kaphein_ErrorCode resultErrorCode = testSortFunctionArguments(
        elementTrait
        , elements
        , elementCount
    );

    if(resultErrorCode == kapheinErrorCodeNoError) {
        char * lhs, * rhs;
        kaphein_SSize l, r;

        for(r = elementCount; r > 1; ) {
            --r;

            for(
                lhs = (char *)elements, rhs = lhs + elementTrait->elementSize, l = r;
                l > 0;
                lhs += elementTrait->elementSize, rhs += elementTrait->elementSize
            ) {
                --l;

                if((*elementTrait->compare)(lhs, rhs) > 0) {
                    (*elementTrait->swap)(lhs, rhs);
                }
            };
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_coll_sortByInsertion(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
)
{
    enum kaphein_ErrorCode resultErrorCode = testSortFunctionArguments(
        elementTrait
        , elements
        , elementCount
    );

    if(resultErrorCode == kapheinErrorCodeNoError) {
        char * lhs, * rhs, * currentRhs;
        kaphein_SSize l, r;
        
        rhs = (char *)elements + elementTrait->elementSize;

        for(r = 1; r < elementCount; rhs += elementTrait->elementSize, ++r) {
            for(
                currentRhs = rhs, lhs = currentRhs - elementTrait->elementSize, l = r;
                l > 0 && (*elementTrait->compare)(lhs, currentRhs) > 0;
                lhs -= elementTrait->elementSize, currentRhs -= elementTrait->elementSize, --l
            ) {
                (*elementTrait->swap)(lhs, currentRhs);
            }
        }
    }

    return resultErrorCode;
}
