#include "kaphein/geom3d/Quaternion.h"

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_setZero(
    struct kaphein_geom3d_Quaternion * quatOut
)
{
    quatOut->u.a[0] = 0.0f;
    quatOut->u.a[1] = 0.0f;
    quatOut->u.a[2] = 0.0f;
    quatOut->u.a[3] = 0.0f;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_setIdentity(
    struct kaphein_geom3d_Quaternion * quatOut
)
{
    quatOut->u.a[0] = 0.0f;
    quatOut->u.a[1] = 0.0f;
    quatOut->u.a[2] = 0.0f;
    quatOut->u.a[3] = 1.0f;

    return kapheinErrorCodeNoError;
}

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_axisAngle(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Vector3 *axis
//     , float radian
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_eulerAngles(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , float xRadian
//     , float yRadian
//     , float zRadian
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_fromToRotation(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Vector3 *from
//     , const struct kaphein_geom3d_Vector3 *to
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_lookRotation(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Vector3 *lookAtDirection
//     , const struct kaphein_geom3d_Vector3 *upDirection
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_isConjugateOf(
//     const struct kaphein_geom3d_Quaternion * lhs->u.v.u.a
//     , const struct kaphein_geom3d_Quaternion * rhs->u.v.u.a
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_isInverseOf(
//     const struct kaphein_geom3d_Quaternion * lhs->u.v.u.a
//     , const struct kaphein_geom3d_Quaternion * rhs->u.v.u.a
// );

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_norm2Sq(
    const struct kaphein_geom3d_Quaternion * quat,
    float * resultOut
)
{
    return kaphein_geom3d_Vector4_norm2Sq(
        &quat->u.v,
        resultOut
    );
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_norm2(
    const struct kaphein_geom3d_Quaternion * quat,
    float * resultOut
)
{
    return kaphein_geom3d_Vector4_norm2(
        &quat->u.v,
        resultOut
    );
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_normalize(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
)
{
    return kaphein_geom3d_Vector4_norm2(
        &quatOut->u.v,
        &quatIn->u.v
    );
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_conjugate(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
)
{
    quatOut->u.a[0] = -quatIn->u.a[0];
    quatOut->u.a[1] = -quatIn->u.a[1];
    quatOut->u.a[2] = -quatIn->u.a[2];
    quatOut->u.a[3] = quatIn->u.a[3];

    return kapheinErrorCodeNoError;
}

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_invert(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Quaternion * quatIn
// );

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_add(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
)
{
    return kaphein_geom3d_Vector4_add(
        &lhs->u.v,
        &rhs->u.v,
        &quatOut->u.v
    );
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_subtract(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
)
{
    return kaphein_geom3d_Vector4_subtract(
        &lhs->u.v,
        &rhs->u.v,
        &quatOut->u.v
    );
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_multiply(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * lhs
    , const struct kaphein_geom3d_Quaternion * rhs
)
{
    quatOut->u.v.u.a[0] = rhs->u.v.u.a[0] * lhs->u.v.u.a[3] + rhs->u.v.u.a[3] * lhs->u.v.u.a[0] - rhs->u.v.u.a[2] * lhs->u.v.u.a[1] + rhs->u.v.u.a[1] * lhs->u.v.u.a[2];
    quatOut->u.v.u.a[1] = rhs->u.v.u.a[1] * lhs->u.v.u.a[3] + rhs->u.v.u.a[2] * lhs->u.v.u.a[0] + rhs->u.v.u.a[3] * lhs->u.v.u.a[1] - rhs->u.v.u.a[0] * lhs->u.v.u.a[2];
    quatOut->u.v.u.a[2] = rhs->u.v.u.a[2] * lhs->u.v.u.a[3] - rhs->u.v.u.a[1] * lhs->u.v.u.a[0] + rhs->u.v.u.a[0] * lhs->u.v.u.a[1] + rhs->u.v.u.a[3] * lhs->u.v.u.a[2];
    quatOut->u.v.u.a[3] = rhs->u.v.u.a[3] * lhs->u.v.u.a[3] - rhs->u.v.u.a[0] * lhs->u.v.u.a[0] - rhs->u.v.u.a[1] * lhs->u.v.u.a[1] - rhs->u.v.u.a[2] * lhs->u.v.u.a[2];

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Quaternion_scale(
    struct kaphein_geom3d_Quaternion * quatOut
    , const struct kaphein_geom3d_Quaternion * quatIn
    , float s
)
{
    return kaphein_geom3d_Vector4_scale(
        &quatIn->u.v,
        s,
        &quatOut->u.v
    );
}

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_lerp(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Quaternion * from
//     , const struct kaphein_geom3d_Quaternion * to
//     , float ratio
// );

// enum kaphein_ErrorCode
// kaphein_geom3d_Quaternion_slerp(
//     struct kaphein_geom3d_Quaternion * quatOut
//     , const struct kaphein_geom3d_Quaternion * from
//     , const struct kaphein_geom3d_Quaternion * to
//     , float ratio
// );
