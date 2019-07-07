#ifndef KAPHEIN_HGRD_kaphein_coll_Iterator_h
#define KAPHEIN_HGRD_kaphein_coll_Iterator_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_coll_Iterator_VTable
{
    kaphein_copyConstructFunction * copyConstruct;
    
    kaphein_destructFunction * destruct;

    enum kaphein_ErrorCode
    (* copyAssign) (
        void * thisObj
        , const void * src
    );

    void *
    (* dereference) (
        const void * thisObj
        , enum kaphein_ErrorCode * errorCodeOut
    );

    const void *
    (* dereferenceConst) (
        const void * thisObj
        , enum kaphein_ErrorCode * errorCodeOut
    );

    enum kaphein_ErrorCode
    (* compareTo) (
        const void * thisObj
        , const void * other
        , int * resultOut
    );

    enum kaphein_ErrorCode
    (* hasReachedBegin) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* hasReachedEnd) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* reset) (
        void * thisObj
    );

    bool
    (* moveToNext) (
        void * thisObj
        , enum kaphein_ErrorCode * errorCodeOut
    );

    bool
    (* moveToPrevious) (
        void * thisObj
        , enum kaphein_ErrorCode * errorCodeOut
    );

    bool
    (* move) (
        void * thisObj
        , kaphein_SSize amount
        , enum kaphein_ErrorCode * errorCodeOut
    );
};

struct kaphein_coll_Iterator
{
    void * thisObj;

    const struct kaphein_coll_Iterator_VTable * vTable;
};

#endif
