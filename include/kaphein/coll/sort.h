#ifndef KAPHEIN_HGRD_kaphein_sort_h
#define KAPHEIN_HGRD_kaphein_sort_h

#include "../def.h"
#include "../ErrorCode.h"
#include "def.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_sortBySelection(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_sortByBubble(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_coll_sortByInsertion(
    const struct kaphein_coll_ElementTrait * elementTrait
    , void * elements
    , kaphein_SSize elementCount
);

#endif
