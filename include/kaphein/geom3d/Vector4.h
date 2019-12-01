#ifndef KAPHEIN_GEOM3D_Vector4_H
#define KAPHEIN_GEOM3D_Vector4_H

#include "../def.h"
#include "../ErrorCode.h"

struct kaphein_geom3d_Vector4
{
    union {
        float a[4];

        struct {
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
kaphein_geom3d_Vector4_setZero(
    struct kaphein_geom3d_Vector4 * thisObj
);


KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_fill(
    struct kaphein_geom3d_Vector4 * thisObj
    , float value
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_negate(
    const struct kaphein_geom3d_Vector4 * thisObj
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_add(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_subtract(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_scale(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float scalar
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_dot(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_norm2Sq(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_norm2(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_normalize(
    const struct kaphein_geom3d_Vector4 * thisObj
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Projects a vector on another vector.
 *  @param thisObj An input vector.
 *  @param axis Another input vector.
 *  @param[out] resultOut The perpendicular vector of lhs and rhs.
 *  <br/>The pointer must not be equal to lhs's or rhs's.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_project(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * axis
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_projectOnPlane(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * normal
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_reflect(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * normal
    , struct kaphein_geom3d_Vector4 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector4_lerp(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , float ratio
    , struct kaphein_geom3d_Vector4 * resultOut
);

#endif
