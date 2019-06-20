#ifndef KAPHEIN_HGRD_kaphein_text_base64_h
#define KAPHEIN_HGRD_kaphein_text_base64_h

#include "../def.h"
#include "../ErrorCode.h"

/**
 *  @brief Encodes an array of plain bytes to a base64-encoded string.
 *  @param input 
 *  @param inputSize 
 *  @param[out] output 
 *  @param[in,out] outputSizeInOut 
 *  @return An error code.
 *  @since 2017-05-13
 */
KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_convertBytesToBase64(
    const char * input
    , kaphein_SSize inputSize
    , char * output
    , kaphein_SSize * outputSizeInOut
);

/**
 *  @brief Decodes a base64-encoded string to an array of plain bytes.
 *  @param input 
 *  @param inputSize 
 *  @param[out] output 
 *  @param[in,out] outputSizeInOut 
 *  @return An error code.
 *  @since 2017-05-13
 */
KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_convertBase64ToBytes(
    const char * input
    , kaphein_SSize inputSize
    , char * output
    , kaphein_SSize * outputSizeInOut
);

#endif
