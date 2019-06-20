#include "kaphein/math/scalar.h"
#include "kaphein/math/vector.h"
#include "kaphein/math/quaternion.h"

enum kaphein_ErrorCode
kaphein_math_zeroQF32(
    float * qOut
)
{
    *qOut++ = 0.0f;
    *qOut++ = 0.0f;
    *qOut++ = 0.0f;
    *qOut++ = 0.0f;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_identityQF32(
    float * qOut
)
{
    *qOut++ = 0.0f;
    *qOut++ = 0.0f;
    *qOut++ = 0.0f;
    *qOut++ = 1.0f;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_axisAngleQF32(
    float * qOut
    , const float * axis
    , float radian
)
{
    const float angle = 0.5f * radian;

    kaphein_math_normalizeV3F32(qOut, axis);
    kaphein_math_scaleV3F32(qOut, qOut, kaphein_math_sinF32(angle));
    qOut[3] = kaphein_math_cosF32(angle);

    /*
        const E angle = radian * (One<E>() / (One<E>() * 2));

        return Versor<E>(
            Cos<E>()(angle),
            axis.normalized() * Sin<E>()(angle)
        );
    */

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_eulerAnglesQF32(
    float * qOut
    , float xRadian
    , float yRadian
    , float zRadian
)
{
    static const float axisX[] = {1.0f, 0.0f, 0.0f};
    static const float axisY[] = {0.0f, 1.0f, 0.0f};
    static const float axisZ[] = {0.0f, 0.0f, 1.0f};
    float temp[4];

    kaphein_math_axisAngleQF32(qOut, axisX, xRadian);
    kaphein_math_axisAngleQF32(temp, axisY, yRadian);
    kaphein_math_multiplyQF32(qOut, qOut, temp);
    kaphein_math_axisAngleQF32(temp, axisZ, zRadian);
    kaphein_math_multiplyQF32(qOut, qOut, temp);

    /*
        return Versor<E>::axisAngle({1, 0, 0}, xRadian)
        * Versor<E>::axisAngle({0, 1, 0}, yRadian)
        * Versor<E>::axisAngle({0, 0, 1}, zRadian);
    */

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_fromToRotationQF32(
    float * qOut
    , const float * from
    , const float * to
)
{
    static const float axisX[] = {1.0f, 0.0f, 0.0f};
    static const float axisY[] = {0.0f, 1.0f, 0.0f};
    static const float axisZ[] = {0.0f, 0.0f, 1.0f};
    float fromNorm2Sq, toNorm2Sq;
    float magMul;
    float dot;
    
    kaphein_math_norm2SqV3F32(&fromNorm2Sq, from);
    kaphein_math_norm2SqV3F32(&toNorm2Sq, to);
    magMul = kaphein_math_sqrtF32(fromNorm2Sq * toNorm2Sq);

    kaphein_math_dotV3F32(&dot, from, to);

    //Tests if the angle is 180 degree.
    if(kaphein_math_almostEqualF32(dot, -magMul)) {
        //Selects the axis that has the biggest included angle.
        const float absX = kaphein_math_absF32(from[0]);
        const float absY = kaphein_math_absF32(from[1]);
        const float absZ = kaphein_math_absF32(from[2]);
        const float * const newTo = (
            absX < absY
            ? (absX < absZ ? axisX : axisZ)
            : (absY < absZ ? axisY : axisZ)
        );

        kaphein_math_crossV3F32(qOut, from, newTo);
        kaphein_math_normalizeV3F32(qOut, qOut);
        qOut[3] = 0.0f;
    }
    else {
        float fromDotTo;

        kaphein_math_crossV3F32(qOut, from, to);
        kaphein_math_dotV3F32(&fromDotTo, from, to);
        qOut[3] = magMul + fromDotTo;
    }

    /*
    const E magMul = Sqrt<E>()(from.squaredMagnitude() * to.squaredMagnitude());
    const E dot = from.dot(to);

    //Test if the angle is 180 degree.
    if(Equal<E>()(dot, -magMul, epsilon)) {
        //Select the axis that has the biggest included angle.
        const E absX = Abs<E>()(from[0]);
        const E absY = Abs<E>()(from[1]);
        const E absZ = Abs<E>()(from[2]);
        const ImaginaryType newTo = (
            absX < absY
            ? (absX < absZ ? ImaginaryType::bases[0] : ImaginaryType::bases[2])
            : (absY < absZ ? ImaginaryType::bases[1] : ImaginaryType::bases[2])
        );

        return Versor<E>(
            Zero<E>()
            , from.cross(newTo).normalized()
        );
    }

    return Versor<E>(
        magMul + from.dot(to)
        , from.cross(to)
    ).normalize();
    */

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_lookRotationQF32(
    float * qOut
    , const float * lookAtDirection
    , const float * upDirection
)
{
    KAPHEIN_x_UNUSED_PARAMETER(qOut)
    KAPHEIN_x_UNUSED_PARAMETER(lookAtDirection)
    KAPHEIN_x_UNUSED_PARAMETER(upDirection)
    
    //TODO : 코드 이해하기
    /*
        const ImaginaryType axisZ = lookAtDirection.normalized();
        const ImaginaryType axisX = upDirection.cross(axisZ).normalized();
        const ImaginaryType axisY = axisZ.cross(axisX);
        const VectorN< ImaginaryType, 3 > matrix = {
            {axisX[0], axisY[0], axisZ[0]}, 
            {axisX[1], axisY[1], axisZ[1]}, 
            {axisX[2], axisY[2], axisZ[2]}
        };

        float trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
        if(trace > 0) {
            float s = (E)0.5 / Sqrt<float>()(trace + One<float>());

            return Versor<E>(
                (matrix[2][1] - matrix[1][2]) * s,
                (matrix[0][2] - matrix[2][0]) * s,
                (matrix[1][0] - matrix[0][1]) * s,
                (E)0.25 / s
            );
        }
        else if(matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2]) {
            float s = (E)2.0 * Sqrt<float>()(One<float>() + matrix[0][0] - matrix[1][1] - matrix[2][2]);
            float invS = One<float>() / s;

            return Versor<E>(
                (E)0.25 * s,
                (matrix[0][1] + matrix[1][0]) * invS,
                (matrix[0][2] + matrix[2][0]) * invS,
                (matrix[2][1] - matrix[1][2]) * invS
            );
        }
        else if(matrix[1][1] > matrix[2][2]) {
            float s = (E)2.0 * Sqrt<float>()(One<float>() + matrix[1][1] - matrix[0][0] - matrix[2][2]);
            float invS = One<float>() / s;

            return Versor<E>(
                (matrix[0][1] + matrix[1][0]) * invS,
                (E)0.25 * s,
                (matrix[1][2] + matrix[2][1]) * invS,
                (matrix[0][2] - matrix[2][0]) * invS
            );
        }
        else {
            float s = (E)2.0 * Sqrt<float>()(One<float>() + matrix[2][2] - matrix[0][0] - matrix[1][1]);
            float invS = One<float>() / s;

            return Versor<E>(
                (matrix[0][2] + matrix[2][0]) * invS,
                (matrix[1][2] + matrix[2][1]) * invS,
                (E)0.25 * s,
                (matrix[1][0] - matrix[0][1]) * invS
            );
        }
    */

    return kapheinErrorCodeNotImplemented;
}

enum kaphein_ErrorCode
kaphein_math_isConjugateOfQF32(
    bool * truthOut
    , const float * lhs
    , const float * rhs
)
{
    *truthOut = kaphein_math_almostEqualF32(lhs[0], -rhs[0])
        && kaphein_math_almostEqualF32(lhs[1], -rhs[1])
        && kaphein_math_almostEqualF32(lhs[2], -rhs[2])
        && kaphein_math_almostEqualF32(lhs[3], rhs[3])
    ;

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_isInverseOfQF32(
    bool * truthOut
    , const float * lhs
    , const float * rhs
)
{
    KAPHEIN_x_UNUSED_PARAMETER(truthOut)
    KAPHEIN_x_UNUSED_PARAMETER(lhs)
    KAPHEIN_x_UNUSED_PARAMETER(rhs)
    
    *truthOut = false;
    
    return kapheinErrorCodeNotImplemented;
    
    /*
        return inverted().equals(rhs);
    */
}

enum kaphein_ErrorCode
kaphein_math_conjugateQF32(
    float * qOut
    , const float * qIn
)
{
    kaphein_math_negateV3F32(qOut, qIn);
    qOut[3] = qIn[3];

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_invertQF32(
    float * qOut
    , const float * qIn
)
{
    float norm2Sq;

    kaphein_math_norm2SqV4F32(&norm2Sq, qIn);

    if(!kaphein_math_almostEqualF32(norm2Sq, 0.0f)) {
        kaphein_math_conjugateQF32(qOut, qIn);
        kaphein_math_scaleV4F32(qOut, qOut, 1.0f / kaphein_math_signF32(norm2Sq));
    }
    else {
        kaphein_math_zeroQF32(qOut);
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_multiplyQF32(
    float * qOut
    , const float * lhs
    , const float * rhs
)
{
    *qOut++ = rhs[0] * lhs[3] + rhs[3] * lhs[0] - rhs[2] * lhs[1] + rhs[1] * lhs[2];
    *qOut++ = rhs[1] * lhs[3] + rhs[2] * lhs[0] + rhs[3] * lhs[1] - rhs[0] * lhs[2];
    *qOut++ = rhs[2] * lhs[3] - rhs[1] * lhs[0] + rhs[0] * lhs[1] + rhs[3] * lhs[2];
    *qOut++ = rhs[3] * lhs[3] - rhs[0] * lhs[0] - rhs[1] * lhs[1] - rhs[2] * lhs[2];
    
    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_math_slerpQF32(
    float * qOut
    , const float * from
    , const float * to
    , float ratio
)
{
    KAPHEIN_x_UNUSED_PARAMETER(qOut)
    KAPHEIN_x_UNUSED_PARAMETER(from)
    KAPHEIN_x_UNUSED_PARAMETER(to)
    KAPHEIN_x_UNUSED_PARAMETER(ratio)

    /*
    const Versor<E> & lhs = *this;
    E dot = lhs.dot(rhs);
    Versor<E> lhsReversed(lhs);

    //최장 호를 따라 반대 방향으로 보간되는 문제 방지
    if(dot < epsilon) {
        lhsReversed = -lhs;
        dot = -dot;     //dot 결과도 부호가 뒤집힌다.
    }

    //두 쿼터니언 사이 각이 너무 작은 경우
    if(Equal<E>()(dot, One<E>(), epsilon)) {
        return rhs;//lerp(lhs, rhs, delta);
    }
    else {
        const E angle = Acos<E>()(dot);
        return (Sin<E>()((One<float>() - delta)*angle) * lhsReversed + Sin<E>()(delta * angle) * rhs) / Sin<E>()(angle);
    }
    */

    return kapheinErrorCodeNotImplemented;
}
