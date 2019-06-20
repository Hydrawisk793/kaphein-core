#ifndef KAPHEIN_HGRD_kaphein_math_matrix_h
#define KAPHEIN_HGRD_kaphein_math_matrix_h

#include "../ErrorCode.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_addMF32(
    float * mOut
    , const float * lhs
    , const float * rhs
    , int n
);

enum kaphein_ErrorCode
kaphein_math_addM4F32(
    float * mOut
    , const float * lhs
    , const float * rhs
);

enum kaphein_ErrorCode
kaphein_math_subtractM4F32(
    float * mOut
    , const float * lhs
    , const float * rhs
);

enum kaphein_ErrorCode
kaphein_math_scaleM4F32(
    float * mOut
    , const float * mIn
    , float s
    , int majorFlag
);

enum kaphein_ErrorCode
kaphein_math_multiplyV4M4F32(
    float * vOut
    , const float * vIn
    , const float * mIn
    , int majorFlag
);

enum kaphein_ErrorCode
kaphein_math_multiplyV4M4F32(
    float * vOut
    , const float * vIn
    , const float * mIn
    , int majorFlag
);

enum kaphein_ErrorCode
kaphein_math_multiplyM4V4F32(
    float * vOut
    , const float * mIn
    , const float * vIn
    , int majorFlag
);

enum kaphein_ErrorCode
kaphein_math_multiplyM4F32(
    float * mOut
    , const float * lhs
    , const float * rhs
    , int majorFlags
);

enum kaphein_ErrorCode
kaphein_math_invertM4F32(
    float * mOut
    , const float * mIn
);

#endif
