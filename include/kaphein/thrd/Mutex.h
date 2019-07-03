#ifndef KAPHEIN_HGRD_kaphein_thrd_Mutex_h
#define KAPHEIN_HGRD_kaphein_thrd_Mutex_h

#include "../def.h"
#include "../ErrorCode.h"
#include "../mem/Allocator.h"

/**
 *  @brief Represents mutex objects that are used to protect shared data from being simultaneously accessed by multiple threads.
 */
struct kaphein_thrd_Mutex
{
    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Constructs a mutex.
 *  @param[in,out] thisObjOut A mutex to construct.
 *  @param allocator An optional allocator for internal memory allocations.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_thrd_Mutex_construct(
    struct kaphein_thrd_Mutex * thisObj
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Destructs the specified mutex.
 *  @param thisObj A mutex to destruct.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_thrd_Mutex_destruct(
    struct kaphein_thrd_Mutex * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Gets the implementation-specific internal handle.
 *  @param thisObj A mutex.
 *  @param[out] The internal handle.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_thrd_Mutex_getInternalHandle(
    struct kaphein_thrd_Mutex * thisObj
    , void ** handleOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Locks the mutex.
 *  @param thisObj A mutex.
 *  @param waitMilliseconds The number of milliseconds to wait.
 *  <br/>If the value is negative, this function waits infinitely until the mutex is locked.
 *  <br/>If the value is zero, this function tries to lock the mutex and returns immediately whether locking is succeeded or not.
 *  @return An error code.
 *  <br/>- kapheinErrorCodeNoError : Locking has been succeeded.
 *  <br/>- kapheinErrorCodeArgumentNull : thisObj parameter is null.
 *  <br/>- kapheinErrorCodeOperationTimeout : The mutex couldn't be locked in the specified time.
 *  <br/>- kapheinErrorCodeOperationInvalid : The mutex is invalid and cannot be used anymore.
 *  <br/>In this case, users should destruct the mutex by calling ::kapheinThrdMutexDestruct function.
 */
enum kaphein_ErrorCode
kaphein_thrd_Mutex_lock(
    struct kaphein_thrd_Mutex * thisObj
    , int waitMilliseconds
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Unlocks the mutex.
 *  @param thisObj A mutex.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_thrd_Mutex_unlock(
    struct kaphein_thrd_Mutex * thisObj
);

#endif
