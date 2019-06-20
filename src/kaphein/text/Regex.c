#include "kaphein/mem/utils.h"
#include "kaphein/def.h"
#include "kaphein/ErrorCode.h"
#include "kaphein/mem/utils.h"
#include "kaphein/coll/List.h"
#include "kaphein/text/utils.h"
#include "kaphein/text/RegexMatch.h"
#include "kaphein/text/Regex.h"

enum kaphein_x_RegexOperatorId
{
    kaphein_x_RegexOperatorId_nop = 0
    , kaphein_x_RegexOperatorId_alternateRegex
    , kaphein_x_RegexOperatorId_alternate
    , kaphein_x_RegexOperatorId_concatenate
    , kaphein_x_RegexOperatorId_repet
    , kaphein_x_RegexOperatorId_callTokenExpression
    , kaphein_x_RegexOperatorId_accept
};

enum kaphein_x_RegexOperatorAssociativity
{
    kaphein_x_RegexOperatorAssociativity_none = 0
    , kaphein_x_RegexOperatorAssociativity_reserved1 = 1
    , kaphein_x_RegexOperatorAssociativity_leftToRight = 2
    , kaphein_x_RegexOperatorAssociativity_rightToLeft = 3
};

struct kaphein_x_RegexOperator
{
    enum kaphein_x_RegexOperatorId id_;

    enum kaphein_x_RegexOperatorAssociativity associativity_;
    
    int parameterCount_;

    int priority_;
};

static const struct kaphein_x_RegexOperator kaphein_x_Regex_operators[] = {
    {
        kaphein_x_RegexOperatorId_nop
        , kaphein_x_RegexOperatorAssociativity_none
        , 0
        , 0
    }
    , {
        kaphein_x_RegexOperatorId_alternateRegex
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 2
        , 4
    }
    , {
        kaphein_x_RegexOperatorId_alternate
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 2
        , 4
    }
    , {
        kaphein_x_RegexOperatorId_concatenate
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 2
        , 3
    }
    , {
        kaphein_x_RegexOperatorId_repet
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 1
        , 2
    }
    , {
        kaphein_x_RegexOperatorId_callTokenExpression
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 0
        , 10
    }
    , {
        kaphein_x_RegexOperatorId_accept
        , kaphein_x_RegexOperatorAssociativity_leftToRight
        , 0
        , 20
    }
};

enum kaphein_x_RegexAstNodeType
{
    kaphein_x_RegexAstNodeType_text
    , kaphein_x_RegexAstNodeType_operator
    , kaphein_x_RegexAstNodeType_identifier
};

struct kaphein_x_RegexAstTextTag
{
    char * text_;

    kaphein_SSize textSize_;
};

struct kaphein_x_RegexAstOperatorTag
{
    enum kaphein_x_RegexOperatorId id_;

    void * tag_;

    kaphein_SSize tagSize_;
};

/* **************************************************************** */
/* RegexAstNode */

/* ******************************** */
/* Delcarations */

struct kaphein_x_RegexAstNode
{
    void * allocator_;
	
    struct kaphein_x_RegexAstNode * parent_;

    struct kaphein_x_RegexAstNode * children_;
    
    kaphein_SSize childrenCount_;

    int tagDiscriminator_;

    void * tag_;

    kaphein_SSize tagSize_;
};

/* ******************************** */

/* ******************************** */
/* Definitions */



/* ******************************** */

/* **************************************************************** */

/* **************************************************************** */
/* ExpressionContext */

/* ******************************** */
/* Delcarations */

struct kaphein_x_ExpressionContext
{
    void * allocator_;
    
    union
    {
        struct kaphein_coll_List * a_[2];

        struct {
            struct kaphein_coll_List * term_;

            struct kaphein_coll_List * op_;
        } m_;
    } stacks_;
};

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_construct(
    struct kaphein_x_ExpressionContext * thisObjOut
    , void * allocator
);

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_destruct(
    struct kaphein_x_ExpressionContext * thisObj
);

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_pushTextTerm(
    struct kaphein_x_ExpressionContext * thisObj
    , const char * text
    , kaphein_SSize textSize
);

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_pushOperator(
    struct kaphein_x_ExpressionContext * thisObj
    , enum kaphein_x_RegexOperatorId opId
    , const void * tag
    , kaphein_SSize tagSize
);

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_evaluate(
    struct kaphein_x_ExpressionContext * thisObj
    , struct kaphein_x_RegexAstNode * astNodeOut
    , void * allocator
);

/* ******************************** */

/* ******************************** */
/* Definitions */

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_construct(
    struct kaphein_x_ExpressionContext * thisObjOut
    , void * allocator
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObjOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObjOut->allocator_ = allocator;

    //    thisObjOut->stacks_.m_.term_ = KAPHEIN_NULL;
    //    thisObjOut->stacks_.m_.op_ = KAPHEIN_NULL;

    //    thisObjOut->stacks_.m_.term_ = kaphein_coll_List_new(
    //        thisObjOut->allocator_
    //        , KAPHEIN_NULL
    //        , &errorCode
    //    );
    //    if(errorCode != kapheinErrorCodeNoError) {
    //        goto endOfCtor;
    //    }
    //    errorCode = kaphein_coll_List_construct(
    //        thisObjOut->stacks_.m_.term_
    //        , KAPHEIN_NULL
    //        , allocator
    //    );
    //    if(errorCode != kapheinErrorCodeNoError) {
    //        goto endOfCtor;
    //    }

    //    thisObjOut->stacks_.m_.op_ = kaphein_coll_List_new(
    //        thisObjOut->allocator_
    //        , KAPHEIN_NULL
    //        , &errorCode
    //    );
    //    if(errorCode != kapheinErrorCodeNoError) {
    //        goto endOfCtor;
    //    }
    //    errorCode = kaphein_coll_List_construct(
    //        thisObjOut->stacks_.m_.op_
    //        , KAPHEIN_NULL
    //        , allocator
    //    );
    //    if(errorCode != kapheinErrorCodeNoError) {
    //        goto endOfCtor;
    //    }

    //endOfCtor:
    //    if(errorCode != kapheinErrorCodeNoError) {
    //        kaphein_x_ExpressionContext_destruct(thisObjOut);
    //    }

        errorCode = kapheinErrorCodeNotImplemented;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_destruct(
    struct kaphein_x_ExpressionContext * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->stacks_.m_.op_ != KAPHEIN_NULL) {
            kaphein_coll_List_destruct(thisObj->stacks_.m_.op_);
            kaphein_coll_List_delete(thisObj->stacks_.m_.op_, thisObj->allocator_);
            thisObj->stacks_.m_.op_ = KAPHEIN_NULL;
        }

        if(thisObj->stacks_.m_.term_ != KAPHEIN_NULL) {
            kaphein_coll_List_destruct(thisObj->stacks_.m_.term_);
            kaphein_coll_List_delete(thisObj->stacks_.m_.term_, thisObj->allocator_);
            thisObj->stacks_.m_.term_ = KAPHEIN_NULL;
        }
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_pushTextTerm(
    struct kaphein_x_ExpressionContext * thisObj
    , const char * text
    , kaphein_SSize textSize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        //struct kaphein_x_RegexAstTermTag * termTag;
        //struct kaphein_x_RegexAstNode * astNode;

        text;
        textSize;

        //errorCode = kaphein_coll_List_pushBack(
        //    thisObj->stacks_.m_.term_
        //    , astNode
        //    , KAPHEIN_ssizeof(astNode)
        //);

        errorCode = kapheinErrorCodeNotImplemented;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_pushOperator(
    struct kaphein_x_ExpressionContext * thisObj
    , enum kaphein_x_RegexOperatorId opId
    , const void * tag
    , kaphein_SSize tagSize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        //struct kaphein_x_RegexAstTermTag * termTag;
        struct kaphein_x_RegexAstNode * astNode;
        
        errorCode = kaphein_coll_List_pushBack(
            thisObj->stacks_.m_.op_
            , astNode
            , KAPHEIN_ssizeof(astNode)
        );

        opId;
        tag;
        tagSize;

        errorCode = kapheinErrorCodeNotImplemented;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_ExpressionContext_evaluate(
    struct kaphein_x_ExpressionContext * thisObj
    , struct kaphein_x_RegexAstNode * astNodeOut
    , void * allocator
);

/* ******************************** */

/* **************************************************************** */

/* **************************************************************** */
/* RegexParser */

/* ******************************** */
/* Declarations */

struct kaphein_x_RegexParser
{
    void * allocator_;

    char * regex_;

    int state_;

    struct kaphein_coll_List * exprCtxtStack_;

    kaphein_SSize regexSize_;

    kaphein_SSize cursor_;
};

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_construct(
    struct kaphein_x_RegexParser * thisObj
    , void * allocator
    , void * hint
);

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_destruct(
    struct kaphein_x_RegexParser * thisObj
);

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_parseRepetOperator(
    struct kaphein_x_RegexParser * thisObj
    , kaphein_SSize startIndex
    , kaphein_SSize * endIndexOut
    , int * repetitionTypeOut
    , kaphein_IntLeast32 * minCountOut
    , kaphein_IntLeast32 * maxCountOut
);

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_parse(
    struct kaphein_x_RegexParser * thisObj
    , const char * regex
    , kaphein_SSize regexSize
);

/* ******************************** */

/* ******************************** */
/* Definitions */

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_construct(
    struct kaphein_x_RegexParser * thisObj
    , void * allocator
    , void * hint
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObj->allocator_ = allocator;
        thisObj->regex_ = KAPHEIN_NULL;
        thisObj->state_ = 0;
        thisObj->exprCtxtStack_ = KAPHEIN_NULL;
        thisObj->regexSize_ = 0;
        thisObj->cursor_ = 0;

        hint;

        errorCode = kaphein_coll_List_construct(
            thisObj->exprCtxtStack_
            , KAPHEIN_NULL
            , allocator
        );
        if(errorCode != kapheinErrorCodeNoError) {
            kaphein_x_RegexParser_destruct(thisObj);
        }
    }
    
    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_destruct(
    struct kaphein_x_RegexParser * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->exprCtxtStack_ != KAPHEIN_NULL) {
            kaphein_coll_List_destruct(thisObj->exprCtxtStack_);
            thisObj->exprCtxtStack_ = KAPHEIN_NULL;
        }
    }
    
    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_parseRepetOperator(
    struct kaphein_x_RegexParser * thisObj
    , kaphein_SSize startIndex
    , kaphein_SSize * endIndexOut
    , int * repetitionTypeOut
    , kaphein_IntLeast32 * minCountOut
    , kaphein_IntLeast32 * maxCountOut
)
{
    //TODO : 코드 검증
    
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    kaphein_SSize i = startIndex;
    kaphein_SSize decTokenEndIndex;
    kaphein_IntLeast32 minCount = -1;
    kaphein_IntLeast32 maxCount = -1;
    int repetitionType = 0;
    int state = 0;

    for(; state < 6 && i < thisObj->regexSize_; ) {
        const char ch = thisObj->regex_[i];

        switch(state) {
        case 0:
            switch(ch) {
            case '*':
                ++i;
                state = 1;
            break;
            case '+':
                ++i;
                state = 1;
            break;
            case '?':
                ++i;
                state = 1;
            break;
            case '{':
                ++i;
                state = 2;
            break;
            }
        break;
        case 1:
            switch(ch) {
            case '+':
                repetitionType = 1;
                
                ++i;
                state = 6;
            break;
            case '?':
                repetitionType = 2;
                
                ++i;
                state = 6;
            break;
            default:
                state = 6;
            //break;
            }
        break;
        case 2:
            errorCode = kaphein_text_parseInt32(
                thisObj->regex_ + i
                , i + 1
                , 10
                , &decTokenEndIndex
                , &minCount
            );
            i += decTokenEndIndex;

            if(errorCode == kapheinErrorCodeNoError) {
                state = 3;
            }
            else {
                state = 6;
            }
        break;
        case 3:
            switch(ch) {
            case ',':
                ++i;
                state = 4;
            break;
            case '}':
                ++i;
                state = 6;
            break;
            }
        break;
        case 4:
            errorCode = kaphein_text_parseInt32(
                thisObj->regex_ + i
                , i + 1
                , 10
                , &decTokenEndIndex
                , &maxCount
            );
            i += decTokenEndIndex;

            if(errorCode == kapheinErrorCodeNoError) {
                state = 3;
            }
            else {
                state = 5;
            }
        break;
        case 5:
            switch(ch) {
            case '}':
                ++i;
            break;
            default:
                errorCode = kapheinErrorCodeArgumentInvalid;
            }

            state = 6;
        break;
        }
    }

    if(state < 6 && errorCode == kapheinErrorCodeNoError) {
        errorCode = kapheinErrorCodeCollectionUnderflow;
    }

    if(endIndexOut != KAPHEIN_NULL) {
        *endIndexOut = i;
    }

    if(repetitionTypeOut != KAPHEIN_NULL) {
        *repetitionTypeOut = repetitionType;
    }

    if(minCountOut != KAPHEIN_NULL) {
        *minCountOut = minCount;
    }

    if(maxCountOut != KAPHEIN_NULL) {
        *maxCountOut = maxCount;
    }

    return errorCode;
}

static
enum kaphein_ErrorCode
kaphein_x_RegexParser_parse(
    struct kaphein_x_RegexParser * thisObj
    , const char * regex
    , kaphein_SSize regexSize
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;
    
    if(thisObj->regexSize_ < regexSize) {
        if(thisObj->regex_ != KAPHEIN_NULL) {
            kaphein_mem_deallocate(thisObj->allocator_, thisObj->regex_, regexSize);
            thisObj->regex_ = KAPHEIN_NULL;
        }
        thisObj->regexSize_ = 0;

        thisObj->regex_ = (char *)kaphein_mem_allocate(thisObj->allocator_, regexSize + 1, KAPHEIN_NULL, &errorCode);
        thisObj->regexSize_ = regexSize + 1;
    }

    kaphein_mem_copy(thisObj->regex_, thisObj->regexSize_ - 1, regex, regexSize);
    thisObj->regex_[thisObj->regexSize_ - 1] = '\0';
    thisObj->cursor_ = 0;

    for(; errorCode == kapheinErrorCodeNoError && thisObj->cursor_ < thisObj->regexSize_; ) {
        kaphein_SSize endIndex;
        const char ch = thisObj->regex_[thisObj->cursor_];

        switch(ch) {
        case '^':
            errorCode = kapheinErrorCodeNotImplemented;
        break;
        case '$':
            errorCode = kapheinErrorCodeNotImplemented;
        break;
        case '(':
            
        break;
        case ')':
            
        break;
        case '*':
        case '+':
        case '?':
        case '{':
            errorCode = kaphein_x_RegexParser_parseRepetOperator(
                thisObj
                , thisObj->cursor_
                , &endIndex
                , NULL
                , NULL
                , NULL
            );
            if(errorCode == kapheinErrorCodeNoError) {
                
            }
        break;
        case '}':
            
        break;
        case '|':
            
        break;
        case '.':
            
        break;
        case '[':
            
        break;
        case ']':
            
        break;
        case '\\':
            
        break;
        }
    }

    return kapheinErrorCodeNotImplemented;
}

/* ******************************** */

/* **************************************************************** */

enum kaphein_x_Opcode
{
    kaphein_x_Opcode_nop = 0x00
    , kaphein_x_Opcode_accept = 0x01
    , kaphein_x_Opcode_branch = 0x10
    , kaphein_x_Opcode_fork = 0x11
    , kaphein_x_Opcode_jsr = 0x12
    , kaphein_x_Opcode_rts = 0x13
    , kaphein_x_Opcode_grpbegin = 0x20
    , kaphein_x_Opcode_grpend = 0x21
    , kaphein_x_Opcode_test = 0x30
    , kaphein_x_Opcode_testrange = 0x31
};

/* **************************************************************** */
/* ByteCode */

/* ******************************** */
/* Declarations */

struct kaphein_x_ByteCode
{
    void * allocator_;
    
    kaphein_UIntLeast8 * data_;

    kaphein_SSize dataSize_;
};

enum kaphein_ErrorCode
kaphein_x_ByteCode_new(
    struct kaphein_x_ByteCode ** ptrOut
    , void * allocator
    , void * hint
);

enum kaphein_ErrorCode
kaphein_x_ByteCode_delete(
    struct kaphein_x_ByteCode * ptr
);

enum kaphein_ErrorCode
kaphein_x_ByteCode_construct(
    struct kaphein_x_ByteCode * thisObjOut
    , const char * data
    , kaphein_SSize dataSize
    , void * allocator
);

enum kaphein_ErrorCode
kaphein_x_ByteCode_destruct(
    struct kaphein_x_ByteCode * thisObj
);

/* ******************************** */

/* ******************************** */
/* Definitions */

enum kaphein_ErrorCode
kaphein_x_ByteCode_new(
    struct kaphein_x_ByteCode ** ptrOut
    , void * allocator
    , void * hint
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(ptrOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *ptrOut = (struct kaphein_x_ByteCode *)kaphein_mem_allocate(
            allocator
            , KAPHEIN_ssizeof(struct kaphein_x_ByteCode)
            , hint
            , &errorCode
        );
        if(*ptrOut == NULL) {
            *ptrOut = KAPHEIN_NULL;

            errorCode = kapheinErrorCodeMemoryAllocationFailed;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_x_ByteCode_delete(
    struct kaphein_x_ByteCode * ptr
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(ptr == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        errorCode = kaphein_mem_deallocate(ptr->allocator_, ptr, KAPHEIN_ssizeof(*ptr));
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_x_ByteCode_construct(
    struct kaphein_x_ByteCode * thisObjOut
    , const char * data
    , kaphein_SSize dataSize
    , void * allocator
);

enum kaphein_ErrorCode
kaphein_x_ByteCode_destruct(
    struct kaphein_x_ByteCode * thisObj
);

/* ******************************** */

/* **************************************************************** */

struct kaphein_x_VmThread
{
    int dummy_;
};

struct kaphein_x_VmFrame
{
    int dummy_;
};

/* **************************************************************** */
/* Regex */

/* ******************************** */
/* Declarations */

struct kaphein_text_Regex
{
    void * allocator_;
    
    struct kaphein_x_ByteCode * byteCode_;
};

/* ******************************** */

/* ******************************** */
/* Definitions */

enum kaphein_ErrorCode
kaphein_text_Regex_new(
    struct kaphein_text_Regex ** objOut
    , void * allocator
    , void * hint
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(objOut == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *objOut = (struct kaphein_text_Regex *)kaphein_mem_allocate(
            allocator
            , KAPHEIN_ssizeof(struct kaphein_text_Regex)
            , hint
            ,  &errorCode
        );
        if(*objOut == NULL) {
            *objOut = KAPHEIN_NULL;
            errorCode = kapheinErrorCodeMemoryAllocationFailed;
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_text_Regex_delete(
    struct kaphein_text_Regex * obj
    , void * allocator
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(obj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        errorCode = kaphein_mem_deallocate(allocator, obj, KAPHEIN_ssizeof(*obj));
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_text_Regex_compile(
    struct kaphein_text_Regex * thisObj
    , const char * regex
    , kaphein_SSize regexSize
    , void * allocator
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || regex == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else if(regexSize < 0) {
        errorCode = kapheinErrorCodeArgumentOutOfRange;
    }
    else {
        //TODO : Compile the regex parameter.
        struct kaphein_x_RegexParser parser;

        errorCode = kaphein_x_RegexParser_construct(&parser, allocator, KAPHEIN_NULL);
        if(errorCode != kapheinErrorCodeNoError) {
            goto endOfCompilation;
        }
        
        errorCode = kaphein_x_RegexParser_parse(&parser, regex, regexSize);
        if(errorCode != kapheinErrorCodeNoError) {
            goto endOfCompilation;
        }

    endOfCompilation:
        kaphein_x_RegexParser_destruct(&parser);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_text_Regex_destruct(
    struct kaphein_text_Regex * thisObj
)
{
    enum kaphein_ErrorCode errorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        errorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        if(thisObj->byteCode_ != KAPHEIN_NULL) {
            //kaphein_x_ByteCode_destruct(thisObj->byteCode_);
            thisObj->byteCode_ = KAPHEIN_NULL;
        }
    }

    return errorCode;
}

/* ******************************** */

/* **************************************************************** */
