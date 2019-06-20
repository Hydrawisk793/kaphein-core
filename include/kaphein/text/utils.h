#ifndef KAPHEIN_HGRD_kaphein_text_utils_h
#define KAPHEIN_HGRD_kaphein_text_utils_h

#include "../ErrorCode.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_parseInt32(
    const char * text
    , kaphein_SSize textSize
    , int radix
    , kaphein_SSize * endIndexOut
    , kaphein_IntLeast32 * valueOut
);

#endif
