#ifndef KAPHEIN_HGRD_kaphein_text_Lexer_h
#define KAPHEIN_HGRD_kaphein_text_Lexer_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_text_Lexer
{
    void * impl_;
};

enum kaphein_ErrorCode
kaphein_text_Lexer_construct(
    struct kaphein_text_Lexer * thisObj
    , const char * regex
    , kaphein_SSize regexSize
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_text_Lexer_destruct(
    struct kaphein_text_Lexer * thisObj
);

enum kaphein_ErrorCode
kaphein_text_Lexer_find(
    const struct kaphein_text_Lexer * thisObj
    , const char * text
    , kaphein_SSize textSize
    , struct kaphein_text_Match * matchesOut
    , kaphein_SSize matchesOutSize
);

#endif
