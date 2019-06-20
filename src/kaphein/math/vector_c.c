#include "kaphein/math/scalar.h"
#include "kaphein/math/vector.h"

/* **************************************************************** */
/* V3F32 function definitions */

enum kaphein_ErrorCode
kaphein_math_zeroV3F32(
    float * vInOut
)
{
    *vInOut++ = 0.0f;
    *vInOut++ = 0.0f;
    *vInOut++ = 0.0f;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_fillV3F32(
    float * vInOut
    , float s
)
{
    *vInOut++ = s;
    *vInOut++ = s;
    *vInOut++ = s;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_negateV3F32(
    float * vOut
    , const float * vIn
)
{
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_addV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
)
{
    *vOut++ = *lhs++ + *rhs++;
    *vOut++ = *lhs++ + *rhs++;
    *vOut++ = *lhs++ + *rhs++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_subtractV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
)
{
    *vOut++ = *lhs++ - *rhs++;
    *vOut++ = *lhs++ - *rhs++;
    *vOut++ = *lhs++ - *rhs++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_scaleV3F32(
    float * vOut
    , const float * vIn
    , float s
)
{
    *vOut++ = *vIn++ * s;
    *vOut++ = *vIn++ * s;
    *vOut++ = *vIn++ * s;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_crossV3F32(
    float * vOut
    , const float * lhs
    , const float * rhs
)
{
    *vOut++ = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    *vOut++ = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    *vOut++ = lhs[0] * rhs[1] - lhs[1] * rhs[0];

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_dotV3F32(
    float * sOut
    , const float * lhs
    , const float * rhs
)
{
    float sum = 0.0f;
    
    sum += *lhs++ * *rhs++;
    sum += *lhs++ * *rhs++;
    sum += *lhs++ * *rhs++;

    *sOut = sum;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_norm2SqV3F32(
    float * sOut
    , const float * vIn
)
{
    return kaphein_math_dotV3F32(sOut, vIn, vIn);
}

enum kaphein_ErrorCode
kaphein_math_norm2V3F32(
    float * sOut
    , const float * vIn
)
{
    enum kaphein_ErrorCode errorCode;
    float norm2Sq;

    errorCode = kaphein_math_norm2SqV3F32(&norm2Sq, vIn);
    
    if(errorCode == kapheinErrorCodeNoError) {
        *sOut = kaphein_math_sqrtF32(norm2Sq);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_normalizeV3F32(
    float * vOut
    , const float * vIn
)
{
    enum kaphein_ErrorCode errorCode;
    float norm2Sq = 0.0f;
    
    errorCode = kaphein_math_norm2SqV3F32(&norm2Sq, vIn);

    if(errorCode == kapheinErrorCodeNoError) {
        if(!kaphein_math_almostEqualF32(norm2Sq, 0.0f)) {
            kaphein_math_scaleV3F32(vOut, vIn, 1.0f / kaphein_math_sqrtF32(norm2Sq));
        }
        else {
            kaphein_math_zeroV3F32(vOut);
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_projectV3F32(
    float * vOut
    , const float * vIn
    , const float * axis
)
{
    float axisNorm2Sq;
    float vInDotAxis;
    
    kaphein_math_norm2SqV3F32(&axisNorm2Sq, axis);
    
    if(!kaphein_math_almostEqualF32(axisNorm2Sq, 0.0f)) {
        kaphein_math_dotV3F32(&vInDotAxis, vIn, axis);
        kaphein_math_scaleV3F32(vOut, axis, vInDotAxis / axisNorm2Sq);
    }
    else {
        kaphein_math_zeroV3F32(vOut);
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_projectOnPlaneV3F32(
    float * vOut
    , const float * vIn
    , const float * normal
)
{
    kaphein_math_projectV3F32(vOut, vIn, normal);
    kaphein_math_subtractV3F32(vOut, vIn, vOut);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_reflectV3F32(
    float * vOut
    , const float * vIn
    , const float * normal
)
{
    float inDotNormal;
    
    kaphein_math_dotV3F32(&inDotNormal, vIn, normal);
    kaphein_math_scaleV3F32(vOut, normal, 2.0f * inDotNormal);
    kaphein_math_subtractV3F32(vOut, vIn, vOut);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_lerpV3F32(
    float * vOut
    , const float * from
    , const float * to
    , float ratio
)
{
    const float alpha = 1.0f - ratio;

    *vOut++ = alpha * *from++ + ratio * *to++;
    *vOut++ = alpha * *from++ + ratio * *to++;
    *vOut++ = alpha * *from++ + ratio * *to++;

    return kapheinErrorCodeNoError;
}

/* **************************************************************** */

/* **************************************************************** */
/* V4F32 function definitions */

enum kaphein_ErrorCode
kaphein_math_zeroV4F32(
    float * vInOut
)
{
    *vInOut++ = 0.0f;
    *vInOut++ = 0.0f;
    *vInOut++ = 0.0f;
    *vInOut++ = 0.0f;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_fillV4F32(
    float * vInOut
    , float s
)
{
    *vInOut++ = s;
    *vInOut++ = s;
    *vInOut++ = s;
    *vInOut++ = s;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_negateV4F32(
    float * vOut
    , const float * vIn
)
{
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;
    *vOut++ = -*vIn++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_addV4F32(
    float * vOut
    , const float * lhs
    , const float * rhs
)
{
    *vOut++ = *lhs++ + *rhs++;
    *vOut++ = *lhs++ + *rhs++;
    *vOut++ = *lhs++ + *rhs++;
    *vOut++ = *lhs++ + *rhs++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_subtractV4F32(
    float * vOut
    , const float * lhs
    , const float * rhs
)
{
    *vOut++ = *lhs++ - *rhs++;
    *vOut++ = *lhs++ - *rhs++;
    *vOut++ = *lhs++ - *rhs++;
    *vOut++ = *lhs++ - *rhs++;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_scaleV4F32(
    float * vOut
    , const float * vIn
    , float s
)
{
    *vOut++ = *vIn++ * s;
    *vOut++ = *vIn++ * s;
    *vOut++ = *vIn++ * s;
    *vOut++ = *vIn++ * s;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_dotV4F32(
    float * sOut
    , const float * lhs
    , const float * rhs
)
{
    float sum = 0.0f;
    
    sum += *lhs++ * *rhs++;
    sum += *lhs++ * *rhs++;
    sum += *lhs++ * *rhs++;
    sum += *lhs++ * *rhs++;

    *sOut = sum;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_norm2SqV4F32(
    float * sOut
    , const float * vIn
)
{
    return kaphein_math_dotV4F32(sOut, vIn, vIn);
}

enum kaphein_ErrorCode
kaphein_math_norm2V4F32(
    float * sOut
    , const float * vIn
)
{
    enum kaphein_ErrorCode errorCode;
    float norm2Sq;

    errorCode = kaphein_math_norm2SqV4F32(&norm2Sq, vIn);
    
    if(errorCode == kapheinErrorCodeNoError) {
        *sOut = kaphein_math_sqrtF32(norm2Sq);
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_normalizeV4F32(
    float * vOut
    , const float * vIn
)
{
    enum kaphein_ErrorCode errorCode;
    float norm2Sq = 0.0f;
    
    errorCode = kaphein_math_norm2SqV4F32(&norm2Sq, vIn);

    if(errorCode == kapheinErrorCodeNoError) {
        if(!kaphein_math_almostEqualF32(norm2Sq, 0.0f)) {
            kaphein_math_scaleV4F32(vOut, vIn, 1.0f / kaphein_math_sqrtF32(norm2Sq));
        }
        else {
            kaphein_math_zeroV4F32(vOut);
        }
    }

    return errorCode;
}

enum kaphein_ErrorCode
kaphein_math_projectV4F32(
    float * vOut
    , const float * vIn
    , const float * axis
)
{
    float axisNorm2Sq;
    float vInDotAxis;
    
    kaphein_math_norm2SqV4F32(&axisNorm2Sq, axis);
    
    if(!kaphein_math_almostEqualF32(axisNorm2Sq, 0.0f)) {
        kaphein_math_dotV4F32(&vInDotAxis, vIn, axis);
        kaphein_math_scaleV4F32(vOut, axis, vInDotAxis / axisNorm2Sq);
    }
    else {
        kaphein_math_zeroV4F32(vOut);
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_projectOnPlaneV4F32(
    float * vOut
    , const float * vIn
    , const float * normal
)
{
    kaphein_math_projectV4F32(vOut, vIn, normal);
    kaphein_math_subtractV4F32(vOut, vIn, vOut);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_reflectV4F32(
    float * vOut
    , const float * vIn
    , const float * normal
)
{
    float inDotNormal;
    
    kaphein_math_dotV4F32(&inDotNormal, vIn, normal);
    kaphein_math_scaleV4F32(vOut, normal, 2.0f * inDotNormal);
    kaphein_math_subtractV4F32(vOut, vIn, vOut);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_lerpV4F32(
    float * vOut
    , const float * from
    , const float * to
    , float ratio
)
{
    const float alpha = 1.0f - ratio;

    *vOut++ = alpha * *from++ + ratio * *to++;
    *vOut++ = alpha * *from++ + ratio * *to++;
    *vOut++ = alpha * *from++ + ratio * *to++;
    *vOut++ = alpha * *from++ + ratio * *to++;

    return kapheinErrorCodeNoError;
}

/* **************************************************************** */
