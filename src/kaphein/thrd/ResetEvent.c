#include "kaphein/ErrorCode.h"
#include "kaphein/thrd/internal.h"
#include "kaphein/thrd/ResetEvent.h"

int kapheinThrdResetEventGetSize(void)
{
    return (int)sizeof(struct kapheinThrdResetEvent);
}

int kapheinThrdResetEventConstruct(
    struct kapheinThrdResetEvent *objOut
)
{
    int errorCode = kapheinErrorCodeNoError;

    if(objOut == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
    #if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
        objOut->handle_ = CreateEventA(NULL, TRUE, FALSE, NULL);
        if(objOut->handle_ == NULL) {
            errorCode = kapheinErrorCodePlatformResourceAllocationFailed;
        }
    #elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
        if(errorCode = kapheinThrdMutexConstruct(&objOut->mutex_), errorCode == kapheinErrorCodeNoError) {
            if(objOut->cv_ = NULL, pthread_cond_init(&objOut->cv_, NULL) != 0) {
                errorCode = kapheinErrorCodePlatformResourceAllocationFailed;
            }
            else {
                objOut->isSet_ = false;
            }
        }
    #else
        errorCode = kapheinErrorCodeNotSupported;
    #endif
    }

    return errorCode;
}

int kapheinThrdResetEventDestruct(
    struct kapheinThrdResetEvent *obj
)
{
    int errorCode = kapheinErrorCodeNoError;

    if(obj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
    #if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
        if(obj->handle_ != NULL) {
            CloseHandle(obj->handle_);
            obj->handle_ = NULL;
        }
    #elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
        kapheinThrdMutexDestruct(&obj->mutex_);
        
        if(obj->cv_ != NULL) {
            pthread_cond_destroy(&obj->cv_);
            obj->cv_ = NULL;
        }

        obj->isSet_ = false;
    #endif
    }

    return errorCode;
}

int kapheinThrdResetEventReset(
    struct kapheinThrdResetEvent *obj
)
{
    int errorCode = kapheinErrorCodeNoError;

    if(obj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
    #if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
        if(ResetEvent(obj->handle_) == FALSE) {
            errorCode = kapheinErrorCodeOperationInvalid;
        }
    #elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
        errorCode = kapheinThrdMutexLock(&obj->mutex_, -1);
        if(errorCode == kapheinErrorCodeNoError) {
            obj->isSet_ = false;

            kapheinThrdMutexUnlock(&obj->mutex_);
        }
    #else
        errorCode = kapheinErrorCodeNotSupported;
    #endif
    }

    return errorCode;
}

int kapheinThrdResetEventSet(
    struct kapheinThrdResetEvent *obj
)
{
    int errorCode = kapheinErrorCodeNoError;

    if(obj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
    #if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
        if(SetEvent(obj->handle_) == FALSE) {
            errorCode = kapheinErrorCodeOperationInvalid;
        }
    #elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
        errorCode = kapheinThrdMutexLock(&obj->mutex_, -1);
        if(errorCode == kapheinErrorCodeNoError) {
            obj->isSet_ = true;

            kapheinThrdMutexUnlock(&obj->mutex_);
            
            pthread_cond_signal(&obj->cv_);
        }
    #else
        errorCode = kapheinErrorCodeNotSupported;
    #endif
    }

    return errorCode;
}

int kapheinThrdResetEventWaitOne(
    struct kapheinThrdResetEvent *obj
    , int milliseconds
)
{
#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
    DWORD waitResult;
#elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
    struct timespec ts;
    int condWaitResult;
#endif
    int errorCode = kapheinErrorCodeNoError;

    if(obj == NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
    #if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
        waitResult = WaitForSingleObject(obj->handle_, (milliseconds < 0 ? INFINITE : (DWORD)milliseconds));
        switch(waitResult) {
        case WAIT_OBJECT_0:
        break;
        case WAIT_ABANDONED:
            errorCode = kapheinErrorCodeOperationInvalid;
        break;
        case WAIT_TIMEOUT:
            errorCode = kapheinErrorCodeOperationTimeout;
        break;
        case WAIT_FAILED:
            errorCode = kapheinErrorCodeOperationInvalid;
        break;
        default:
            errorCode = kapheinErrorCodeOperationInvalid;
        //break;
        }
    #elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
        errorCode = kapheinThrdMutexLock(&obj->mutex_, -1);
        if(errorCode == kapheinErrorCodeNoError) {
            if(!obj->isSet_) {
                if(milliseconds < 0) {
                    condWaitResult = pthread_cond_wait(&obj->cv_, &obj->mutex_.mutex_);
                }
                else {
                    kapheinThrdMillisecondsToTimespec(milliseconds, &ts);
                    condWaitResult = pthread_cond_timedwait(&obj->cv_, &obj->mutex_.mutex_, &ts);
                }

                switch(condWaitResult) {
                case 0:
                break;
                case ETIMEDOUT:
                    errorCode = kapheinErrorCodeOperationTimeout;
                break;
                default:
                    errorCode = kapheinErrorCodeOperationInvalid;
                //break;
                }
            }

            kapheinThrdMutexUnlock(&obj->mutex_);
        }
    #else
        milliseconds;

        errorCode = kapheinErrorCodeNotSupported;
    #endif
    }

    return errorCode;
}
