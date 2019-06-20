#ifndef KAPHEIN_THRD_INTERNAL_H
#define KAPHEIN_THRD_INTERNAL_H

#include "kaphein/def.h"
#if KAPHEIN_THREAD_MODEL != KAPHEIN_THREAD_MODEL_UNKNOWN
    #if defined(KAPHEIN_PLATFORM_WINDOWS)
        #include <Windows.h>
    #elif defined(KAPHEIN_PLATFORM_UNIX) || defined(KAPHEIN_PLATFORM_LINUX)
        #include <unistd.h>
    #endif
#endif
#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
    #include <Windows.h>
#elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
    #include <pthread.h>
    #include "kaphein/thrd/Mutex.h"
#endif

struct kapheinThrdMutex
{
#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
    HANDLE handle_;
#elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
    pthread_mutex_t mutex_;
#else
    void *dummy_;
#endif
};

struct kapheinThrdResetEvent
{
#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_WINTHREAD
    HANDLE handle_;
#elif KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
    struct kapheinThrdMutex mutex_;
    pthread_cond_t cv_;
    volatile bool isSet_;
#else
    void *dummy_;
#endif
};

#if KAPHEIN_THREAD_MODEL == KAPHEIN_THREAD_MODEL_PTHREAD
int kapheinThrdMillisecondsToTimespec(
    int milliseconds
    , struct timespec *tsOut
);
#endif

#endif
