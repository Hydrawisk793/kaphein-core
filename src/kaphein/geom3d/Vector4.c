#include "kaphein/math/scalar.h"
#include "kaphein/geom3d/Vector4.h"

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_setZero(
    struct kaphein_geom3d_Vector4 * thisObj
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObj->u.a[0] = 0.0f;
        thisObj->u.a[1] = 0.0f;
        thisObj->u.a[2] = 0.0f;
        thisObj->u.a[3] = 0.0f;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_fill(
    struct kaphein_geom3d_Vector4 * thisObj
    , float value
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        thisObj->u.a[0] = value;
        thisObj->u.a[1] = value;
        thisObj->u.a[2] = value;
        thisObj->u.a[3] = value;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_negate(
    const struct kaphein_geom3d_Vector4 * thisObj
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultOut->u.a[0] = -thisObj->u.a[0];
        resultOut->u.a[1] = -thisObj->u.a[1];
        resultOut->u.a[2] = -thisObj->u.a[2];
        resultOut->u.a[3] = -thisObj->u.a[3];
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_add(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || other == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultOut->u.a[0] = thisObj->u.a[0] + other->u.a[0];
        resultOut->u.a[1] = thisObj->u.a[1] + other->u.a[1];
        resultOut->u.a[2] = thisObj->u.a[2] + other->u.a[2];
        resultOut->u.a[3] = thisObj->u.a[3] + other->u.a[3];
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_subtract(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || other == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultOut->u.a[0] = thisObj->u.a[0] - other->u.a[0];
        resultOut->u.a[1] = thisObj->u.a[1] - other->u.a[1];
        resultOut->u.a[2] = thisObj->u.a[2] - other->u.a[2];
        resultOut->u.a[3] = thisObj->u.a[3] - other->u.a[3];
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_scale(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float scalar
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultOut->u.a[0] = thisObj->u.a[0] * scalar;
        resultOut->u.a[1] = thisObj->u.a[1] * scalar;
        resultOut->u.a[2] = thisObj->u.a[2] * scalar;
        resultOut->u.a[3] = thisObj->u.a[3] * scalar;
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_dot(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , float * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const float * lhs = thisObj->u.a;
    const float * rhs = other->u.a;
    float sum = 0.0f;

    if(thisObj == KAPHEIN_NULL || other == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        sum += *lhs++ * *rhs++;
        sum += *lhs++ * *rhs++;
        sum += *lhs++ * *rhs++;
        sum += *lhs++ * *rhs++;

        *resultOut = sum;
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_norm2Sq(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float * resultOut
)
{
    return kaphein_geom3d_Vector4_dot(thisObj, thisObj, resultOut);
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_norm2(
    const struct kaphein_geom3d_Vector4 * thisObj
    , float * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float norm2Sq = 0.0f;

    resultErrorCode = kaphein_geom3d_Vector4_norm2Sq(thisObj, &norm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        *resultOut = kaphein_math_sqrtF32(norm2Sq);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_normalize(
    const struct kaphein_geom3d_Vector4 * thisObj
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float norm2Sq = 0.0f;
    
    resultErrorCode = kaphein_geom3d_Vector4_norm2Sq(thisObj, &norm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        if(kaphein_math_almostEqualF32(norm2Sq, 0.0f)) {
            resultErrorCode = kaphein_geom3d_Vector4_setZero(resultOut);
        }
        else {
            resultErrorCode = kaphein_geom3d_Vector4_scale(thisObj, 1.0f / kaphein_math_sqrtF32(norm2Sq), resultOut);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_project(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * axis
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float axisNorm2Sq;
    float vInDotAxis;
    
    resultErrorCode = kaphein_geom3d_Vector4_norm2Sq(axis, &axisNorm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        if(kaphein_math_almostEqualF32(axisNorm2Sq, 0.0f)) {
            kaphein_geom3d_Vector4_setZero(resultOut);
        }
        else {
            kaphein_geom3d_Vector4_dot(thisObj, axis, &vInDotAxis);
            kaphein_geom3d_Vector4_scale(axis, vInDotAxis / axisNorm2Sq, resultOut);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_projectOnPlane(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * normal
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;

    resultErrorCode = kaphein_geom3d_Vector4_project(thisObj, normal, resultOut);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        kaphein_geom3d_Vector4_subtract(thisObj, resultOut, resultOut);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_reflect(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * normal
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float inDotNormal;

    resultErrorCode = kaphein_geom3d_Vector4_dot(thisObj, normal, &inDotNormal);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        kaphein_geom3d_Vector4_scale(normal, 2.0f * inDotNormal, resultOut);
        kaphein_geom3d_Vector4_subtract(thisObj, resultOut, resultOut);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_geom3d_Vector4_lerp(
    const struct kaphein_geom3d_Vector4 * thisObj
    , const struct kaphein_geom3d_Vector4 * other
    , float ratio
    , struct kaphein_geom3d_Vector4 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;
    const float * from = thisObj->u.a;
    const float * to = other->u.a;
    float * vOut = resultOut->u.a;
    const float alpha = 1.0f - ratio;

    if(thisObj == KAPHEIN_NULL || other == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        *vOut++ = alpha * *from++ + ratio * *to++;
        *vOut++ = alpha * *from++ + ratio * *to++;
        *vOut++ = alpha * *from++ + ratio * *to++;
        *vOut++ = alpha * *from++ + ratio * *to++;
    }

    return resultErrorCode;
}
