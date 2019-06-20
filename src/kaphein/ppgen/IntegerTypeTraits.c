#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kaphein/ppgen/IntegerTypeTraits.h"

int kaphein_ppgen_GenerateIntegerTypeTraitMacros(
    const char * filePath
    , kaphein_SSize filePathSize
    , int maximumBitSize
)
{
    char * tempText;
    FILE * fout;
    kaphein_UInt64 uIntMax;
    int i;

    tempText = (char *)malloc(1024);

    memcpy(tempText, filePath, filePathSize);
    tempText[filePathSize] = '\0';
    fout = fopen(tempText, "wt");
    free(tempText);

    for(uIntMax = 1, i = 1; i <= maximumBitSize; uIntMax <<= 1, uIntMax |= 1, ++i) {
        fprintf(
            fout
            , "#define KAPHEIN_x_UNSIGNED_INTEGER_MINIMUM_VALUE_%d 0x%llX\n"
            , i
            , 0ll
        );

        fprintf(
            fout
            , "#define KAPHEIN_x_UNSIGNED_INTEGER_MAXIMUM_VALUE_%d 0x%llX\n"
            , i
            , uIntMax
        );
    }
    
    fputs("\r\n", fout);
    for(uIntMax = 1, i = 1; i <= maximumBitSize; uIntMax <<= 1, uIntMax |= 1, ++i) {
        fprintf(
            fout
            , "#define KAPHEIN_x_SIGNED_INTEGER_MINIMUM_VALUE_%d 0x%llX\n"
            , i
            , ((uIntMax >> 1) + 1)
        );

        fprintf(
            fout
            , "#define KAPHEIN_x_SIGNED_INTEGER_MAXIMUM_VALUE_%d 0x%llX\n"
            , i
            , (uIntMax >> 1)
        );
    }

    fclose(fout);

    return 0;
}
