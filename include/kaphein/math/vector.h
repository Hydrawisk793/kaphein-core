#ifndef KAPHEIN_HGRD_kaphein_math_vector_h
#define KAPHEIN_HGRD_kaphein_math_vector_h

#include "../ErrorCode.h"

/* **************************************************************** */
/* V3F32 functions */

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_zeroV3F32(
    float * vInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_fillV3F32(
    float * vInOut
    , float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_negateV3F32(
    float * vOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_addV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_subtractV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_scaleV3F32(
    float * vOut
    , const float * vIn
    , float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_crossV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_dotV3F32(
    float * sOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_norm2SqV3F32(
    float * sOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_norm2V3F32(
    float * sOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_normalizeV3F32(
    float * vOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
/**
 *  @brief Projects a vector on another vector.
 *  @param[out] vecOut The perpendicular vector of lhs and rhs.
 *  <br/>The pointer must not be equal to lhs's or rhs's.
 *  @param lhs An input vector.
 *  @param rhs Another input vector.
 *  @return An error code.
 */
kaphein_math_projectV3F32(
    float * vOut
    , const float * vIn
    , const float * axis
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_projectOnPlaneV3F32(
    float * vOut
    , const float * vIn
    , const float * normal
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_reflectV3F32(
    float * vOut
    , const float * vIn
    , const float * normal
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_lerpV3F32(
    float * vOut
    , const float * from
    , const float * to
    , float ratio
);

/* **************************************************************** */

/* **************************************************************** */
/* V4F32 functions */

struct kaphein_math_Vector4
{
    union
    {
        float a[4];

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
kaphein_math_zeroV4F32(
    float * vInOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_fillV4F32(
    float * vInOut
    , float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_negateV4F32(
    float * vOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_addV4F32(
    float * vOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_subtractV4F32(
    float * vOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_scaleV4F32(
    float * vOut
    , const float * vIn
    , float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_dotV4F32(
    float * sOut
    , const float * lhs
    , const float * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_norm2SqV4F32(
    float * sOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_norm2V4F32(
    float * sOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_normalizeV4F32(
    float * vOut
    , const float * vIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_projectV4F32(
    float * vOut
    , const float * vIn
    , const float * axis
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_projectOnPlaneV4F32(
    float * vOut
    , const float * vIn
    , const float * normal
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_reflectV4F32(
    float * vOut
    , const float * vIn
    , const float * normal
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_math_lerpV4F32(
    float * vOut
    , const float * from
    , const float * to
    , float ratio
);

/* **************************************************************** */

#endif
