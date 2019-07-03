#ifndef KAPHEIN_HGRD_kaphein_io_Stream_h
#define KAPHEIN_HGRD_kaphein_io_Stream_h

#include "../ErrorCode.h"
#include "SeekOrigin.h"

struct kaphein_io_Stream_VTable
{
    enum kaphein_ErrorCode
    (* destruct) (
        void * thisObj
    );

    enum kaphein_ErrorCode
    (* isOpened) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* close) (
        void * thisObj
    );

    enum kaphein_ErrorCode
    (* getSize) (
        const void * thisObj
        , kaphein_Int64 * sizeOut
    );

    enum kaphein_ErrorCode
    (* getPosition) (
        const void * thisObj
        , kaphein_Int64 * positionOut
    );

    enum kaphein_ErrorCode
    (* hasReachedEnd) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* getReadTimeout) (
        const void * thisObj
        , int * millisecondsOut
    );

    enum kaphein_ErrorCode
    (* setReadTimeout) (
        void * thisObj
        , int milliseconds
    );

    enum kaphein_ErrorCode
    (* getWriteTimeout) (
        const void * thisObj
        , int * millisecondsOut
    );

    enum kaphein_ErrorCode
    (* setWriteTimeout) (
        void * thisObj
        , int milliseconds
    );

    enum kaphein_ErrorCode
    (* canRead) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* canWrite) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* canSeek) (
        const void * thisObj
        , bool * truthOut
    );

    enum kaphein_ErrorCode
    (* read) (
        void * thisObj
        , void * dest
        , kaphein_SSize destSize
        , kaphein_SSize * readByteCountOut
    );

    enum kaphein_ErrorCode
    (* write) (
        void * thisObj
        , const void * src
        , kaphein_SSize srcSize
        , kaphein_SSize * writtenByteCountOut
    );

    enum kaphein_ErrorCode
    (* flush) (
        void * thisObj
    );

    enum kaphein_ErrorCode
    (* seek) (
        void * thisObj
        , kaphein_Int64 offset
        , enum kaphein_io_SeekOrigin origin
        , kaphein_Int64 * newPositionOut
    );
};

struct kaphein_io_Stream
{
    void * thisObj;

    const struct kaphein_io_Stream_VTable * vTable;
};

#endif
