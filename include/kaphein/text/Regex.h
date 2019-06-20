#ifndef KAPHEIN_HGRD_kaphein_text_Regex_h
#define KAPHEIN_HGRD_kaphein_text_Regex_h

#include "../def.h"
#include "Regex_fwd.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_Regex_new(
    struct kaphein_text_Regex ** objOut
    , void * allocator
    , void * hint
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_Regex_delete(
    struct kaphein_text_Regex * obj
    , void * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_Regex_compile(
    struct kaphein_text_Regex * thisObj
    , const char * regex
    , kaphein_SSize regexSize
    , void * allocator
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_text_Regex_destruct(
    struct kaphein_text_Regex * thisObj
);

enum kaphein_ErrorCode
kaphein_text_Regex_find(
    const struct kaphein_text_Regex * thisObj
    , const char * text
    , kaphein_SSize textSize
    , struct kaphein_text_RegexMatch * matchesOut
    , kaphein_SSize matchCount
);

#endif
