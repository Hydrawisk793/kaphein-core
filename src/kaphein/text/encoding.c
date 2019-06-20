#include "kaphein/ErrorCode.h"
#include "kaphein/mem/utils.h"
#include "kaphein/text/encoding.h"

/* ******************************** */
/* Internal function declarations */

static
enum kaphein_ErrorCode
kaphein_text_convertUcs4CharToUtf16Chars(
    kaphein_IntLeast32 ucs4Char
    , kaphein_UIntLeast16 * utf16CharsOut
    , kaphein_SSize * utf16CharCountInOut
);

static
enum kaphein_ErrorCode
kaphein_text_convertUtf16CharsToUcs4Char(
    const kaphein_UIntLeast16 * utf16Chars
    , kaphein_SSize utf16CharCount
    , kaphein_IntLeast32 * ucs4CharOut
    , kaphein_SSize * consumedUtf16CharCountOut
);

static
enum kaphein_ErrorCode
kaphein_text_convertUcs4CharToUtf8Chars(
    kaphein_IntLeast32 ucs4Char
    , char * utf8CharsOut
    , kaphein_SSize * utf8CharCountInOut
);

static
enum kaphein_ErrorCode
kaphein_text_convertUtf8CharsToUcs4Char(
    const char * utf8Chars
    , kaphein_SSize utf8CharCount
    , kaphein_IntLeast32 * ucs4CharOut
    , kaphein_SSize * consumedUtf8CharCountOut
);

/* ******************************** */

/* ******************************** */
/* Function definitions */

enum kaphein_ErrorCode
kaphein_text_convertUtf8ToUtf16(
    const char * utf8Text
    , kaphein_SSize utf8TextSize
    , kaphein_UIntLeast16 * utf16TextOut
    , kaphein_SSize * utf16TextSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    kaphein_IntLeast32 ucs4Char;
    kaphein_SSize consumedUtf8CharCount;
    kaphein_SSize utf16TextActualSize;
    kaphein_SSize utf16TextSize;
    kaphein_SSize utf16TextRestSize;

    utf16TextRestSize = *utf16TextSizeInOut;
    utf16TextActualSize = 0;
    do {
        errorCode = kaphein_text_convertUtf8CharsToUcs4Char(
            utf8Text
            , utf8TextSize
            , &ucs4Char
            , &consumedUtf8CharCount
        );
        if(errorCode == kapheinErrorCodeNoError) {
            utf8Text += consumedUtf8CharCount;
            utf8TextSize -= consumedUtf8CharCount;

            utf16TextSize = utf16TextRestSize;
            errorCode = kaphein_text_convertUcs4CharToUtf16Chars(
                ucs4Char
                , utf16TextOut
                , &utf16TextSize
            );
            if(errorCode == kapheinErrorCodeNoError) {
                if(utf16TextOut != KAPHEIN_NULL) {
                    utf16TextOut += utf16TextSize;
                }
                utf16TextRestSize -= utf16TextSize;
                utf16TextActualSize += utf16TextSize;
            }
        }
    }
    while(errorCode == kapheinErrorCodeNoError && utf8TextSize > 0);

    *utf16TextSizeInOut = utf16TextActualSize;

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_text_convertUtf16ToUtf8(
    const kaphein_UIntLeast16 * utf16Text
    , kaphein_SSize utf16TextSize
    , char * utf8TextOut
    , kaphein_SSize * utf8TextSizeInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    kaphein_IntLeast32 ucs4Char;
    kaphein_SSize consumedUtf16CharCount;
    kaphein_SSize utf8TextActualSize;
    kaphein_SSize utf8TextSize;
    kaphein_SSize utf8TextRestSize;

    utf8TextRestSize = *utf8TextSizeInOut;
    utf8TextActualSize = 0;
    do {
        errorCode = kaphein_text_convertUtf16CharsToUcs4Char(
            utf16Text
            , utf16TextSize
            , &ucs4Char
            , &consumedUtf16CharCount
        );
        if(errorCode == kapheinErrorCodeNoError) {
            utf16Text += consumedUtf16CharCount;
            utf16TextSize -= consumedUtf16CharCount;

            utf8TextSize = utf8TextRestSize;
            errorCode = kaphein_text_convertUcs4CharToUtf8Chars(
                ucs4Char
                , utf8TextOut
                , &utf8TextSize
            );
            if(errorCode == kapheinErrorCodeNoError) {
                if(utf8TextOut != KAPHEIN_NULL) {
                    utf8TextOut += utf8TextSize;
                }
                utf8TextRestSize -= utf8TextSize;
                utf8TextActualSize += utf8TextSize;
            }
        }
    }
    while(errorCode == kapheinErrorCodeNoError && utf16TextSize > 0);

    *utf8TextSizeInOut = utf8TextActualSize;

    return errorCode;
}

/* ******************************** */

/* ******************************** */
/* Internal function definitions */

static
enum kaphein_ErrorCode
kaphein_text_convertUcs4CharToUtf16Chars(
    kaphein_IntLeast32 ucs4Char
    , kaphein_UIntLeast16 * utf16CharsOut
    , kaphein_SSize * utf16CharCountInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(utf16CharCountInOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(utf16CharsOut != KAPHEIN_NULL && *utf16CharCountInOut < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        kaphein_SSize utf16CharCount = 0;

        if((ucs4Char & 0x80000000) != 0 || 0x10FFFF < ucs4Char) {
            errorCode = kapheinErrorCodeArgumentInvalid;
        }
        else {
            utf16CharCount = *utf16CharCountInOut;
            
            if(0xFFFF < ucs4Char) {
                if(utf16CharsOut != KAPHEIN_NULL) {
                    if(utf16CharCount < 2) {
                        errorCode = kapheinErrorCodeArgumentOutOfRange;
                    }
                    else {
                        const kaphein_IntLeast32 ucs4Char10Bits = ucs4Char - 0x10000;
                        
                        *utf16CharsOut++ = (kaphein_UIntLeast16)(0xD800 | ((ucs4Char10Bits & ((0x03FF) << 10)) >> 10));
                        *utf16CharsOut++ = (kaphein_UIntLeast16)(0xDC00 | (ucs4Char10Bits & 0x03FF));
                    }
                }
                
                utf16CharCount = 2;
            }
            else {
                if(utf16CharsOut != KAPHEIN_NULL) {
                    if(utf16CharCount < 1) {
                        errorCode = kapheinErrorCodeArgumentOutOfRange;
                    }
                    else {
                        *utf16CharsOut = (kaphein_UIntLeast16)ucs4Char;
                    }
                }

                utf16CharCount = 1;
            }
        }
        
        *utf16CharCountInOut = utf16CharCount;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_text_convertUtf16CharsToUcs4Char(
    const kaphein_UIntLeast16 * utf16Chars
    , kaphein_SSize utf16CharCount
    , kaphein_IntLeast32 * ucs4CharOut
    , kaphein_SSize * consumedUtf16CharCountOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(utf16Chars == KAPHEIN_NULL || consumedUtf16CharCountOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(utf16CharCount < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        kaphein_IntLeast32 ucs4Char = 0;
        kaphein_SSize consumedUtf16CharCount = 0;

        if(utf16CharCount > 0) {
            kaphein_UIntLeast16 utf16Char;
            int surrogateFlags = 0;

            do {
                --utf16CharCount;
                utf16Char = *utf16Chars++;
                ++consumedUtf16CharCount;
                
                switch(((utf16Char & 0xFF00) >> 8)) {
                case 0xD8:
                case 0xD9:
                case 0xDA:
                case 0xDB:
                    ucs4Char |= ((utf16Char & 0x03FF) << 10);
                    surrogateFlags |= 0x02;
                break;
                case 0xDC:
                case 0xDD:
                case 0xDE:
                case 0xDF:
                    ucs4Char |= (utf16Char & 0x03FF);
                    surrogateFlags |= 0x01;
                break;
                }
            }
            while((surrogateFlags != 0x00 && surrogateFlags != 0x03) && utf16CharCount > 0);

            switch(surrogateFlags) {
            case 0x00:
                ucs4Char = (utf16Char & 0xFFFF);
            break;
            case 0x01:
            case 0x02:
                errorCode = kapheinErrorCodeArgumentInvalid;
            break;
            case 0x03:
                ucs4Char += 0x00010000;
            break;
            }
        }
        
        *ucs4CharOut = ucs4Char;
        *consumedUtf16CharCountOut = consumedUtf16CharCount;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_text_convertUcs4CharToUtf8Chars(
    kaphein_IntLeast32 ucs4Char
    , char * utf8CharsOut
    , kaphein_SSize * utf8CharCountInOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(utf8CharCountInOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(utf8CharsOut != KAPHEIN_NULL && *utf8CharCountInOut < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        kaphein_SSize utf8CharCount = 0;

        if((ucs4Char & 0x80000000) != 0) {
            errorCode = kapheinErrorCodeArgumentInvalid;
        }
        else {
            static const kaphein_IntLeast32 sizeMasks[] = {
                0x7C000000
                , 0x03E00000
                , 0x001F0000
                , 0x0000F800
                , 0x00000780
                , 0x0000007F
            };
            const kaphein_IntLeast32 * pSizeMask = sizeMasks;
            kaphein_SSize currentUtf8CharCount;
            kaphein_SSize i;
            
            for(i = 6; i > 0; ) {
                currentUtf8CharCount = i;
                --i;

                if(i == 0 || (ucs4Char & *pSizeMask++) != 0) {
                    if(utf8CharsOut != KAPHEIN_NULL) {
                        if(*utf8CharCountInOut < currentUtf8CharCount) {
                            errorCode = kapheinErrorCodeArgumentOutOfRange;
                        }
                        else {
                            switch(i) {
                            case 0:
                                *utf8CharsOut++ = (char)(ucs4Char & 0x7F);
                            break;
                            case 1:
                                *utf8CharsOut++ = (char)(0xC0 | ((ucs4Char >> 6) & 0x1F));
                                *utf8CharsOut++ = (char)(0x80 | (ucs4Char & 0x3F));
                            break;
                            case 2:
                                *utf8CharsOut++ = (char)(0xE0 | ((ucs4Char >> 12) & 0x0F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 6) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | (ucs4Char & 0x3F));
                            break;
                            case 3:
                                *utf8CharsOut++ = (char)(0xF0 | ((ucs4Char >> 18) & 0x07));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 12) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 6) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | (ucs4Char & 0x3F));
                            break;
                            case 4:
                                *utf8CharsOut++ = (char)(0xF8 | ((ucs4Char >> 24) & 0x03));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 18) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 12) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 6) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | (ucs4Char & 0x3F));
                            break;
                            case 5:
                                *utf8CharsOut++ = (char)(0xFC | ((ucs4Char >> 30) & 0x01));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 24) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 18) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 12) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | ((ucs4Char >> 6) & 0x3F));
                                *utf8CharsOut++ = (char)(0x80 | (ucs4Char & 0x3F));
                            break;
                            }
                        }
                    }

                    utf8CharCount = currentUtf8CharCount;
                    i = 0;
                }
            }
        }

        *utf8CharCountInOut = utf8CharCount;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_text_convertUtf8CharsToUcs4Char(
    const char * utf8Chars
    , kaphein_SSize utf8CharCount
    , kaphein_IntLeast32 * ucs4CharOut
    , kaphein_SSize * consumedUtf8CharCountOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(utf8Chars == KAPHEIN_NULL || consumedUtf8CharCountOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(utf8CharCount < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        kaphein_SSize consumedUtf8CharCount = 0;
        kaphein_IntLeast32 ucs4Char = 0;
        
        if(utf8CharCount > 0) {
            kaphein_SSize actualUtf8CharCount = 0;
            kaphein_SSize i;
            char utf8Char;
            bool isLooping = true;

            utf8Char = *utf8Chars++;
            consumedUtf8CharCount = 1;

            if((utf8Char & 0x80) == 0) {
                ucs4Char = (utf8Char & 0x7F);

                isLooping = false;
            }
            else {
                char utf8CharTemp;
                char utf8CharMask;

                for(
                    utf8CharMask = 0x7F, utf8CharTemp = utf8Char, actualUtf8CharCount = 0;
                    (utf8CharTemp & 0x80) != 0;
                    utf8CharTemp <<= 1, utf8CharMask >>= 1, ++actualUtf8CharCount
                );

                if(6 < actualUtf8CharCount) {
                    errorCode = kapheinErrorCodeArgumentOutOfRange;
                }
                else if(utf8CharCount < actualUtf8CharCount) {
                    errorCode = kapheinErrorCodeArgumentOutOfRange;
                }

                if(errorCode == kapheinErrorCodeNoError) {
                    ucs4Char |= (utf8Char & utf8CharMask);
                }
                else {
                    isLooping = false;
                }
            }

            for(i = actualUtf8CharCount - 1; isLooping && i > 0; ) {
                --i;
                utf8Char = *utf8Chars++;
                ++consumedUtf8CharCount;
                
                if((utf8Char & 0xC0) == 0x80) {
                    ucs4Char <<= 6;
                    ucs4Char |= (utf8Char & 0x3F);
                }
                else {
                    errorCode = kapheinErrorCodeArgumentInvalid;
                    
                    isLooping = false;
                }
            }
        }

        if(ucs4CharOut != KAPHEIN_NULL) {
            *ucs4CharOut = ucs4Char;
        }

        *consumedUtf8CharCountOut = consumedUtf8CharCount;
    }

    return errorCode;
}

/* ******************************** */
