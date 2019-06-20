#include "kaphein/def.h"
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    #include <math.h>
#endif
#include "kaphein/math/scalar.h"

#define KAPHEIN_MATH_x_EPSILON_F32 1.192092896e-07F

#define KAPHEIN_MATH_x_EPSILON_F64 2.2204460492503131e-016

#define KAPHEIN_MATH_x_PI_F64 3.14159265358979323846

bool kaphein_math_almostEqualF32(
    float lhs
    , float rhs
)
{
    float max = 1.0f;

    if(max < lhs) {
        max = lhs;
    }

    if(max < rhs) {
        max = rhs;
    }

    return kaphein_math_absF32(lhs - rhs) <= KAPHEIN_MATH_x_EPSILON_F32 * max;
}

bool kaphein_math_almostEqualF64(
    double lhs
    , double rhs
)
{
    double max = 1.0;

    if(max < lhs) {
        max = lhs;
    }

    if(max < rhs) {
        max = rhs;
    }

    return kaphein_math_absF64(lhs - rhs) <= KAPHEIN_MATH_x_EPSILON_F64 * max;
}

int kaphein_math_signF32(
    float s
)
{
    return (0.0f < s) - (s < 0.0f);
}

int kaphein_math_signF64(
    double s
)
{
    return (0.0 < s) - (s < 0.0);
}

float kaphein_math_absF32(
    float s
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return fabsf(s);
#else
    s;

    return 0.0f;
#endif
}

double kaphein_math_absF64(
    double s
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return fabs(s);
#else
    s;

    return 0.0;
#endif
}

float kaphein_math_sqrtF32(
    float s
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return sqrtf(s);
#else
    s;

    return 0.0f;
#endif
}

double kaphein_math_sqrtF64(
    double s
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return sqrt(s);
#else
    s;

    return 0.0;
#endif
}

float kaphein_math_radianToDegreeF32(
    float radian
)
{
    return radian * (180.0f / (float)KAPHEIN_MATH_x_PI_F64);
}

double kaphein_math_radianToDegreeF64(
    double radian
)
{
    return radian * (180.0 / KAPHEIN_MATH_x_PI_F64);
}

float kaphein_math_degreeToRadianF32(
    float degree
)
{
    return degree * ((float)KAPHEIN_MATH_x_PI_F64 / 180.0f);
}

double kaphein_math_degreeToRadianF64(
    double degree
)
{
    return degree * (KAPHEIN_MATH_x_PI_F64 / 180.0);
}

float kaphein_math_sinF32(
    float radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return sinf(radian);
#else
    radian;

    return 0.0f;
#endif
}

double kaphein_math_sinF64(
    double radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return sin(radian);
#else
    radian;

    return 0.0;
#endif
}

float kaphein_math_cosF32(
    float radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return cosf(radian);
#else
    radian;

    return 0.0f;
#endif
}

double kaphein_math_cosF64(
    double radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return cos(radian);
#else
    radian;

    return 0.0;
#endif
}

float kaphein_math_tanF32(
    float radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return tanf(radian);
#else
    radian;

    return 0.0f;
#endif
}

double kaphein_math_tanF64(
    double radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    return tan(radian);
#else
    radian;

    return 0.0;
#endif
}

void kaphein_math_sinCosF32(
    float *sinOut
    , float *cosOut
    , float radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    *sinOut = sinf(radian);
    *cosOut = cosf(radian);
#else
    radian;

    *sinOut = 0.0f;
    *cosOut = 0.0f;
#endif
}

void kaphein_math_sinCosF64(
    double *sinOut
    , double *cosOut
    , double radian
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    *sinOut = sin(radian);
    *cosOut = cos(radian);
#else
    radian;

    *sinOut = 0.0;
    *cosOut = 0.0;
#endif
}

float kaphein_math_hypotF32(
    float x
    , float y
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    float temp;
    float t;
    float result;

    x = kaphein_math_absF32(x);
    y = kaphein_math_absF32(y);

    if(y > x) {
        temp = x;
        x = y;
        y = temp;
    }

    if(kaphein_math_almostEqualF32(x, 0.0f)) {
        result = y;
    }
    else {
        t = y / x;
        result = x * kaphein_math_sqrtF32(1.0f + t * t);
    }
    
    return result;
#else
    x;
    y;

    return 0.0f;
#endif
}

double kaphein_math_hypotF64(
    double x
    , double y
)
{
#if !defined(KAPHEIN_x_EMPTY_C_MATH)
    double temp;
    double t;
    double result;

    x = kaphein_math_absF64(x);
    y = kaphein_math_absF64(y);

    if(y > x) {
        temp = x;
        x = y;
        y = temp;
    }

    if(kaphein_math_almostEqualF64(x, 0.0)) {
        result = y;
    }
    else {
        t = y / x;
        result = x * kaphein_math_sqrtF64(1.0 + t * t);
    }
    
    return result;
#else
    x;
    y;

    return 0.0;
#endif
}
