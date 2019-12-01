#ifndef KAPHEIN_HGRD_kaphein_geom3d_Quaternion_H
#define KAPHEIN_HGRD_kaphein_geom3d_Quaternion_H

#include "../ErrorCode.h"
#include "Vector3.h"
#include "Vector4.h"

struct kaphein_geom3d_Quaternion
{
    union {
        float a[4];

        struct kaphein_geom3d_Vector4 v;

        struct {
            struct kaphein_geom3d_Vector3 imaginary;

            float real;
        } p;
    } u;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_setZero(
    struct kaphein_geom3d_Quaternion * quatOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_setIdentity(
    struct kaphein_geom3d_Quaternion * quatOut
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_axisAngle(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Vector3 *axis
    , float radian
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_eulerAngles(
    struct kaphein_geom3d_Quaternion * quatOut
    , float xRadian
    , float yRadian
    , float zRadian
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_fromToRotation(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Vector3 *from
    , const struct kaphein_geom3d_Vector3 *to
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_lookRotation(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Vector3 *lookAtDirection
    , const struct kaphein_geom3d_Vector3 *upDirection
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_isConjugateOf(
    const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_isInverseOf(
    const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_norm2Sq(
    const struct kaphein_geom3d_Quaternion * quat,
    float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_norm2(
    const struct kaphein_geom3d_Quaternion * quat,
    float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_normalize(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_conjugate(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_invert(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_add(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_subtract(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Multiplies two quaternions.
 *  @param[out] quatOut The muliplied quaternion.
 *  <br/>The pointer must not be equal to lhs's or rhs's.
 *  @param lhs A quaternion.
 *  @param rhs Another quaternion.
 *  @return 
 */
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_multiply(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_scale(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
    , float s
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_lerp(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * from
    , const struct kaphein_geom3d_Quaternion * to
    , float ratio
);

// KAPHEIN_ATTRIBUTE_C_LINKAGE
// KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_slerp(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * from
    , const struct kaphein_geom3d_Quaternion * to
    , float ratio
);

#endif
