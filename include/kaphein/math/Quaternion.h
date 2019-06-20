#ifndef KAPHEIN_HGRD_kaphein_math_Quaternion_h
#define KAPHEIN_HGRD_kaphein_math_Quaternion_h

#include "../ErrorCode.h"

struct kaphein_math_Quaternion
{
    union
    {
        float v[4];

        struct
        {
            float x;

            float y;

            float z;

            float w;
        } m;
    } u;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_zeroQF32(
    float * qOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_identityQF32(
    float * qOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_axisAngleQF32(
    float * qOut
    , const float * axis
    , float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_eulerAnglesQF32(
    float * qOut
    , float xRadian
    , float yRadian
    , float zRadian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_fromToRotationQF32(
    float * qOut
    , const float * from
    , const float * to
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_lookRotationQF32(
    float * qOut
    , const float * lookAtDirection
    , const float * upDirection
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_isConjugateOfQF32(
    bool * truthOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_isInverseOfQF32(
    bool * truthOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_conjugateQF32(
    float * qOut
    , const float * qIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_invertQF32(
    float * qOut
    , const float * qIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_multiplyQF32(
    float * qOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_slerpQF32(
    float * qOut
    , const float * from
    , const float * to
    , float ratio
);

#endif
