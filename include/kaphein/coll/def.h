#ifndef KAPHEIN_HGRD_kaphein_coll_def_h
#define KAPHEIN_HGRD_kaphein_coll_def_h

#include "../mem/Allocator.h"

typedef
int
kaphein_coll_compareFunction(
    const void * lhs
    , const void * rhs
);

typedef
void
kaphein_coll_swapFunction(
    void * lhs
    , void * rhs
);

struct kaphein_coll_ElementTrait
{
    kaphein_SSize elementSize;

    kaphein_copyConstructFunction * copyConstruct;

    kaphein_destructFunction * destruct;

    kaphein_coll_swapFunction * swap;

    kaphein_coll_compareFunction * compare;
};

#endif
