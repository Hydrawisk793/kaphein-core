#ifndef KAPHEIN_HGRD_kaphein_mem_Allocator_h
#define KAPHEIN_HGRD_kaphein_mem_Allocator_h

#include "../def.h"
#include "../ErrorCode.h"

struct kaphein_mem_Allocator_VTable
{
    enum kaphein_ErrorCode
    (* destruct) (
        void * thisObj
    );

    void *
    (* allocate) (
        void * thisObj
        , kaphein_SSize memorySize
        , void * hint
        , enum kaphein_ErrorCode * errorCodeOut
    );

    enum kaphein_ErrorCode
    (* deallocate) (
        void * thisObj
        , void * memory
        , kaphein_SSize memorySize
    );
};

struct kaphein_mem_Allocator
{
    void * thisObj;

    const struct kaphein_mem_Allocator_VTable * vTable;
};

#endif
