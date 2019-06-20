#ifndef KAPHEIN_HGRD_kaphein_text_encoding_h
#define KAPHEIN_HGRD_kaphein_text_encoding_h

#include "../def.h"
#include "../ErrorCode.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Converts an UTF-8 text to an UTF-16 text.
 *  @param utf8Text An UTF-8 text.
 *  @param utf8TextSize The size of utf8Text parameter.
 *  @param[out] utf16TextOut The converted UTF-16 text.
 *  @param[in,out] utf16TextSizeInOut On input, the value is the size of utf16TextOut parameter.
 *  <br/>On output, the actual size of the output UTF-16 text will be returned.
 *  @return An error code defined in ::kaphein_ErrorCode enum.
 */
enum kaphein_ErrorCode
kaphein_text_convertUtf8ToUtf16(
    const char * utf8Text
    , kaphein_SSize utf8TextSize
    , kaphein_UIntLeast16 * utf16TextOut
    , kaphein_SSize * utf16TextSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Converts an UTF-16 text to an UTF-8 text.
 *  @param utf16Text An UTF-16 text.
 *  @param utf16TextSize The size of utf16Text parameter.
 *  @param[out] utf8TextOut The converted UTF-8 text.
 *  @param[in,out] utf8TextSizeInOut On input, the value is the size of utf8TextOut parameter.
 *  <br/>On output, the actual size of the output UTF-8 text will be returned.
 *  @return An error code defined in ::kaphein_ErrorCode enum.
 */
enum kaphein_ErrorCode
kaphein_text_convertUtf16ToUtf8(
    const kaphein_UIntLeast16 * utf16Text
    , kaphein_SSize utf16TextSize
    , char * utf8TextOut
    , kaphein_SSize *utf8TextSizeInOut
);

#endif
