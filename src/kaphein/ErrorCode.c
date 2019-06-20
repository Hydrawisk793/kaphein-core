#include <string.h>
#include "kaphein/internal.h"
#include "kaphein/ErrorCode.h"
#include "kaphein/mem/utils.h"
#include "kaphein/text/encoding.h"

enum kaphein_ErrorCode
kaphein_ErrorCode_getMessage(
    enum kaphein_ErrorCode errorCode
    , char * messageOut
    , kaphein_SSize * messageSizeInOut
)
{
    const char * msg;
    kaphein_SSize msgSize;
    kaphein_SSize destSize;
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(messageSizeInOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        destSize = *messageSizeInOut;

        switch(errorCode) {
        case kapheinErrorCodeNoError:
            msg = "No errors have been occured.";
        break;
        case kapheinErrorCodeUnknownError:
            msg = "An unknown error has been occured.";
        break;
        case kapheinErrorCodeOperationTimeout:
            msg = "The operation is timed out.";
        break;
        case kapheinErrorCodeOperationInvalid:
            msg = "The operation is invalid in the current state.";
        break;
        case kapheinErrorCodeNotImplemented:
            msg = "The operation is not implemeted yet.";
        break;
        case kapheinErrorCodeNotSupported:
            msg = "The operation is not supported.";
        break;
        case kapheinErrorCodeArgumentInvalid:
            msg = "The argument is invalid.";
        break;
        case kapheinErrorCodeArgumentNull:
            msg = "The argument cannot be null.";
        break;
        case kapheinErrorCodeArgumentOutOfRange:
            msg = "The argument is out of range.";
        break;
        case kapheinErrorCodeMemoryAllocationFailed:
            msg = "A memory allocation has been failed.";
        break;
        case kapheinErrorCodePlatformResourceAllocationFailed:
            msg = "A system resource allocation has been failed.";
        break;
        case kapheinErrorCodeArithmeticError:
            msg = "An arithmetic error has been occured.";
        break;
        case kapheinErrorCodeDivisionByZero:
            msg = "Division by zero has been attempted.";
        break;
        default:
            msg = "An unknown error has been occured.";
        }

        msgSize = (kaphein_SSize)strlen(msg);
        *messageSizeInOut = msgSize;

        if(messageOut != KAPHEIN_NULL) {
            resultErrorCode = kaphein_mem_copy(
                messageOut
                , destSize
                , msg
                , msgSize
            );
        }
    }

    return resultErrorCode;
}
