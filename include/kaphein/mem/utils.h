#ifndef KAPHEIN_HGRD_kaphein_mem_utils_h
#define KAPHEIN_HGRD_kaphein_mem_utils_h

#include "../def.h"
#include "Allocator.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Copies a memory block to another.
 *  @param[out] dest A memory block to hold the copied bytes.
 *  @param destSize The number of bytes of dest parameter.
 *  @param src A memory block to copy.
 *  @param count The number of bytes to copy.
 *  @return An error code defined in ::kaphein_ErrorCode enum.
 */
enum kaphein_ErrorCode
kaphein_mem_copy(
    void * dest
    , kaphein_SSize destSize
    , const void * src
    , kaphein_SSize count
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Fills a memory block with zero.
 *  @param[out] dest A memory block.
 *  @param destSize The size of dest parameter.
 *  @param count The number of bytes to fill.
 *  @return An error code defined in ::kaphein_ErrorCode enum.
 */
enum kaphein_ErrorCode
kaphein_mem_fillZero(
    void * dest
    , kaphein_SSize destSize
    , kaphein_SSize count
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Fills a memory block with the specified byte value.
 *  @param[out] dest A memory block.
 *  @param destSize The size of dest parameter.
 *  @param value A byte value.
 *  @param count The number of bytes to fill.
 *  @return An error code defined in ::kaphein_ErrorCode enum.
 */
enum kaphein_ErrorCode
kaphein_mem_fill(
    void * dest
    , kaphein_SSize destSize
    , int value
    , kaphein_SSize count
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int
kaphein_mem_compare(
    const void * lhs
    , kaphein_SSize lhsSize
    , const void * rhs
    , kaphein_SSize rhsSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void *
kaphein_mem_allocate(
    struct kaphein_mem_Allocator * allocator
    , kaphein_SSize memorySize
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_mem_deallocate(
    struct kaphein_mem_Allocator * allocator
    , void * memory
    , kaphein_SSize memorySize
);

#endif
