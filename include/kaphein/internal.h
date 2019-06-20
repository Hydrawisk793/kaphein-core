#ifndef KAPHEIN_INTERNAL_H
#define KAPHEIN_INTERNAL_H

#include "kaphein/def.h"

size_t kapheinStrlen(
    const char *str
);

int kapheinMemcpyS(
    void *dest
    , int destSize
    , const void *src
    , int count
);

int kapheinMemsetS(
    void *dest
    , int destSize
    , int value
    , int count
);

#endif
