#ifndef KAPHEIN_GEOM3D_Capsule_H
#define KAPHEIN_GEOM3D_Capsule_H

#include "Ray.h"

struct kapheinGeom3dCapsule
{
    struct kapheinGeom3dRay axis;

    float radius;
};

int kapheinGeom3dCapsuleGetCenter(
    const struct kapheinGeom3dCapsule *capsule
    , struct kapheinGeom3dVector3 *centerOut
);

int kapheinGeom3dCapsuleGetSupportingPoint(
    const void *capsule
    , const struct kapheinGeom3dVector3 *direction
    ,  struct kapheinGeom3dVector3 *pointOut
);

#endif
