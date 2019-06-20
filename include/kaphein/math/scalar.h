#ifndef KAPHEIN_HGRD_kaphein_math_scalar_h
#define KAPHEIN_HGRD_kaphein_math_scalar_h

#include "../def.h"

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool kaphein_math_almostEqualF32(
    float lhs
    , float rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
bool kaphein_math_almostEqualF64(
    double lhs
    , double rhs
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_math_signF32(
    float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kaphein_math_signF64(
    double s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_absF32(
    float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_absF64(
    double s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_sqrtF32(
    float s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_sqrtF64(
    double s
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_radianToDegreeF32(
    float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_radianToDegreeF64(
    double radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_degreeToRadianF32(
    float degree
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_degreeToRadianF64(
    double degree
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_sinF32(
    float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_sinF64(
    double radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_cosF32(
    float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_cosF64(
    double radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_tanF32(
    float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_tanF64(
    double radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void kaphein_math_sinCosF32(
    float *sinOut
    , float *cosOut
    , float radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
void kaphein_math_sinCosF64(
    double *sinOut
    , double *cosOut
    , double radian
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
float kaphein_math_hypotF32(
    float x
    , float y
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
double kaphein_math_hypotF64(
    double x
    , double y
);

#endif
