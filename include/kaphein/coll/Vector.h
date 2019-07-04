#ifndef KAPHEIN_HGRD_kaphein_coll_Vector_h
#define KAPHEIN_HGRD_kaphein_coll_Vector_h

#include "../mem/Allocator.h"
#include "def.h"

/**
 *  @brief A sequence collection that holds variable number of elements.
 */
struct kaphein_coll_Vector
{
    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Constructs a new vector.
 *  @param thisObj 
 *  @param initialCapacity The initial size of the container of the vector.
 *  @param elementTrait An elementTrait struct that describes element operations in the vector.
 *  <br/>The element trait struct must provide following operations.
 *  <br/>- copyConstruct
 *  <br/>- destruct
 *  @param allocator Optional. An allocator to manage internal memory allocations.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_construct(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize initialCapacity
    , const struct kaphein_coll_ElementTrait * elementTrait
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_destruct(
    struct kaphein_coll_Vector * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Gets the current capacity of the vector.
 *  @param thisObj 
 *  @param[out] capacityOut 
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_getCapacity(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * capacityOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Changes the size of the internal container of the vector.
 *  @details If the new size value is less than current capacity, overflowing elements will be removed.
 *  @param thisObj 
 *  @param size 
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_resize(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
/**
 *  @brief Reserves extra spaces of the container of the vector.
 *  @param thisObj 
 *  @param size 
 *  @return An error code.
 */
kaphein_coll_Vector_reserve(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize size
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Shrinks the size of the container of the vector.
 *  @param thisObj 
 *  @param size 
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_trim(
    struct kaphein_coll_Vector * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_getPointerToElements(
    const struct kaphein_coll_Vector * thisObj
    , void ** pointerOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_isEmpty(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_isFull(
    const struct kaphein_coll_Vector * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_getCount(
    const struct kaphein_coll_Vector * thisObj
    , kaphein_SSize * countOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_pushFront(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_popFront(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_pushBack(
    struct kaphein_coll_Vector * thisObj
    , const void * element
    , kaphein_SSize elementSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_Vector_popBack(
    struct kaphein_coll_Vector * thisObj
    , void * elementOut
    , kaphein_SSize elementOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Inserts one or more elements at the specified index.
 *  @param thisObj 
 *  @param startIndex 
 *  @param elements A pointer to the start of one or more elements.
 *  @param elementSize 
 *  @param elementCount 
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_insert(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize startIndex
    , const void * elements
    , kaphein_SSize elementSize
    , kaphein_SSize elementCount
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Removes one or more elements at the specified index.
 *  @param thisObj 
 *  @param index 
 *  @param count 
 *  @param elementsOut[out] Optional. The removed one or more elements will be copied to here.
 *  @param elementsOutSize The size of the buffer pointed by elementsOut parameter.
 *  <br/>If elementsOut is null, this parameter will be ignored.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_remove(
    struct kaphein_coll_Vector * thisObj
    , kaphein_SSize index
    , kaphein_SSize count
    , void * elementsOut
    , kaphein_SSize elementsOutSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Removes all elements in the vector.
 *  @param thisObj 
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_coll_Vector_clear(
    struct kaphein_coll_Vector * thisObj
);

#endif
