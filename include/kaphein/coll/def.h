#ifndef KAPHEIN_HGRD_kaphein_coll_def_h
#define KAPHEIN_HGRD_kaphein_coll_def_h

#include "../mem/Allocator.h"

typedef int kaphein_coll_compareFunction(
    const void * lhs
    , const void * rhs
);

typedef void kaphein_coll_swapFunction(
    void * lhs
    , void * rhs
);

struct kaphein_coll_ElementTrait
{
    kaphein_SSize elementSize;

    enum kaphein_ErrorCode
    (* copyConstruct) (
        void * objOut
        , const void * src
        , struct kaphein_mem_Allocator * allocator
    );

    enum kaphein_ErrorCode
    (* destruct) (
        void * obj
    );

    kaphein_coll_swapFunction * swap;

    kaphein_coll_compareFunction * compare;
};

#endif
