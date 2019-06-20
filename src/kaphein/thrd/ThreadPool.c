//#include <Windows.h>
//#include <process.h>
//#include <stdio.h>
//#include <limits.h>
//#include "kaphein/ErrorCode.h"
//#include "kaphein/coll/List.h"
//#include "kaphein/mem/Allocator.h"
//#include "kaphein/thrd/Mutex.h"
//#include "kaphein/thrd/ThreadPool.h"
//
///******************************************************************/
///*kapheinThrdThreadPoolWork Declarations*/
//
//struct kapheinThrdThreadPoolWork
//{
//    kapheinThrdThreadPoolWorkFunction *pFunc_;
//
//    void *param_;
//
//    int result_;
//};
//
///******************************************************************/
//
///******************************************************************/
///*kapheinThrdThreadPoolWorker Declarations*/
//
//struct kapheinThrdThreadPoolWorker
//{
//    HANDLE thread_;
//
//    HANDLE workerStartedResetEvent_;
//
//    HANDLE wokeUpResetEvent_;
//
//    HANDLE workCompletedResetEvent_;
//
//    HANDLE idleResetEvent_;
//    
//    struct kapheinThrdThreadPool *pool_;
//
//    kapheinHandle thisLock_;
//
//    struct kapheinThrdThreadPoolWork *work_;
//
//    int index_;
//
//    bool isAlive_;
//
//    bool isBusy_;
//};
//
//static int kapheinThrdThreadPoolWorkerConstruct(
//    struct kapheinThrdThreadPoolWorker *worker
//    , struct kapheinThrdThreadPool *pool
//    , int index
//);
//
//static int kapheinThrdThreadPoolWorkerDestruct(
//    struct kapheinThrdThreadPoolWorker *worker
//);
//
//static int kapheinThrdThreadPoolWorkerIsBusy(
//    struct kapheinThrdThreadPoolWorker *worker
//    , bool *truthOut
//);
//
//static int kapheinThrdThreadPoolWorkerTryStartWork(
//    struct kapheinThrdThreadPoolWorker *worker
//    , struct kapheinThrdThreadPoolWork *work
//);
//
//static unsigned int KAPHEIN_STDCALL kapheinThrdThreadPoolWorkerMain(
//    void *param
//);
//
///******************************************************************/
//
///******************************************************************/
///*kapheinThrdThreadPool Declarations*/
//
//struct kapheinThrdThreadPool
//{
//    kapheinHandle allocator_;
//
//    kapheinHandle thisLock_;
//
//    kapheinHandle workQueueLock_;
//
//    kapheinHandle workQueue_;
//
//    HANDLE workDispatcherThread_;
//
//    HANDLE workQueueEmptyResetEvent_;
//
//    struct kapheinThrdThreadPoolWorker *workers_;
//    
//    int workerCount_;
//
//    int workerCursor_;
//    
//    int state_;
//};
//
//static unsigned int KAPHEIN_STDCALL kapheinThrdThreadPoolWorkDispatcherMain(
//    void *param
//);
//
///******************************************************************/
//
///******************************************************************/
///*kapheinThrdThreadPool Definitions*/
//
//int kapheinThrdThreadPoolConstruct(
//    kapheinHandle *handleOut
//    , kapheinHandle allocator
//    , int workerCount
//)
//{
//    struct kapheinThrdThreadPool *pool;
//    int errorCode = kapheinErrorCodeNoError;
//    int i;
//
//    if(handleOut == NULL) {
//        return kapheinErrorCodeArgumentNull;
//    }
//
//    *handleOut = NULL;
//
//    if(workerCount < 1 || workerCount > INT_MAX - 1) {
//        return kapheinErrorCodeArgumentOutOfRange;
//    }
//
//    pool = (struct kapheinThrdThreadPool *)kapheinMemAllocatorAllocate(
//        allocator
//        , sizeof(*pool->workers_) * workerCount
//        , NULL
//        , &errorCode
//    );
//    if(pool == NULL) {
//        return errorCode;
//    }
//    pool->allocator_ = allocator;
//    pool->workerCount_ = workerCount;
//    pool->workerCursor_ = 0;
//
//    pool->workQueueEmptyResetEvent_ = CreateEvent(NULL, TRUE, FALSE, NULL);
//    if(pool->workQueueEmptyResetEvent_ == NULL) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return errorCode;
//    }
//
//    errorCode = kapheinCollListConstruct(&pool->workQueue_, allocator);
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return errorCode;
//    }
//
//    errorCode = kapheinThrdMutexConstruct(&pool->workQueueLock_, allocator);
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return errorCode;
//    }
//
//    errorCode = kapheinThrdMutexConstruct(&pool->thisLock_, allocator);
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return errorCode;
//    }
//
//    pool->workers_ = (struct kapheinThrdThreadPoolWorker *)kapheinMemAllocatorAllocate(
//        pool->allocator_
//        , sizeof(*pool->workers_) * workerCount
//        , NULL
//        , &errorCode
//    );
//    if(pool->workers_ == NULL) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return errorCode;
//    }
//    for(i = workerCount; i > 0; ) {
//        --i;
//
//        errorCode = kapheinThrdThreadPoolWorkerConstruct(pool->workers_ + i, pool, i);
//        if(errorCode != kapheinErrorCodeNoError) {
//            kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//            return errorCode;
//        }
//    }
//
//    pool->state_ = 0;
//    pool->workDispatcherThread_ = (HANDLE)_beginthreadex(
//        NULL
//        , 0
//        , kapheinThrdThreadPoolWorkDispatcherMain
//        , pool
//        , 0
//        , NULL
//    );
//    if(pool->workDispatcherThread_ == NULL) {
//        kapheinThrdThreadPoolDestruct((kapheinHandle)pool);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//
//    *handleOut = pool;
//
//    return kapheinErrorCodeNoError;
//}
//
//int kapheinThrdThreadPoolDestruct(
//    kapheinHandle handle
//)
//{
//    struct kapheinThrdThreadPool *pool = (struct kapheinThrdThreadPool *)handle;
//    int errorCode = kapheinErrorCodeNoError;
//    int i;
//
//    if(pool == NULL) {
//        kapheinErrorCodeArgumentNull;
//    }
//
//    errorCode = kapheinThrdThreadPoolJoinAll(handle, -1);
//    if(errorCode != kapheinErrorCodeNoError) {
//        return errorCode;
//    }
//
//    if(pool->workDispatcherThread_ != NULL) {
//        while(pool->state_ >= 0) {
//            pool->state_ = -1;
//        }
//        WaitForSingleObject(pool->workDispatcherThread_, INFINITE);
//
//        pool->workDispatcherThread_ = NULL;
//    }
//
//    if(pool->workQueueLock_ != NULL) {
//        kapheinThrdMutexDestruct(pool->workQueueLock_);
//        pool->workQueueLock_ = NULL;
//    }
//
//    if(pool->workQueue_ != NULL) {
//        kapheinCollListDestruct(pool->workQueue_);
//        pool->workQueue_ = NULL;
//    }
//
//    if(pool->workers_ != NULL) {
//        for(i = pool->workerCount_; i > 0; ) {
//            --i;
//
//            kapheinThrdThreadPoolWorkerDestruct(pool->workers_ + 1);
//        }
//        kapheinMemAllocatorDeallocate(pool->allocator_, pool->workers_, sizeof(*pool->workers_) * pool->workerCount_);
//        pool->workers_ = NULL;
//    }
//
//    if(pool->thisLock_ != NULL) {
//        kapheinThrdMutexDestruct(pool->thisLock_);
//        pool->thisLock_ = NULL;
//    }
//
//    if(pool->workQueueEmptyResetEvent_ != NULL) {
//        CloseHandle(pool->workQueueEmptyResetEvent_);
//        pool->workQueueEmptyResetEvent_ = NULL;
//    }
//
//    kapheinMemAllocatorDeallocate(pool->allocator_, pool, sizeof(*pool));
//
//    return kapheinErrorCodeNoError;
//}
//
//int kapheinThrdThreadPoolQueueWork(
//    kapheinHandle handle
//    , int waitMilliseconds
//    , kapheinThrdThreadPoolWorkFunction *pWorkFunc
//    , void *param
//)
//{
//    struct kapheinThrdThreadPool *pool = (struct kapheinThrdThreadPool *)handle;
//    struct kapheinThrdThreadPoolWork *work = NULL;
//    int errorCode = kapheinErrorCodeNoError;
//
//    if(pool == NULL) {
//        kapheinErrorCodeArgumentNull;
//    }
//
//    errorCode = kapheinThrdMutexLock(pool->thisLock_, waitMilliseconds);
//    if(errorCode != kapheinErrorCodeNoError) {
//        return errorCode;
//    }
//
//    errorCode = kapheinThrdMutexLock(pool->workQueueLock_, waitMilliseconds);
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdMutexUnlock(pool->thisLock_);
//        
//        return errorCode;
//    }
//
//    work = (struct kapheinThrdThreadPoolWork *)kapheinMemAllocatorAllocate(
//        pool->allocator_
//        , sizeof(*work)
//        , NULL
//        , &errorCode
//    );
//    if(work != NULL) {
//        work->pFunc_ = pWorkFunc;
//        work->param_ = param;
//        work->result_ = 0;
//        
//        kapheinCollListPushBack(pool->workQueue_, work);
//    }
//
//    kapheinThrdMutexUnlock(pool->workQueueLock_);
//
//    kapheinThrdMutexUnlock(pool->thisLock_);
//
//    return kapheinErrorCodeNoError;
//}
//
//int kapheinThrdThreadPoolJoinAll(
//    kapheinHandle handle
//    , int waitMilliseconds
//)
//{
//    struct kapheinThrdThreadPool *pool = (struct kapheinThrdThreadPool *)handle;
//    DWORD waitResult;
//    int errorCode = kapheinErrorCodeNoError;
//    int i;
//    bool isWorkerBusy = false;
//
//    if(pool == NULL) {
//        kapheinErrorCodeArgumentNull;
//    }
//
//    errorCode = kapheinThrdMutexLock(pool->thisLock_, waitMilliseconds);
//    if(errorCode != kapheinErrorCodeNoError) {
//        return errorCode;
//    }
//
//    ResetEvent(pool->workQueueEmptyResetEvent_);
//    waitResult = WaitForSingleObject(pool->workQueueEmptyResetEvent_, waitMilliseconds);
//    switch(waitResult) {
//    case WAIT_OBJECT_0:
//        errorCode = kapheinErrorCodeNoError;
//    break;
//    case WAIT_TIMEOUT:
//        errorCode = kapheinErrorCodeOperationTimeout;
//    break;
//    case WAIT_ABANDONED:
//        errorCode = kapheinErrorCodeOperationInvalid;
//    break;
//    case WAIT_FAILED:
//        errorCode = kapheinErrorCodeOperationInvalid;
//    break;
//    }
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdMutexUnlock(pool->thisLock_);
//
//        return errorCode;
//    }
//
//    for(i = pool->workerCount_; i > 0; ) {
//        --i;
//        
//        ResetEvent(pool->workers_[i].idleResetEvent_);
//        kapheinThrdThreadPoolWorkerIsBusy(pool->workers_ + i, &isWorkerBusy);
//        if(isWorkerBusy) {
//            WaitForSingleObject(pool->workers_[i].workCompletedResetEvent_, INFINITE);
//        }
//        SetEvent(pool->workers_[i].wokeUpResetEvent_);
//        WaitForSingleObject(pool->workers_[i].idleResetEvent_, INFINITE);
//    }
//
//    kapheinThrdMutexUnlock(pool->thisLock_);
//
//    return kapheinErrorCodeNoError;
//}
//
//static unsigned int KAPHEIN_STDCALL kapheinThrdThreadPoolWorkDispatcherMain(
//    void *param
//)
//{
//    struct kapheinThrdThreadPool *pool = (struct kapheinThrdThreadPool *)param;
//    struct kapheinThrdThreadPoolWork *work = NULL;
//    void *listElement;
//    int errorCode = kapheinErrorCodeNoError;
//    int i;
//    int workerCursor = 0;
//    int availableWorkerIndex;
//    int count;
//
//    while(pool->state_ >= 0) {
//        switch(pool->state_) {
//        case 0:
//            kapheinThrdMutexLock(pool->workQueueLock_, -1);
//
//            if(kapheinCollListPopFront(pool->workQueue_, &listElement) == kapheinErrorCodeNoError) {
//                work = (struct kapheinThrdThreadPoolWork *)listElement;
//
//                pool->state_ = 1;
//            }
//
//            kapheinCollListGetCount(pool->workQueue_, &count);
//            if(count < 1) {
//                SetEvent(pool->workQueueEmptyResetEvent_);
//            }
//            else {
//                //printf("Remaining work count == %d\r\n", count);
//            }
//
//            kapheinThrdMutexUnlock(pool->workQueueLock_);
//
//            if(work == NULL) {
//                Sleep(1);
//            }
//        break;
//        case 1:
//            availableWorkerIndex = -1;
//            i = workerCursor;
//            do {
//                errorCode = kapheinThrdThreadPoolWorkerTryStartWork(pool->workers_ + i, work);
//
//                ++i;
//                if(i >= pool->workerCount_) {
//                    i -= pool->workerCount_;
//                }
//
//                if(errorCode == kapheinErrorCodeNoError) {
//                    work = NULL;
//
//                    workerCursor = i;
//                    pool->state_ = 0;
//                }
//            }
//            while(i != workerCursor);
//        break;
//        }
//    }
//
//    if(work != NULL) {
//        kapheinMemAllocatorDeallocate(pool->allocator_, work, sizeof(*work));
//
//        work = NULL;
//    }
//    
//    kapheinThrdMutexLock(pool->workQueueLock_, -1);
//
//    while(kapheinCollListPopFront(pool->workQueue_, &listElement) == kapheinErrorCodeNoError) {
//        work = (struct kapheinThrdThreadPoolWork *)listElement;
//
//        if(work != NULL) {
//            kapheinMemAllocatorDeallocate(pool->allocator_, work, sizeof(*work));
//
//            work = NULL;
//        }
//    }
//
//    kapheinThrdMutexUnlock(pool->workQueueLock_);
//    
//    return 0;
//}
//
///******************************************************************/
//
///******************************************************************/
///*kapheinThrdThreadPoolWorker Definitions*/
//
//static int kapheinThrdThreadPoolWorkerConstruct(
//    struct kapheinThrdThreadPoolWorker *worker
//    , struct kapheinThrdThreadPool *pool
//    , int index
//)
//{
//    int errorCode = kapheinErrorCodeNoError;
//    
//    worker->pool_ = pool;
//    worker->index_ = index;
//    worker->work_ = NULL;
//    worker->isAlive_ = true;
//    worker->isBusy_ = false;
//
//    errorCode = kapheinThrdMutexConstruct(&worker->thisLock_, pool->allocator_);
//    if(errorCode != kapheinErrorCodeNoError) {
//        return errorCode;
//    }
//
//    worker->workerStartedResetEvent_ = CreateEvent(NULL, TRUE, FALSE, NULL);
//    if(worker->workerStartedResetEvent_ == NULL) {
//        kapheinThrdThreadPoolWorkerDestruct(worker);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//
//    worker->wokeUpResetEvent_ = CreateEvent(NULL, TRUE, FALSE, NULL);
//    if(worker->wokeUpResetEvent_ == NULL) {
//        kapheinThrdThreadPoolWorkerDestruct(worker);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//
//    worker->workCompletedResetEvent_ = CreateEvent(NULL, TRUE, FALSE, NULL);
//    if(worker->workCompletedResetEvent_ == NULL) {
//        kapheinThrdThreadPoolWorkerDestruct(worker);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//    
//    worker->idleResetEvent_ = CreateEvent(NULL, TRUE, FALSE, NULL);
//    if(worker->idleResetEvent_ == NULL) {
//        kapheinThrdThreadPoolWorkerDestruct(worker);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//
//    worker->thread_ = (HANDLE)_beginthreadex(
//        NULL
//        , 0
//        , kapheinThrdThreadPoolWorkerMain
//        , worker
//        , 0
//        , NULL
//    );
//    if(worker->thread_ == NULL) {
//        kapheinThrdThreadPoolWorkerDestruct(worker);
//
//        return kapheinErrorCodePlatformResourceAllocationFailed;
//    }
//
//    WaitForSingleObject(worker->workerStartedResetEvent_, INFINITE);
//
//    return kapheinErrorCodeNoError;
//};
//
//static int kapheinThrdThreadPoolWorkerDestruct(
//    struct kapheinThrdThreadPoolWorker *worker
//)
//{
//    worker->isAlive_ = false;
//
//    if(worker->wokeUpResetEvent_ != NULL) {
//        SetEvent(worker->wokeUpResetEvent_);
//    }
//
//    if(worker->thread_ != NULL) {
//        WaitForSingleObject(worker->thread_, INFINITE);
//    }
//
//    if(worker->workCompletedResetEvent_ != NULL) {
//        CloseHandle(worker->workCompletedResetEvent_);
//        worker->workCompletedResetEvent_ = NULL;
//    }
//
//    if(worker->wokeUpResetEvent_ != NULL) {
//        CloseHandle(worker->wokeUpResetEvent_);
//        worker->wokeUpResetEvent_ = NULL;
//    }
//
//    if(worker->idleResetEvent_ != NULL) {
//        CloseHandle(worker->idleResetEvent_);
//        worker->idleResetEvent_ = NULL;
//    }
//
//    if(worker->workerStartedResetEvent_ != NULL) {
//        CloseHandle(worker->workerStartedResetEvent_);
//        worker->workerStartedResetEvent_ = NULL;
//    }
//
//    if(worker->thisLock_ != NULL) {
//        kapheinThrdMutexDestruct(worker->thisLock_);
//        worker->thisLock_ = NULL;
//    }
//
//    return kapheinErrorCodeNoError;
//};
//
//static int kapheinThrdThreadPoolWorkerIsBusy(
//    struct kapheinThrdThreadPoolWorker *worker
//    , bool *truthOut
//)
//{
//    int errorCode = kapheinErrorCodeNoError;
//    errorCode = kapheinThrdMutexLock(worker->thisLock_, -1);
//
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdMutexUnlock(worker->thisLock_);
//        return errorCode;
//    }
//
//    *truthOut = worker->isBusy_;
//    
//    kapheinThrdMutexUnlock(worker->thisLock_);
//
//    return kapheinErrorCodeNoError;
//}
//
//static int kapheinThrdThreadPoolWorkerTryStartWork(
//    struct kapheinThrdThreadPoolWorker *worker
//    , struct kapheinThrdThreadPoolWork *work
//)
//{
//    int errorCode = kapheinErrorCodeNoError;
//
//    errorCode = kapheinThrdMutexLock(worker->thisLock_, -1);
//    if(errorCode != kapheinErrorCodeNoError) {
//        kapheinThrdMutexUnlock(worker->thisLock_);
//        return errorCode;
//    }
//    
//    if(!worker->isAlive_) {
//        kapheinThrdMutexUnlock(worker->thisLock_);
//        return kapheinErrorCodeOperationInvalid;
//    }
//
//    if(worker->isBusy_) {
//        kapheinThrdMutexUnlock(worker->thisLock_);
//        return kapheinErrorCodeOperationInvalid;
//    }
//
//    worker->work_ = work;
//    SetEvent(worker->wokeUpResetEvent_);
//
//    kapheinThrdMutexUnlock(worker->thisLock_);
//
//    return kapheinErrorCodeNoError;
//}
//
//static unsigned int KAPHEIN_STDCALL kapheinThrdThreadPoolWorkerMain(
//    void *param
//)
//{
//    struct kapheinThrdThreadPoolWorker *worker = (struct kapheinThrdThreadPoolWorker *)param;
//    DWORD waitResult;
//    bool isRunning;
//
//    ResetEvent(worker->wokeUpResetEvent_);
//    
//    SetEvent(worker->workerStartedResetEvent_);
//
//    for(isRunning = true; isRunning; ) {
//        waitResult = WaitForSingleObject(worker->wokeUpResetEvent_, INFINITE);
//        switch(waitResult) {
//        case WAIT_OBJECT_0:
//            ResetEvent(worker->wokeUpResetEvent_);
//
//            if(!worker->isAlive_) {
//                isRunning = false;
//            }
//            
//            if(worker->isAlive_ && worker->work_ != NULL && worker->work_->pFunc_ != NULL) {
//                kapheinThrdMutexLock(worker->thisLock_, -1);
//                worker->isBusy_ = true;
//                kapheinThrdMutexUnlock(worker->thisLock_);
//
//                worker->work_->result_ = (*worker->work_->pFunc_)(worker->work_->param_);
//
//                kapheinMemAllocatorDeallocate(worker->pool_->allocator_, worker->work_, sizeof(*worker->work_));
//                worker->work_ = NULL;
//                
//                kapheinThrdMutexLock(worker->thisLock_, -1);
//                worker->isBusy_ = false;
//                kapheinThrdMutexUnlock(worker->thisLock_);
//
//                SetEvent(worker->workCompletedResetEvent_);
//                Sleep(0);
//            }
//            else {
//                SetEvent(worker->idleResetEvent_);
//            }
//        break;
//        case WAIT_ABANDONED:
//        case WAIT_FAILED:
//            isRunning = false;
//        break;
//        }
//    }
//
//    worker->isAlive_ =  false;
//
//    return 0;
//}
//
///******************************************************************/

typedef int kapheinSuppressEmptyFileWarning;
