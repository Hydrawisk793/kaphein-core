#include <Windows.h>
#include "kaphein/mem/utils.h"
#include "kaphein/text/encoding.h"
#include "kaphein/io/FileStream.h"

struct FileStream_Impl
{
    struct kaphein_mem_Allocator * allocator_;
    
    HANDLE natvieHandle_;

    OVERLAPPED overlapped_;
    
    enum kaphein_io_FileAccess fileAccess_;
};

//TODO : Fill the contents of this virtual table.
static const struct kaphein_io_Stream_VTable parentVTable = {
    kaphein_io_FileStream_destruct
    , kaphein_io_FileStream_isOpened
    , kaphein_io_FileStream_close
    , kaphein_io_FileStream_getSize
    , kaphein_io_FileStream_getPosition
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , kaphein_io_FileStream_canRead
    , kaphein_io_FileStream_canWrite
    , kaphein_io_FileStream_canSeek
    , kaphein_io_FileStream_read
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , kaphein_io_FileStream_seek
};

static
int
toWinApiFileSeekOrigin(
    enum kaphein_io_SeekOrigin seekOrigin
)
{
    int winApiFileSeekOrigin = FILE_BEGIN;
    
    switch(seekOrigin) {
    case kaphein_io_SeekOrigin_begin:
        winApiFileSeekOrigin = FILE_BEGIN;
    break;
    case kaphein_io_SeekOrigin_current:
        winApiFileSeekOrigin = FILE_CURRENT;
    break;
    case kaphein_io_SeekOrigin_end:
        winApiFileSeekOrigin = FILE_END;
    break;
    }

    return winApiFileSeekOrigin;
}

static
int
toWinApiFileAccess(
    enum kaphein_io_FileAccess fileAccess
)
{
    int result = GENERIC_READ;
    
    switch(fileAccess) {
    case kaphein_io_FileAccess_none:
    break;
    case kaphein_io_FileAccess_read:
        result = GENERIC_READ;
    break;
    case kaphein_io_FileAccess_write:
        result = GENERIC_WRITE;
    break;
    case kaphein_io_FileAccess_readAndWrite:
        result = GENERIC_READ | GENERIC_WRITE;
    break;
    }

    return result;
}

static
int
toWinApiFileMode(
    enum kaphein_io_FileMode fileMode
)
{
    int result = OPEN_EXISTING;
    
    switch(fileMode) {
    case kaphein_io_FileMode_open:
        result = OPEN_EXISTING;
    break;
    case kaphein_io_FileMode_openOrCreate:
        result = OPEN_ALWAYS;
    break;
    case kaphein_io_FileMode_createNew:
        result = CREATE_NEW;
    break;
    case kaphein_io_FileMode_create:
        result = CREATE_ALWAYS;
    break;
    case kaphein_io_FileMode_truncate:
        result = TRUNCATE_EXISTING;
    break;
    case kaphein_io_FileMode_append:
        result = OPEN_ALWAYS;
    break;
    }

    return result;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_construct(
    struct kaphein_io_FileStream * thisObj
    , struct kaphein_mem_Allocator * allocator
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)kaphein_mem_allocate(
            allocator
            , KAPHEIN_ssizeof(*impl)
            , KAPHEIN_NULL
            , &resultErrorCode
        );

        if(kapheinErrorCodeNoError == resultErrorCode) {
            thisObj->parent.thisObj = thisObj;
            thisObj->parent.vTable = &parentVTable;
            thisObj->impl_ = impl;
            
            impl->allocator_ = allocator;
            impl->natvieHandle_ = INVALID_HANDLE_VALUE;
            impl->overlapped_.hEvent = NULL;
            impl->fileAccess_ = kaphein_io_FileAccess_none;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_destruct(
    void * thisObj
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode resultErrorCode = kaphein_io_FileStream_close(thisPtr);
    
    if(kapheinErrorCodeNoError == resultErrorCode) {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)thisPtr->impl_;

        resultErrorCode = kaphein_mem_deallocate(
            impl->allocator_
            , impl
            , KAPHEIN_ssizeof(*impl)
        );

        if(kapheinErrorCodeNoError == resultErrorCode) {
            thisPtr->parent.thisObj = KAPHEIN_NULL;
            thisPtr->parent.vTable = KAPHEIN_NULL;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_openFromFilePath(
    struct kaphein_io_FileStream * thisObj
    , enum kaphein_io_FileAccess fileAccess
    , enum kaphein_io_FileMode fileMode
    , const char * filePath
    , kaphein_SSize filePathSize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool truth;

    KAPHEIN_x_UNUSED_PARAMETER(fileMode)

    if(thisObj == KAPHEIN_NULL || filePath == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(filePathSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(kaphein_io_FileStream_isOpened(thisObj, &truth), truth) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)thisObj->impl_;
        kaphein_UIntLeast16 * utf16FilePath = KAPHEIN_NULL;
        kaphein_SSize utf16FilePathSize;

        errorCode = kaphein_text_convertUtf8ToUtf16(
            filePath
            , filePathSize
            , KAPHEIN_NULL
            , &utf16FilePathSize
        );
        if(errorCode != kapheinErrorCodeNoError) {
            goto endOfOpen;
        }
        
        utf16FilePath = (kaphein_UIntLeast16 *)kaphein_mem_allocate(
            KAPHEIN_NULL
            , (utf16FilePathSize + 1) * sizeof(*utf16FilePath)
            , KAPHEIN_NULL
            , &errorCode
        );
        if(utf16FilePath == KAPHEIN_NULL) {
            goto endOfOpen;
        }
        utf16FilePath[utf16FilePathSize] = 0;

        kaphein_text_convertUtf8ToUtf16(
            filePath
            , filePathSize
            , utf16FilePath
            , &utf16FilePathSize
        );

        impl->natvieHandle_ = CreateFileW(
            KAPHEIN_x_const_horrible_cast(LPCWSTR, utf16FilePath)
            , toWinApiFileAccess(fileAccess)
            , 0
            , NULL
            , toWinApiFileMode(fileMode)
            , FILE_FLAG_OVERLAPPED
            , NULL
        );
        if(INVALID_HANDLE_VALUE == impl->natvieHandle_) {
            switch(GetLastError()) {
            case ERROR_FILE_NOT_FOUND:
                errorCode = kapheinErrorCodeIoDeviceNotFound;
            break;
            case ERROR_ALREADY_EXISTS:
            case ERROR_FILE_EXISTS:
                errorCode = kapheinErrorCodeIoError;
            break;
            case ERROR_ACCESS_DENIED:
                errorCode = kapheinErrorCodeIoAccessDenied;
            break;
            default:
                errorCode = kapheinErrorCodeIoError;
            break;
            }
            
            goto endOfOpen;
        }
        
        kaphein_mem_fillZero(&impl->overlapped_, KAPHEIN_ssizeof(impl->overlapped_), KAPHEIN_ssizeof(impl->overlapped_));

        impl->overlapped_.hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
        if(NULL == impl->overlapped_.hEvent) {
            errorCode = kapheinErrorCodePlatformResourceAllocationFailed;

            goto endOfOpen;
        }
        impl->fileAccess_ = fileAccess;

        if(kaphein_io_FileMode_append == fileMode) {
            errorCode = kaphein_io_FileStream_seek(thisObj, 0, kaphein_io_SeekOrigin_end, KAPHEIN_NULL);
        }

    endOfOpen:
        if(KAPHEIN_NULL != utf16FilePath) {
            kaphein_mem_deallocate(
                KAPHEIN_NULL
                , utf16FilePath
                , (utf16FilePathSize + 1) * sizeof(*utf16FilePath)
            );
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_isOpened(
    const void * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(
        KAPHEIN_NULL == thisObj
        || KAPHEIN_NULL == truthOut
    ) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct kaphein_io_FileStream *const thisPtr = (const struct kaphein_io_FileStream *)thisObj;
        const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisPtr->impl_;

        *truthOut = impl->natvieHandle_ != INVALID_HANDLE_VALUE;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_close(
    void * thisObj
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == thisPtr) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)thisPtr->impl_;

        if(INVALID_HANDLE_VALUE != impl->natvieHandle_ ) {
            CloseHandle(impl->natvieHandle_);
        }
        impl->natvieHandle_ = INVALID_HANDLE_VALUE;

        if(NULL != impl->overlapped_.hEvent) {
            CloseHandle(impl->overlapped_.hEvent);
        }
        impl->overlapped_.hEvent = NULL;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_getFileAccess(
    const struct kaphein_io_FileStream * thisObj
    , enum kaphein_io_FileAccess * accessOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || accessOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisObj->impl_;

        *accessOut = impl->fileAccess_;
    }
    
    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_getFilePath(
    const struct kaphein_io_FileStream * thisObj
    , char * pathOut
    , kaphein_SSize * pathSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    if(kaphein_io_FileStream_isOpened(thisObj, &isOpened), isOpened) {
        const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisObj->impl_;
        FILE_NAME_INFO fni;

        if(FALSE == GetFileInformationByHandleEx(impl->natvieHandle_, FileNameInfo, &fni, (DWORD)sizeof(fni))) {
            errorCode = kapheinErrorCodeUnknownError;
        }
        else {
            errorCode = kaphein_text_convertUtf16ToUtf8(
                KAPHEIN_x_const_horrible_cast(const kaphein_UIntLeast16 *, fni.FileName)
                , (kaphein_SSize)fni.FileNameLength
                , pathOut
                , pathSizeInOut
            );
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_getSize(
    const void * thisObj
    , kaphein_Int64 * sizeOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    if(kaphein_io_FileStream_isOpened(thisObj, &isOpened), !isOpened) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        const struct kaphein_io_FileStream *const thisPtr = (const struct kaphein_io_FileStream *)thisObj;
        const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisPtr->impl_;
        DWORD fileSizeLow, fileSizeHigh;

        fileSizeLow = GetFileSize(impl->natvieHandle_, &fileSizeHigh);
        if((fileSizeHigh & (1 << ((sizeof(DWORD) << 3) - 1))) != 0) {
            errorCode = kapheinErrorCodeNotSupported;
        }
        else {
            *sizeOut = (kaphein_Int64)(((kaphein_Int64)fileSizeHigh << (sizeof(DWORD) << 3)) | fileSizeLow);
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_getPosition(
    const void * thisObj
    , kaphein_Int64 * positionOut
)
{
    //It's safe to do this because this operation does not change the internal state of the object.
    
    return kaphein_io_FileStream_seek(
        (void *)thisObj
        , 0
        , kaphein_io_SeekOrigin_current
        , positionOut
    );
}

enum kaphein_ErrorCode
kaphein_io_FileStream_canRead(
    const void * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == truthOut) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        bool isOpened;
        
        if(kaphein_io_FileStream_isOpened(thisObj, &isOpened), isOpened) {    
            const struct kaphein_io_FileStream *const thisPtr = (const struct kaphein_io_FileStream *)thisObj;
            const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisPtr->impl_;

            *truthOut = 
                isOpened
                & ((impl->fileAccess_ & kaphein_io_FileAccess_read) != 0)
            ;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_canWrite(
    const void * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == truthOut) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        bool isOpened;
        
        if(kaphein_io_FileStream_isOpened(thisObj, &isOpened), isOpened) {    
            const struct kaphein_io_FileStream *const thisPtr = (const struct kaphein_io_FileStream *)thisObj;
            const struct FileStream_Impl *const impl = (const struct FileStream_Impl *)thisPtr->impl_;

            *truthOut = 
                isOpened
                & ((impl->fileAccess_ & kaphein_io_FileAccess_write) != 0)
            ;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_canSeek(
    const void * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == truthOut) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        kaphein_Int64 position;
        bool isOpened;

        kaphein_io_FileStream_isOpened(thisObj, &isOpened);

        *truthOut = isOpened
            && kapheinErrorCodeNoError == kaphein_io_FileStream_getPosition(thisObj, &position)
        ;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_read(
    void * thisObj
    , void * dest
    , kaphein_SSize destSize
    , kaphein_SSize * readByteCountOut
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    if(kaphein_io_FileStream_isOpened(thisObj, &isOpened), isOpened) {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)thisPtr->impl_;
        DWORD readByteCount = 0;
        BOOL result;
        
        result = ReadFile(
            impl->natvieHandle_
            , dest
            , (DWORD)destSize
            , &readByteCount
            , &impl->overlapped_
        );

        while(FALSE == result) {
            switch(GetLastError()) {
            case ERROR_HANDLE_EOF:
                errorCode = kapheinErrorCodeIoEndOfStreamReached;
                result = TRUE;
            break;
            case ERROR_IO_PENDING:
                result = GetOverlappedResultEx(
                    impl->natvieHandle_
                    , &impl->overlapped_
                    , &readByteCount
                    , INFINITE
                    , TRUE
                );

                if(TRUE == result) {
                    LARGE_INTEGER largeInteger;

                    largeInteger.LowPart = impl->overlapped_.Offset;
                    largeInteger.HighPart = impl->overlapped_.OffsetHigh;
                    largeInteger.QuadPart += readByteCount;
                    impl->overlapped_.Offset = largeInteger.LowPart;
                    impl->overlapped_.OffsetHigh = largeInteger.HighPart;
                }
            break;
            default:
                errorCode = kapheinErrorCodeIoReadFailed;
            //break;
            }
        }

        if(KAPHEIN_NULL != readByteCountOut) {
            *readByteCountOut = (kaphein_SSize)readByteCount;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_write(
    void * thisObj
    , const void * src
    , kaphein_SSize srcSize
    , kaphein_SSize * writtenByteCountOut
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;

    thisPtr;
    KAPHEIN_x_UNUSED_PARAMETER(src)
    KAPHEIN_x_UNUSED_PARAMETER(srcSize)
    KAPHEIN_x_UNUSED_PARAMETER(writtenByteCountOut)
    
    return kapheinErrorCodeNotImplemented;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_seek(
    void * thisObj
    , kaphein_Int64 offset
    , enum kaphein_io_SeekOrigin origin
    , kaphein_Int64 * newPositionOut
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool truth;

    if(offset >= MAXLONGLONG) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else if(kaphein_io_FileStream_isOpened(thisObj, &truth), !truth) {
        errorCode = kapheinErrorCodeOperationInvalid;
    }
    else {
        struct FileStream_Impl *const impl = (struct FileStream_Impl *)thisPtr->impl_;
        LARGE_INTEGER distanceToMove, newPosition;
        distanceToMove.QuadPart = (LONGLONG)offset;
        
        if(FALSE == SetFilePointerEx(impl->natvieHandle_, distanceToMove, &newPosition, toWinApiFileSeekOrigin(origin))) {
            errorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            if(KAPHEIN_NULL != newPositionOut) {
                *newPositionOut = (kaphein_Int64)newPosition.QuadPart;
            }
        }
    }

    return errorCode;
}
