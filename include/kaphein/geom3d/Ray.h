#ifndef KAPHEIN_GEOM3D_Ray_H
#define KAPHEIN_GEOM3D_Ray_H

#include "Vector3.h"

struct kapheinGeom3dRay
{
    struct kapheinGeom3dVector3 origin;

    struct kapheinGeom3dVector3 terminal;
};

int kapheinGeom3dRayGetDirection(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *directionOut
);

int kapheinGeom3dRayGetCenter(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *pointOut
);

int kapheinGeom3dRayGetPoint(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *pointOut
    , float ratio
);

#endif
