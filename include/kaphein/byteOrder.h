#ifndef KAPHEIN_BYTEORDER_H
#define KAPHEIN_BYTEORDER_H

#include "kaphein/def.h"

enum kapheinByteOrder
{
    kapheinByteOrderBigEndian = 0
    , kapheinByteOrderLittleEndian = 1
};

/**
 *  @brief Dynamically determines the byte order of this system.
 */
KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kapheinByteOrder kapheinGetByteOrder();

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinConvertByteOrder16(
    uint16_t *v
    , int size
    , int byteOrder
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinConvertByteOrder32(
    uint32_t *v
    , int size
    , int byteOrder
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinConvertByteOrder64(
    uint64_t *v
    , int size
    , int byteOrder
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinHostOrderToNetworkOrder16(
    uint16_t *v
    , int size
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinHostOrderToNetworkOrder32(
    uint32_t *v
    , int size
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinHostOrderToNetworkOrder64(
    uint64_t *v
    , int size
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinNetworkOrderToHostOrder16(
    uint16_t *v
    , int size
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinNetworkOrderToHostOrder32(
    uint32_t *v
    , int size
);

//KAPHEIN_ATTRIBUTE_C_LINKAGE
//KAPHEIN_ATTRIBUTE_DLL_API
int kapheinNetworkOrderToHostOrder64(
    uint64_t *v
    , int size
);

#endif
