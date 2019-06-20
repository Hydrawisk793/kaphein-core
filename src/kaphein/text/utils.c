#include "kaphein/text/utils.h"

enum kaphein_ErrorCode
kaphein_text_parseInt32(
    const char * text
    , kaphein_SSize textSize
    , int radix
    , kaphein_SSize * endIndexOut
    , kaphein_IntLeast32 * valueOut
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(text == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(textSize < 0 || radix < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        //TODO : Deal with overflow cases.

        kaphein_SSize i = 0;
        kaphein_IntLeast32 value = 0;
        int state = 0;
        
        for(; state < 2 && i < textSize; ) {
            const char ch = text[i];

            switch(radix) {
            case 2:
                errorCode = kapheinErrorCodeNotImplemented;

                state = 2;
            break;
            case 8:
                errorCode = kapheinErrorCodeNotImplemented;

                state = 2;
            break;
            case 10:
                switch(state) {
                case 0:
                    switch(ch) {
                    case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        value = (ch - '0');

                        ++i;
                        state = 1;
                    break;
                    default:
                        errorCode = kapheinErrorCodeArgumentInvalid;

                        state = 2;
                    }
                break;
                case 1:
                    switch(ch) {
                    case '0':
                    case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        value *= 10;
                        value += (ch - '0');

                        ++i;
                    break;
                    default:
                        state = 2;
                    }
                break;
                }
            break;
            case 16:
                switch(ch) {
                case '0':
                case '1': case '2': case '3':
                case '4': case '5': case '6':
                case '7': case '8': case '9':
                    value *= 10;
                    value += (ch - '0');

                    ++i;
                    state = 1;
                break;
                case 'A': case 'B': case 'C':
                case 'D': case 'E': case 'F':
                    value *= 10;
                    value += (ch - 'A') << 4;

                    ++i;
                    state = 1;
                break;
                case 'a': case 'b': case 'c':
                case 'd': case 'e': case 'f':
                    value *= 10;
                    value += (ch - 'a') << 4;

                    ++i;
                    state = 1;
                break;
                default:
                    if(state < 1) {
                        errorCode = kapheinErrorCodeArgumentInvalid;
                    }
                    
                    state = 2;
                }
            break;
            default:
                errorCode = kapheinErrorCodeNotSupported;

                state = 2;
            }
        }

        if(state < 2 && errorCode == kapheinErrorCodeNoError) {
            errorCode = kapheinErrorCodeCollectionUnderflow;
        }

        if(endIndexOut != KAPHEIN_NULL) {
            *endIndexOut = i;
        }

        if(valueOut != KAPHEIN_NULL) {
            *valueOut = value;
        }
    }

    return errorCode;
}
