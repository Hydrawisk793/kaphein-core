#ifndef KAPHEIN_HGRD_kaphein_geom3d_Vector3_h
#define KAPHEIN_HGRD_kaphein_geom3d_Vector3_h

#include "../def.h"
#include "../ErrorCode.h"

struct kaphein_geom3d_Vector3
{
    union
    {
        float a[3];

        struct
        {
            float x;

            float y;

            float z;
        } m;
    } u;
};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_copyTo(
    const struct kaphein_geom3d_Vector3 * src
    , struct kaphein_geom3d_Vector3 * dest
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_setZero(
    struct kaphein_geom3d_Vector3 * thisObj
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_fill(
    struct kaphein_geom3d_Vector3 * thisObj
    , float value
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_setXyz(
    struct kaphein_geom3d_Vector3 * thisObj
    , float x
    , float y
    , float z
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_negate(
    const struct kaphein_geom3d_Vector3 * thisObj
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_add(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * other
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_subtract(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * other
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_scale(
    const struct kaphein_geom3d_Vector3 * thisObj
    , float scalar
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
/**
 *  @brief Calculates the cross product of two vectors.
 *  @param thisObj An input vector.
 *  @param other Another input vector.
 *  @param[out] resultOut The cross product of two vectors.
 *  @return An error code.
 */
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_cross(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * other
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_dot(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * other
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_norm2Sq(
    const struct kaphein_geom3d_Vector3 * thisObj
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_norm2(
    const struct kaphein_geom3d_Vector3 * thisObj
    , float * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_normalize(
    const struct kaphein_geom3d_Vector3 * thisObj
    , struct kaphein_geom3d_Vector3 * resultOut
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
kaphein_geom3d_Vector3_project(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * axis
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_projectOnPlane(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * normal
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_reflect(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * normal
    , struct kaphein_geom3d_Vector3 * resultOut
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
enum kaphein_ErrorCode
kaphein_geom3d_Vector3_lerp(
    const struct kaphein_geom3d_Vector3 * thisObj
    , const struct kaphein_geom3d_Vector3 * other
    , float ratio
    , struct kaphein_geom3d_Vector3 * resultOut
);

#endif
