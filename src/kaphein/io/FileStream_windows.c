#include <Windows.h>
#include "kaphein/mem/utils.h"
#include "kaphein/text/encoding.h"
#include "kaphein/io/FileStream.h"

struct Impl
{
    void * allocator_;
    
    HANDLE natvieHandle_;

    OVERLAPPED overlapped_;
    
    enum kaphein_io_FileAccess fileAccess_;
};

//TODO : Fill the contents of this virtual table.
static const struct kaphein_io_Stream_VTable parentVTable = {
    kaphein_io_FileStream_close
    , kaphein_io_FileStream_getSize
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , kaphein_io_FileStream_canRead
    , kaphein_io_FileStream_canWrite
    , KAPHEIN_NULL
    , kaphein_io_FileStream_read
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
    , KAPHEIN_NULL
};

static
int
kaphein_io_FileStream_toWinApiFileAccess(
    enum kaphein_io_FileAccess fileAccess
)
{
    int result = 0;
    
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
kaphein_io_FileStream_toWinApiFileMode(
    enum kaphein_io_FileMode fileMode
)
{
    int result = 0;
    
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
    , void * allocator
)
{
    enum kaphien_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    
    if(KAPHEIN_NULL == thisObj) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Impl *const implPtr = (struct Impl *)kaphein_mem_allocate(
            allocator
            , KAPHEIN_ssizeof(*implPtr)
            , KAPHEIN_NULL
            , &resultErrorCode
        );

        if(kapheinErrorCodeNoError == resultErrorCode) {
            thisObj->parent.vTable = &parentVTable;
            thisObj->impl_ = implPtr;
            
            implPtr->allocator_ = allocator;
            implPtr->natvieHandle_ = INVALID_HANDLE_VALUE;
            implPtr->overlapped_.hEvent = NULL;
            implPtr->fileAccess_ = kaphein_io_FileAccess_none;
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_destruct(
    struct kaphein_io_FileStream * thisObj
)
{
    enum kaphien_ErrorCode resultErrorCode = kaphein_io_FileStream_close(thisObj);
    
    if(kapheinErrorCodeNoError == resultErrorCode) {
        struct Impl *const implPtr = (struct Impl *)thisObj->impl_;

        resultErrorCode = kaphein_mem_deallocate(
            implPtr->allocator_
            , implPtr
            , KAPHEIN_ssizeof(*implPtr)
        );
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
        struct Impl *const implPtr = (struct Impl *)thisObj->impl_;
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
        
        utf16FilePath = kaphein_mem_allocate(
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

        implPtr->natvieHandle_ = CreateFileW(
            KAPHEIN_x_const_horrible_cast(LPCWSTR, utf16FilePath)
            , kaphein_io_FileStream_toWinApiFileAccess(fileAccess)
            , 0
            , NULL
            , kaphein_io_FileStream_toWinApiFileMode(fileMode)
            , FILE_FLAG_OVERLAPPED
            , NULL
        );
        if(INVALID_HANDLE_VALUE == implPtr->natvieHandle_) {
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
        
        kaphein_mem_fillZero(&implPtr->overlapped_, KAPHEIN_ssizeof(implPtr->overlapped_), KAPHEIN_ssizeof(implPtr->overlapped_));

        implPtr->overlapped_.hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
        if(NULL == implPtr->overlapped_.hEvent) {
            errorCode = kapheinErrorCodePlatformResourceAllocationFailed;

            goto endOfOpen;
        }
        implPtr->fileAccess_ = fileAccess;

        if(kaphein_io_FileMode_append == fileMode) {
            //TODO : Seek to the end.
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
        struct Impl *const implPtr = (struct Impl *)thisPtr->impl_;

        if(INVALID_HANDLE_VALUE != implPtr->natvieHandle_ ) {
            CloseHandle(implPtr->natvieHandle_);
        }
        implPtr->natvieHandle_ = INVALID_HANDLE_VALUE;

        if(NULL != implPtr->overlapped_.hEvent) {
            CloseHandle(implPtr->overlapped_.hEvent);
        }
        implPtr->overlapped_.hEvent = NULL;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_isOpened(
    const struct kaphein_io_FileStream * thisObj
    , bool * truthOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || truthOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        struct Impl *const implPtr = (struct Impl *)thisObj->impl_;

        *truthOut = implPtr->natvieHandle_ != INVALID_HANDLE_VALUE;
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
        struct Impl *const implPtr = (struct Impl *)thisObj->impl_;

        *accessOut = implPtr->fileAccess_;
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
    enum kaphein_ErrorCode errorCode;
    bool isOpened;

    errorCode = kaphein_io_FileStream_isOpened(thisObj, &isOpened);
    if(errorCode == kapheinErrorCodeNoError && isOpened) {
        struct Impl *const implPtr = (struct Impl *)thisObj->impl_;

        FILE_NAME_INFO fni;
        BOOL result;

        result = GetFileInformationByHandleEx(implPtr->natvieHandle_, FileNameInfo, &fni, (DWORD)sizeof(fni));
        if(FALSE == result) {
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
    , kaphein_SSize * sizeOut
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    errorCode = kaphein_io_FileStream_isOpened(thisPtr, &isOpened);
    if(errorCode == kapheinErrorCodeNoError) {
        if(!isOpened) {
            errorCode = kapheinErrorCodeOperationInvalid;
        }
        else {
            struct Impl *const implPtr = (struct Impl *)thisPtr->impl_;
            LARGE_INTEGER fileSize;

            GetFileSizeEx(implPtr->natvieHandle_, &fileSize);

            *sizeOut = (kaphein_SSize)fileSize.QuadPart;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_canRead(
    const void * thisObj
    , bool * truthOut
)
{
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    if(KAPHEIN_NULL == truthOut) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        errorCode = kaphein_io_FileStream_isOpened(thisObj, &isOpened);
        if(kapheinErrorCodeNoError == errorCode) {
            struct Impl *const implPtr = (struct Impl *)thisPtr->impl_;

            *truthOut = 
                isOpened
                & ((implPtr->fileAccess_ & kaphein_io_FileAccess_read) != 0)
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
    struct kaphein_io_FileStream *const thisPtr = (struct kaphein_io_FileStream *)thisObj;
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    bool isOpened;

    if(KAPHEIN_NULL == truthOut) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        errorCode = kaphein_io_FileStream_isOpened(thisObj, &isOpened);
        if(kapheinErrorCodeNoError == errorCode) {
            struct Impl *const implPtr = (struct Impl *)thisPtr->impl_;

            *truthOut = 
                isOpened
                & ((implPtr->fileAccess_ & kaphein_io_FileAccess_write) != 0)
            ;
        }
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
    LARGE_INTEGER largeInteger;
    enum kaphein_ErrorCode errorCode;
    bool isOpened;

    errorCode = kaphein_io_FileStream_isOpened(thisObj, &isOpened);
    if(errorCode == kapheinErrorCodeNoError && isOpened) {
        struct Impl *const implPtr = (struct Impl *)thisPtr->impl_;
        DWORD readByteCount = 0;
        BOOL result;
        
        result = ReadFile(
            implPtr->natvieHandle_
            , dest
            , (DWORD)destSize
            , &readByteCount
            , &implPtr->overlapped_
        );

        while(FALSE == result) {
            switch(GetLastError()) {
            case ERROR_HANDLE_EOF:
                errorCode = kapheinErrorCodeIoEndOfStreamReached;
                result = TRUE;
            break;
            case ERROR_IO_PENDING:
                result = GetOverlappedResultEx(
                    implPtr->natvieHandle_
                    , &implPtr->overlapped_
                    , &readByteCount
                    , INFINITE
                    , TRUE
                );

                if(TRUE == result) {
                    largeInteger.LowPart = implPtr->overlapped_.Offset;
                    largeInteger.HighPart = implPtr->overlapped_.OffsetHigh;
                    largeInteger.QuadPart += readByteCount;
                    implPtr->overlapped_.Offset = largeInteger.LowPart;
                    implPtr->overlapped_.OffsetHigh = largeInteger.HighPart;
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
    void* thisObj
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
kaphein_io_FileStream_toConstStream(
    const struct kaphein_io_FileStream * thisObj
    , const struct kaphein_io_Stream ** streamOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || streamOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *streamOut = &thisObj->parent;
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_io_FileStream_toStream(
    struct kaphein_io_FileStream * thisObj
    , struct kaphein_io_Stream ** streamOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || streamOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *streamOut = &thisObj->parent;
    }

    return errorCode;
}
