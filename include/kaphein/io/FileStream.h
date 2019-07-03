#ifndef KAPHEIN_HGRD_kaphein_io_FileStream_h
#define KAPHEIN_HGRD_kaphein_io_FileStream_h

#include "../mem/Allocator.h"
#include "Stream.h"
#include "FileMode.h"
#include "FileAccess.h"

struct kaphein_io_FileStream
{
    struct kaphein_io_Stream parent;

    void * impl_;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_construct(
    struct kaphein_io_FileStream * thisObj
    , struct kaphein_mem_Allocator * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_destruct(
    void * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_openFromFilePath(
    struct kaphein_io_FileStream * thisObj
    , enum kaphein_io_FileAccess fileAccess
    , enum kaphein_io_FileMode fileMode
    , const char * filePath
    , kaphein_SSize filePathSize
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_isOpened(
    const void * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_close(
    void * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_getFileAccess(
    const struct kaphein_io_FileStream * thisObj
    , enum kaphein_io_FileAccess * accessOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_getFilePath(
    const struct kaphein_io_FileStream * thisObj
    , char * pathOut
    , kaphein_SSize * pathSizeInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_getSize(
    const void * thisObj
    , kaphein_Int64 * sizeOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_getPosition(
    const void * thisObj
    , kaphein_Int64 * positionOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_canRead(
    const void * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_canWrite(
    const void * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_canSeek(
    const void * thisObj
    , bool * truthOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_read(
    void * thisObj
    , void * dest
    , kaphein_SSize destSize
    , kaphein_SSize * readByteCountOut
);

enum kaphein_ErrorCode
kaphein_io_FileStream_write(
    void * thisObj
    , const void * src
    , kaphein_SSize srcSize
    , kaphein_SSize * writtenByteCountOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_io_FileStream_seek(
    void * thisObj
    , kaphein_Int64 offset
    , enum kaphein_io_SeekOrigin origin
    , kaphein_Int64 * newPositionOut
);

#endif
