#ifndef KAPHEIN_THRD_ThreadPool_H
#define KAPHEIN_THRD_ThreadPool_H

/*
#include "kaphein/def.h"

KAPHEIN_C_LINKAGE_BEGIN()

typedef int (KAPHEIN_STDCALL kapheinThrdThreadPoolWorkFunction) (
    void *param
);

int kapheinThrdThreadPoolConstruct(
    kapheinHandle *handleOut
    , kapheinHandle allocator
    , int workerCount
);

int kapheinThrdThreadPoolDestruct(
    kapheinHandle handle
);

int kapheinThrdThreadPoolQueueWork(
    kapheinHandle handle
    , int waitMilliseconds
    , kapheinThrdThreadPoolWorkFunction *pWorkFunc
    , void *param
);

int kapheinThrdThreadPoolJoinAll(
    kapheinHandle handle
    , int waitMilliseconds
);

KAPHEIN_C_LINKAGE_END()
*/

#endif
