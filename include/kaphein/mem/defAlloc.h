#ifndef KAPHEIN_HGRD_kaphein_mem_defAlloc_h
#define KAPHEIN_HGRD_kaphein_mem_defAlloc_h

#include "../ErrorCode.h"

void *
kaphein_mem_defaultAllocate(
    kaphein_SSize memorySize
    , void * hint
    , enum kaphein_ErrorCode * errorCodeOut
);

enum kaphein_ErrorCode
kaphein_mem_defaultDeallocate(
    void * memory
    , kaphein_SSize memorySize
);

#endif
