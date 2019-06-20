#ifndef KAPHEIN_GEOM3D_DEF_H
#define KAPHEIN_GEOM3D_DEF_H

#include "../def.h"

#define KAPHEIN_GEOM3D_EPSILON_F32 1.192092896e-07F

#define KAPHEIN_GEOM3D_EPSILON_F64 2.2204460492503131e-016

#define KAPHEIN_GEOM3D_PI_F64 3.14159265358979323846

#if !defined(KAPHEIN_GEOM3D_UNSAFE_MODE) || KAPHEIN_GEOM3D_UNSAFE_MODE == 0
    #define KAPHEIN_GEOM3D_x_PARAM_TEST_IF_BEGIN(expr) if(expr) {
    #define KAPHEIN_GEOM3D_x_PARAM_TEST_IF_END() }
#else
    #define KAPHEIN_GEOM3D_x_PARAM_TEST_IF_BEGIN(expr)
    #define KAPHEIN_GEOM3D_x_PARAM_TEST_IF_END()
#endif

#endif