#include "kaphein/coll/List.h"
#include "kaphein/text/Lexer.h"

enum IntegerType;

struct RegexVm;

struct RegexVmFrame;

struct RegexVmThread;

enum RegexVmOperandType;

enum RegexVmInstruction;

struct RegexVmByteCode;

/* **************************************************************** */
/* IntegerType */

enum IntegerType
{
    IntegerType_int8 = 0
    , IntegerType_uint8
    , IntegerType_int16
    , IntegerType_uint16
    , IntegerType_int32
    , IntegerType_uint32
    , IntegerType_int64
    , IntegerType_uint64
};

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
int
IntegerType_getSize(
    enum IntegerType thisObj
);

KAPHEIN_ATTRIBUTE_FORCE_INLINE
static
bool
IntegerType_isSigned(
    enum IntegerType thisObj
);

static
int
IntegerType_getSize(
    enum IntegerType thisObj
)
{
    return 1 << ((thisObj & 0xFE) >> 1);
}

static
bool
IntegerType_isSigned(
    enum IntegerType thisObj
)
{
    return !(thisObj & 0x1);
}

/* **************************************************************** */

/* **************************************************************** */
/* RegexVm */

struct RegexVm
{
    const char * inStr;

    const struct RegexVmByteCode * bytecode;

    int cursor;

    int thIdSeq;

    kaphein_SSize inStrSize;
};

static
void
RegexVm_run(
    struct RegexVm * thisObj
    , int startIndex
    , struct kaphein_text_Match * matchOut
);

/* **************************************************************** */

/* **************************************************************** */
/* RegexVmFrame */

struct RegexVmFrame
{
    int returnAddress;


};

/* **************************************************************** */

/* **************************************************************** */
/* RegexVmThread */

struct RegexVmThread
{
    struct RegexVm * vm;

    struct RegexVmThread * parent;

    int id;

    int pc;

    int forkKey;

    int lastOpCode;

    int instAddr;
};

static
void
RegexVmThread_construct(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_destruct(
    struct RegexVmThread * thisObj
);

static
bool
RegexVmThread_isDead(
    const struct RegexVmThread * thisObj
);

static
int
RegexVmThread_comparePriorityTo(
    const struct RegexVmThread * thisObj
    , const struct RegexVmThread * other
);

static
bool
RegexVmThread_isPriorTo(
    const struct RegexVmThread * thisObj
    , const struct RegexVmThread * other
);

static
bool
RegexVmThread_hasSamePathPostfixWith(
    const struct RegexVmThread * thisObj
    , const struct RegexVmThread * other
);

static
struct RegexVmFrame *
RegexVmThread_getCurrentFrame(
    const struct RegexVmThread * thisObj
);

static
void
RegexVmThread_execute(
    struct RegexVmThread * thisObj
);

static
int
RegexVmThread_readOpCode(
    struct RegexVmThread * thisObj
);

static
int
RegexVmThread_readInteger(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_branch(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_jumpToSubroutine(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_returnFromSubroutine(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_fork(
    struct RegexVmThread * thisObj
    , bool prioritize
);

static
void
RegexVmThread_accept(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_moveConsumePointer(
    struct RegexVmThread * thisObj
    , bool consume
);

static
void
RegexVmThread_beginGroup(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_endGroup(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_testCode(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_testRange(
    struct RegexVmThread * thisObj
);

static
void
RegexVmThread_testRanges(
    struct RegexVmThread * thisObj
);

/* **************************************************************** */

/* **************************************************************** */
/* RegexVmOperandType */

enum RegexVmOperandType
{
    RegexVmOperandType_offset = 0
    , RegexVmOperandType_address
    , RegexVmOperandType_byteIndex
    , RegexVmOperandType_index
    , RegexVmOperandType_characterCode
    , RegexVmOperandType_integerLiteral
};

/* **************************************************************** */

/* **************************************************************** */
/* RegexVmInstruction */

enum RegexVmInstruction
{
    RegexVmInstruction_reserved00 = 0x00
    , RegexVmInstruction_reserved01 = 0x01
    , RegexVmInstruction_bra = 0x02
    , RegexVmInstruction_bsr = 0x03
    , RegexVmInstruction_jmp = 0x04
    , RegexVmInstruction_jsr = 0x05
    , RegexVmInstruction_rts = 0x06
    , RegexVmInstruction_accept = 0x07
    , RegexVmInstruction_fork = 0x08
    , RegexVmInstruction_pfork = 0x09
    , RegexVmInstruction_skip = 0x0a
    , RegexVmInstruction_consume = 0x0b
    , RegexVmInstruction_reserved0C = 0x0c
    , RegexVmInstruction_reserved0D = 0x0d
    , RegexVmInstruction_groupBegin = 0x0e
    , RegexVmInstruction_groupEnd = 0x0f
    , RegexVmInstruction_testCode = 0x10
    , RegexVmInstruction_reserved11 = 0x11
    , RegexVmInstruction_testRange = 0x12
    , RegexVmInstruction_testRanges = 0x13
    , RegexVmInstruction_reserved14 = 0x14
    , RegexVmInstruction_reserved15 = 0x15
};

/* **************************************************************** */

/* **************************************************************** */
/* RegexVmBytecode */



/* **************************************************************** */
