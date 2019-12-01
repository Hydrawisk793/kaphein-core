#ifndef KAPHEIN_HGRD_kaphein_geom3d_Aabb_H
#define KAPHEIN_HGRD_kaphein_geom3d_Aabb_H

#include "../ErrorCode.h"
#include "Vector3.h"

struct kaphein_geom3d_Aabb
{
    struct kaphein_geom3d_Vector3 center;

    struct kaphein_geom3d_Vector3 extent;
};

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_fromBounds(
    struct kaphein_geom3d_Aabb *aabbOut
    , const struct kaphein_geom3d_Vector3 *min
    , const struct kaphein_geom3d_Vector3 *max
);

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getPoints(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *pointsOut
    , int *pointCountInOut
);

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getMinimumPoint(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *minOut
);

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getMaximumPoint(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *maxOut
);

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getSupportingPoint(
    const void *aabb
    , const struct kaphein_geom3d_Vector3 *direction
    ,  struct kaphein_geom3d_Vector3 *pointOut
);

#endif
