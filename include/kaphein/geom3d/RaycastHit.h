#ifndef KAPHEIN_GEOM3D_RaycastHit_H
#define KAPHEIN_GEOM3D_RaycastHit_H

#include "Vector3.h"

struct kapheinGeom3dRaycastHit
{
    struct kapheinGeom3dVector3 position;

    float squaredDistance;

    float rayParameter;
};

#endif
