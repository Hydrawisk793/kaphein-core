#ifndef KAPHEIN_HGRD_kaphein_ppgen_IntegerTypeTraits_h
#define KAPHEIN_HGRD_kaphein_ppgen_IntegerTypeTraits_h

#include "../def.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_ppgen_GenerateIntegerTypeTraitMacros(
    const char * filePath
    , kaphein_SSize filePathSize
    , int maximumBitSize
);

#endif
