#ifndef KAPHEIN_GEOM3D_RAYCAST_H
#define KAPHEIN_GEOM3D_RAYCAST_H

#include "RaycastHit.h"
#include "Ray.h"
#include "Aabb.h"
#include "Obb.h"
#include "Sphere.h"
#include "Capsule.h"

int kapheinGeom3dRaycastToPlane(
    const kapheinGeom3dRay *ray
    , const kapheinGeom3dVector3 *normal
    , struct kapheinGeom3dRaycastHit *hitOut
);

int kapheinGeom3dRaycastToAabb(
    const kapheinGeom3dRay *ray
    , const kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dRaycastHit *hitsOut
    , int *hitCoutOut
);

int kapheinGeom3dRaycastToObb(
    const kapheinGeom3dRay *ray
    , const kapheinGeom3dObb *obb
    , struct kapheinGeom3dRaycastHit *hitsOut
    , int *hitCoutOut
);

int kapheinGeom3dRaycastToSphere(
    const kapheinGeom3dRay *ray
    , const kapheinGeom3dSphere *sphere
    , struct kapheinGeom3dRaycastHit *hitsOut
    , int *hitCoutOut
);

int kapheinGeom3dRaycastToCapsule(
    const kapheinGeom3dRay *ray
    , const kapheinGeom3dCapsule *capsule
    , struct kapheinGeom3dRaycastHit *hitsOut
    , int *hitCoutOut
);

#endif
