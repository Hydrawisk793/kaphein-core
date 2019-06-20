#include <Windows.h>
#include "kaphein/mem/utils.h"
#include "kaphein/thrd/Mutex.h"

enum kaphein_ErrorCode
kaphein_thrd_Mutex_construct(
    struct kaphein_thrd_Mutex * thisObj
    , void * allocator
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    KAPHEIN_x_UNUSED_PARAMETER(allocator)

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObj->impl_ = (void *)CreateMutex(NULL, false, NULL);
        if(NULL == thisObj->impl_) {
            resultErrorCode = kapheinErrorCodePlatformResourceAllocationFailed;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_thrd_Mutex_destruct(
    struct kaphein_thrd_Mutex * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        BOOL winResult;
        
        if(NULL != thisObj->impl_) {
            winResult = CloseHandle((HANDLE)thisObj->impl_);

            if(FALSE == winResult) {
                //TODO : 오류 코드 세분화
                resultErrorCode = kapheinErrorCodeUnknownError;
            }
            else {
                thisObj->impl_ = NULL;
            }
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_thrd_Mutex_getInternalHandle(
    struct kaphein_thrd_Mutex * thisObj
    , void ** handleOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *handleOut = thisObj->impl_;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_thrd_Mutex_lock(
    struct kaphein_thrd_Mutex * thisObj
    , int waitMilliseconds
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const DWORD waitResult = WaitForSingleObject(
            (HANDLE)thisObj->impl_
            , (waitMilliseconds < 0 ? INFINITE : (DWORD)waitMilliseconds)
        );

        switch(waitResult) {
        case WAIT_OBJECT_0:
        break;
        case WAIT_ABANDONED:
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        break;
        case WAIT_TIMEOUT:
            resultErrorCode = kapheinErrorCodeOperationTimeout;
        break;
        case WAIT_FAILED:
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        break;
        default:
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        //break;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_thrd_Mutex_unlock(
    struct kaphein_thrd_Mutex * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(FALSE == ReleaseMutex((HANDLE)thisObj->impl_)) {
            resultErrorCode = kapheinErrorCodeOperationInvalid;
        }
    }

    return resultErrorCode;
}
