#ifndef KAPHEIN_GEOM3D_Matrix4x4_H
#define KAPHEIN_GEOM3D_Matrix4x4_H

#include "kaphein/geom3d/Vector4.h"

struct kapheinGeom3dMatrix4x4
{
    union {
        float a[16];

        struct kapheinGeom3dVector4 rows[4];

        struct {
            float v00;

            float v01;

            float v02;

            float v03;

            float v10;

            float v11;

            float v12;

            float v13;

            float v20;

            float v21;

            float v22;

            float v23;
            
            float v30;

            float v31;

            float v32;

            float v33;
        } v;
    } u;
};

static const struct kapheinGeom3dMatrix4x4 kapheinGeom3dMatrix4x4Zero = {{{
    0.0f, 0.0f, 0.0f, 0.0f
    , 0.0f, 0.0f, 0.0f, 0.0f
    , 0.0f, 0.0f, 0.0f, 0.0f
    , 0.0f, 0.0f, 0.0f, 0.0f
}}};

static const struct kapheinGeom3dMatrix4x4 kapheinGeom3dMatrix4x4Identity = {{{
    1.0f, 0.0f, 0.0f, 0.0f
    , 0.0f, 1.0f, 0.0f, 0.0f
    , 0.0f, 0.0f, 1.0f, 0.0f
    , 0.0f, 0.0f, 0.0f, 1.0f
}}};

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kapheinGeom3dMatrix4x4CopyTo(
    const struct kapheinGeom3dMatrix4x4* src
    , struct kapheinGeom3dMatrix4x4* dest
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kapheinGeom3dMatrix4x4SetZero(
    struct kapheinGeom3dMatrix4x4* mat
);

KAPHEIN_ATTRIBUTE_C_LINKAGE
KAPHEIN_ATTRIBUTE_DLL_API
int kapheinGeom3dMatrix4x4SetIdentity(
    struct kapheinGeom3dMatrix4x4* mat
);

#endif
