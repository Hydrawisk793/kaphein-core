#ifndef KAPHEIN_TEXT_JsonSerializable_H
#define KAPHEIN_TEXT_JsonSerializable_H

#include "kaphein/def.h"

struct kapheinTextJsonSerializable
{
    const size_t offsetFromThisObj;

    int (*serialize) (
        void *thisObj
        , char *jsonTextOut
        , int *jsonTextSizeInOut
    );

    int (*deserialize) (
        void *thisObj
        , const char *jsonText
        , int jsonTextSize
    );
};

#endif
