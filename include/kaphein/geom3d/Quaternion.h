#ifndef KAPHEIN_GEOM3D_Quaternion_H
#define KAPHEIN_GEOM3D_Quaternion_H

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
int kaphein_geom3d_Quaternion_zero(
    struct kaphein_geom3d_Quaternion *quatOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_identity(
    struct kaphein_geom3d_Quaternion *quatOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_axisAngle(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Vector3 *axis
    , float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_eulerAngles(
    struct kaphein_geom3d_Quaternion *quatOut
    , float xRadian
    , float yRadian
    , float zRadian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_fromToRotation(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Vector3 *from
    , const struct kaphein_geom3d_Vector3 *to
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_lookRotation(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Vector3 *lookAtDirection
    , const struct kaphein_geom3d_Vector3 *upDirection
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool kaphein_geom3d_Quaternion_isConjugateOf(
    const struct kaphein_geom3d_Quaternion *lhs
    , const struct kaphein_geom3d_Quaternion *rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool kaphein_geom3d_Quaternion_isInverseOf(
    const struct kaphein_geom3d_Quaternion *lhs
    , const struct kaphein_geom3d_Quaternion *rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_geom3d_Quaternion_norm2Sq(
    const struct kaphein_geom3d_Quaternion *quat
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_geom3d_Quaternion_norm2(
    const struct kaphein_geom3d_Quaternion *quat
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_normalize(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *quatIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_conjugate(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *quatIn
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_geom3d_Quaternion_invert(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *quatIn
);

int kaphein_geom3d_Quaternion_add(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *lhs
    , const struct kaphein_geom3d_Quaternion *rhs
);

int kaphein_geom3d_Quaternion_subtract(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *lhs
    , const struct kaphein_geom3d_Quaternion *rhs
);

/**
 *  @brief Multiplies two quaternions.
 *  @param[out] quatOut The muliplied quaternion.
 *  <br/>The pointer must not be equal to lhs's or rhs's.
 *  @param lhs A quaternion.
 *  @param rhs Another quaternion.
 *  @return 
 */
int kaphein_geom3d_Quaternion_multiply(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *lhs
    , const struct kaphein_geom3d_Quaternion *rhs
);

int kaphein_geom3d_Quaternion_scale(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *quatIn
    , float s
);

int kaphein_geom3d_Quaternion_lerp(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *from
    , const struct kaphein_geom3d_Quaternion *to
    , float ratio
);

int kaphein_geom3d_Quaternion_slerp(
    struct kaphein_geom3d_Quaternion *quatOut
    , const struct kaphein_geom3d_Quaternion *from
    , const struct kaphein_geom3d_Quaternion *to
    , float ratio
);

#endif
