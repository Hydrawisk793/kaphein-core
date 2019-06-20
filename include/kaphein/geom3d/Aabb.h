#ifndef KAPHEIN_GEOM3D_Aabb_H
#define KAPHEIN_GEOM3D_Aabb_H

#include "Vector3.h"

struct kapheinGeom3dAabb
{
    struct kapheinGeom3dVector3 center;

    struct kapheinGeom3dVector3 extent;
};

int kapheinGeom3dAabbFromBounds(
    struct kapheinGeom3dAabb *aabbOut
    , const struct kapheinGeom3dVector3 *min
    , const struct kapheinGeom3dVector3 *max
);

int kapheinGeom3dAabbGetPoints(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *pointsOut
    , int *pointCountInOut
);

int kapheinGeom3dAabbGetMinimumPoint(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *minOut
);

int kapheinGeom3dAabbGetMaximumPoint(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *maxOut
);

int kapheinGeom3dAabbGetSupportingPoint(
    const void *aabb
    , const struct kapheinGeom3dVector3 *direction
    ,  struct kapheinGeom3dVector3 *pointOut
);

#endif
