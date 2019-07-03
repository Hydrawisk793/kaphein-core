#ifndef KAPHEIN_HGRD_kaphein_text_LexerGenerator_h
#define KAPHEIN_HGRD_kaphein_text_LexerGenerator_h

#include "../mem/Allocator.h"
#include "def.h"

struct kaphein_text_LexerGenerator
{
    void * impl_;
};

enum kaphein_ErrorCode
kaphein_text_LexerGenerator_construct(
    struct kaphein_text_LexerGenerator * thisObj
    , struct kaphein_mem_Allocator * allocator
);

enum kaphein_ErrorCode
kaphein_text_LexerGenerator_destruct(
    struct kaphein_text_LexerGenerator * thisObj
);

enum kaphein_ErrorCode
kaphein_text_LexerGenerator_defineToken(
    struct kaphein_text_LexerGenerator * thisObj
    , const char * name
    , kaphein_SSize nameSize
    , const char * regex
    , kaphein_SSize regexSize
);

enum kaphein_ErrorCode
kaphein_text_LexerGenerator_generate(
    struct kaphein_text_LexerGenerator * thisObj
    , struct kaphein_text_Lexer * lexerOut
);

#endif
