#include "kaphein/ErrorCode.h"
#include "kaphein/geom3d/Vector3_internal.h"
#include "kaphein/geom3d/Aabb.h"

#define KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT 8

int kapheinGeom3dAabbFromBounds(
    struct kapheinGeom3dAabb *aabbOut
    , const struct kapheinGeom3dVector3 *min
    , const struct kapheinGeom3dVector3 *max
)
{
    kapheinGeom3dVector3ZzzSubtract(aabbOut->extent.u.a, max->u.a, min->u.a);
    kapheinGeom3dVector3ZzzScale(aabbOut->extent.u.a, aabbOut->extent.u.a, 0.5f);

    kapheinGeom3dVector3ZzzAdd(aabbOut->center.u.a, min->u.a, aabbOut->extent.u.a);

    return 0;
}

int kapheinGeom3dAabbGetPoints(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *pointsOut
    , int *pointCountInOut
)
{
    struct kapheinGeom3dVector3 minPoint;
    struct kapheinGeom3dVector3 maxPoint;
    int minCount;
    int i;
    
    if(pointsOut == NULL) {
        *pointCountInOut = KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
    }
    else {
        kapheinGeom3dAabbGetMinimumPoint(aabb, &minPoint);
        kapheinGeom3dAabbGetMaximumPoint(aabb, &maxPoint);
        minCount = (*pointCountInOut < KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT ? *pointCountInOut : KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT);
        for(i = 0; i < minCount; ++i) {
            switch(i) {
            case 0:
                kapheinGeom3dVector3ZzzCopyTo(minPoint.u.a, pointsOut->u.a);
                pointsOut++;
            break;
            case 1:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, minPoint.u.a[0], minPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 2:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, minPoint.u.a[0], maxPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 3:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, minPoint.u.a[0], maxPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 4:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, maxPoint.u.a[0], minPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 5:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, maxPoint.u.a[0], minPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 6:
                kapheinGeom3dVector3ZzzSetXyz(pointsOut->u.a, maxPoint.u.a[0], maxPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 7:
                kapheinGeom3dVector3ZzzCopyTo(maxPoint.u.a, pointsOut->u.a);
                pointsOut++;
            break;
            }
        }
    }

    return kapheinErrorCodeNoError;
}

int kapheinGeom3dAabbGetMinimumPoint(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *minOut
)
{
    kapheinGeom3dVector3ZzzSubtract(minOut->u.a, aabb->center.u.a, aabb->extent.u.a);

    return 0;
}

int kapheinGeom3dAabbGetMaximumPoint(
    const struct kapheinGeom3dAabb *aabb
    , struct kapheinGeom3dVector3 *maxOut
)
{
    kapheinGeom3dVector3ZzzAdd(maxOut->u.a, aabb->center.u.a, aabb->extent.u.a);;

    return 0;
}

int kapheinGeom3dAabbGetSupportingPoint(
    const void *aabb
    , const struct kapheinGeom3dVector3 *direction
    ,  struct kapheinGeom3dVector3 *pointOut
)
{
    struct kapheinGeom3dVector3 points[KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT];
    float max, dot;
    int i, index;
    int pointCount;

    pointCount = KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
    kapheinGeom3dAabbGetPoints((const struct kapheinGeom3dAabb *)aabb, points, &pointCount);

    for(
        max = -3.402823466e+38f, index = -1, i = 0;
        i < KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
        ++i
    ) {
        dot = kapheinGeom3dVector3ZzzDot(points[i].u.a, direction->u.a);
        if(dot > max) {
            max = dot;
            index = i;
        }
    }

    kapheinGeom3dVector3ZzzCopyTo(points[index].u.a, pointOut->u.a);

    return 0;
}
