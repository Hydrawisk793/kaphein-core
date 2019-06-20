#include "kaphein/mem/utils.h"
#include "kaphein/text/base64.h"

enum kaphein_ErrorCode
kaphein_text_convertBytesToBase64(
    const char * input
    , kaphein_SSize inputSize
    , char * output
    , kaphein_SSize * outputSizeInOut
)
{
    static const char * base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/="
    ;
    enum kaphein_ErrorCode result = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == input || KAPHEIN_NULL == outputSizeInOut) {
        result = kapheinErrorCodeArgumentNull;
    }
    else if(0 > inputSize || (KAPHEIN_NULL != output && 0 > *outputSizeInOut)) {
        result = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        char fourBase64Chars[4];
        char inputChar;
        int fourBase64CharIndices[4];
        int i;
        kaphein_SSize remainingByteCount = inputSize;
        kaphein_SSize byteCountToCopy;
        kaphein_SSize outputSize = *outputSizeInOut;
        kaphein_SSize base64StrLen = 0;
        kaphein_SSize copiedByteCount = 0;

        while(remainingByteCount > 0) {
            if(remainingByteCount > 0) {
                inputChar = *input++;
                
                fourBase64CharIndices[0] = (inputChar & 0xFC) >> 2;
                fourBase64CharIndices[1] = ((inputChar & 0x03) << 4);

                --remainingByteCount;
                base64StrLen += 2;
            }

            if(remainingByteCount > 0) {
                inputChar = *input++;

                fourBase64CharIndices[1] |= ((inputChar & 0xF0) >> 4);
                fourBase64CharIndices[2] = ((inputChar & 0x0F) << 2);
            
                --remainingByteCount;
                ++base64StrLen;
            }
            else {
                fourBase64CharIndices[2] = 64;
                ++base64StrLen;
            }

            if(remainingByteCount > 0) {
                inputChar = *input++;

                fourBase64CharIndices[2] |= ((inputChar & 0xC0) >> 6);
                fourBase64CharIndices[3] = inputChar & 0x3F;
            
                --remainingByteCount;
                ++base64StrLen;
            }
            else {
                fourBase64CharIndices[3] = 64;
                ++base64StrLen;
            }

            for(i = 4; i > 0; ) {
                --i;
                fourBase64Chars[i] = base64Chars[fourBase64CharIndices[i]];
            }

            if(KAPHEIN_NULL != output) {
                byteCountToCopy = outputSize - copiedByteCount;
                if(byteCountToCopy > 4) {
                    byteCountToCopy = 4;
                }
                else if(byteCountToCopy < 0) {
                    byteCountToCopy = 0;

                    result = kapheinErrorCodeNotEnoughBufferSpace;
                }

                if(byteCountToCopy > 0) {
                    kaphein_mem_copy(output, byteCountToCopy, fourBase64Chars, byteCountToCopy);
                    output += byteCountToCopy;
                    copiedByteCount += byteCountToCopy;
                }
            }
        }

        *outputSizeInOut = (KAPHEIN_NULL == output ? base64StrLen : copiedByteCount);
    }

    return result;
}

enum kaphein_ErrorCode
kaphein_text_convertBase64ToBytes(
    const char * input
    , kaphein_SSize inputSize
    , char * output
    , kaphein_SSize * outputSizeInOut
)
{
    enum kaphein_ErrorCode result = kapheinErrorCodeNoError;

    if(KAPHEIN_NULL == input || KAPHEIN_NULL == outputSizeInOut) {
        result = kapheinErrorCodeArgumentNull;
    }
    else if(0 > inputSize || (KAPHEIN_NULL != output && 0 > *outputSizeInOut)) {
        result = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        char threeBytes[3];
        char base64Char;
        int base64CharIndex;
        int state = 0;
        kaphein_SSize byteCountToCopy;
        kaphein_SSize decodedByteCount = 0;
        kaphein_SSize byteCount = 0;
        kaphein_SSize outputSize = *outputSizeInOut;
        kaphein_SSize outputLen = 0;
        bool shouldCopyBytes = false;

        do {
            base64CharIndex = 64;
            if(inputSize > 0) {
                --inputSize;
                base64Char = *input++;

                if(base64Char >= 'A' && base64Char <= 'Z') {
                    base64CharIndex = base64Char - 'A';
                }
                else if(base64Char >= 'a' && base64Char <= 'z') {
                    base64CharIndex = base64Char - 'a' + ('Z' - 'A' + 1);
                }
                else if(base64Char >= '0' && base64Char <= '9') {
                    base64CharIndex = base64Char - '0' + ('Z' - 'A' + 1) + ('z' - 'a' + 1);
                }
                else if(base64Char == '+') {
                    base64CharIndex = 62;
                }
                else if(base64Char == '/') {
                    base64CharIndex = 63;
                }
                else {
                    if(base64Char != '=') {
                        result = kapheinErrorCodeArgumentFormatInvalid;
                    }
                    
                    shouldCopyBytes = true;
                }
            }
            else {
                shouldCopyBytes = true;
            }
            
            if(base64CharIndex < 64) {
                switch(state) {
                case 0:
                    kaphein_mem_fillZero(threeBytes, KAPHEIN_ssizeof(threeBytes), KAPHEIN_ssizeof(threeBytes));

                    threeBytes[0] = (char)((base64CharIndex << 2) & 0xFF);

                    ++state;
                break;
                case 1:
                    threeBytes[0] |= (char)((base64CharIndex >> 4) & 0xFF);
                    threeBytes[1] = (char)((base64CharIndex << 4) & 0xFF);

                    ++decodedByteCount;
                    ++outputLen;

                    ++state;
                break;
                case 2:
                    threeBytes[1] |= (char)((base64CharIndex >> 2) & 0xFF);
                    threeBytes[2] = (char)((base64CharIndex << 6) & 0xFF);

                    ++decodedByteCount;
                    ++outputLen;

                    ++state;
                break;
                case 3:
                    threeBytes[2] |= base64CharIndex;

                    ++decodedByteCount;
                    ++outputLen;

                    shouldCopyBytes = true;

                    ++state;
                break;
                }
            }

            if(shouldCopyBytes) {
                if(KAPHEIN_NULL != output) {
                    byteCountToCopy = outputSize - byteCount;
                    if(byteCountToCopy >= decodedByteCount) {
                        byteCountToCopy = decodedByteCount;
                    }

                    kaphein_mem_copy(output, byteCountToCopy, threeBytes, byteCountToCopy);
                    byteCount += byteCountToCopy;

                    output += byteCountToCopy;
                }
                
                shouldCopyBytes = false;
            }

            if(state >= 4) {
                state = 0;
                decodedByteCount = 0;
            }
        }
        while(base64CharIndex < 64);
        
        *outputSizeInOut = (KAPHEIN_NULL == output ? outputLen : byteCount);
    }

    return result;
}
