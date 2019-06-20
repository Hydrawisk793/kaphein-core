#include "kaphein/math/scalar.h"
#include "kaphein/math/Vector3.h"

enum kaphein_ErrorCode
kaphein_math_Vector3_setZero(
    struct kaphein_math_Vector3 * thisObj
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_fill(
    struct kaphein_math_Vector3 * thisObj
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_negate(
    const struct kaphein_math_Vector3 * thisObj
    , struct kaphein_math_Vector3 * resultOut
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_add(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * other
    , struct kaphein_math_Vector3 * resultOut
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_subtract(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * other
    , struct kaphein_math_Vector3 * resultOut
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_scale(
    const struct kaphein_math_Vector3 * thisObj
    , float scalar
    , struct kaphein_math_Vector3 * resultOut
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
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_cross(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * other
    , struct kaphein_math_Vector3 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode = kapheinErrorCodeNoError;

    if(thisObj == KAPHEIN_NULL || other == KAPHEIN_NULL || resultOut == KAPHEIN_NULL) {
        resultErrorCode = kapheinErrorCodeArgumentNull;
    }
    else {
        resultOut->u.a[0] = thisObj->u.a[1] * other->u.a[2] - thisObj->u.a[2] * other->u.a[1];
        resultOut->u.a[1] = thisObj->u.a[2] * other->u.a[0] - thisObj->u.a[0] * other->u.a[2];
        resultOut->u.a[2] = thisObj->u.a[0] * other->u.a[1] - thisObj->u.a[1] * other->u.a[0];
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_dot(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * other
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

        *resultOut = sum;
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_norm2Sq(
    const struct kaphein_math_Vector3 * thisObj
    , float * resultOut
)
{
    return kaphein_math_Vector3_dot(thisObj, thisObj, resultOut);
}

enum kaphein_ErrorCode
kaphein_math_Vector3_norm2(
    const struct kaphein_math_Vector3 * thisObj
    , float * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float norm2Sq = 0.0f;

    resultErrorCode = kaphein_math_Vector3_norm2Sq(thisObj, &norm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        *resultOut = kaphein_math_sqrtF32(norm2Sq);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_normalize(
    const struct kaphein_math_Vector3 * thisObj
    , struct kaphein_math_Vector3 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float norm2Sq = 0.0f;
    
    resultErrorCode = kaphein_math_Vector3_norm2Sq(thisObj, &norm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        if(kaphein_math_almostEqualF32(norm2Sq, 0.0f)) {
            resultErrorCode = kaphein_math_Vector3_setZero(resultOut);
        }
        else {
            resultErrorCode = kaphein_math_Vector3_scale(thisObj, 1.0f / kaphein_math_sqrtF32(norm2Sq), resultOut);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_project(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * axis
    , struct kaphein_math_Vector3 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float axisNorm2Sq;
    float vInDotAxis;
    
    resultErrorCode = kaphein_math_Vector3_norm2Sq(axis, &axisNorm2Sq);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        if(kaphein_math_almostEqualF32(axisNorm2Sq, 0.0f)) {
            kaphein_math_Vector3_setZero(resultOut);
        }
        else {
            kaphein_math_Vector3_dot(thisObj, axis, &vInDotAxis);
            kaphein_math_Vector3_scale(axis, vInDotAxis / axisNorm2Sq, resultOut);
        }
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_projectOnPlane(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * normal
    , struct kaphein_math_Vector3 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;

    resultErrorCode = kaphein_math_Vector3_project(thisObj, normal, resultOut);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        kaphein_math_Vector3_subtract(thisObj, resultOut, resultOut);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_reflect(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * normal
    , struct kaphein_math_Vector3 * resultOut
)
{
    enum kaphein_ErrorCode resultErrorCode;
    float inDotNormal;

    resultErrorCode = kaphein_math_Vector3_dot(thisObj, normal, &inDotNormal);
    if(resultErrorCode == kapheinErrorCodeNoError) {
        kaphein_math_Vector3_scale(normal, 2.0f * inDotNormal, resultOut);
        kaphein_math_Vector3_subtract(thisObj, resultOut, resultOut);
    }

    return resultErrorCode;
}

enum kaphein_ErrorCode
kaphein_math_Vector3_lerp(
    const struct kaphein_math_Vector3 * thisObj
    , const struct kaphein_math_Vector3 * other
    , float ratio
    , struct kaphein_math_Vector3 * resultOut
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
    }

    return resultErrorCode;
}
