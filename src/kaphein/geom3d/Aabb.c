#include "kaphein/ErrorCode.h"
#include "kaphein/geom3d/Aabb.h"

#define KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT 8

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_fromBounds(
    struct kaphein_geom3d_Aabb *aabbOut
    , const struct kaphein_geom3d_Vector3 *min
    , const struct kaphein_geom3d_Vector3 *max
)
{
    kaphein_geom3d_Vector3_subtract(max->u.a, min->u.a, aabbOut->extent.u.a);
    kaphein_geom3d_Vector3_scale(aabbOut->extent.u.a, 0.5f, aabbOut->extent.u.a);
    kaphein_geom3d_Vector3_add(min->u.a, aabbOut->extent.u.a, aabbOut->center.u.a);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getPoints(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *pointsOut
    , int *pointCountInOut
)
{
    struct kaphein_geom3d_Vector3 minPoint;
    struct kaphein_geom3d_Vector3 maxPoint;
    int minCount;
    int i;

    if(pointsOut == NULL) {
        *pointCountInOut = KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
    }
    else {
        kaphein_geom3d_Aabb_getMinimumPoint(aabb, &minPoint);
        kaphein_geom3d_Aabb_getMaximumPoint(aabb, &maxPoint);
        minCount = (*pointCountInOut < KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT ? *pointCountInOut : KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT);
        for(i = 0; i < minCount; ++i) {
            switch(i) {
            case 0:
                kaphein_geom3d_Vector3_copyTo(minPoint.u.a, pointsOut->u.a);
                pointsOut++;
            break;
            case 1:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, minPoint.u.a[0], minPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 2:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, minPoint.u.a[0], maxPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 3:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, minPoint.u.a[0], maxPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 4:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, maxPoint.u.a[0], minPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 5:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, maxPoint.u.a[0], minPoint.u.a[1], maxPoint.u.a[2]);
                pointsOut++;
            break;
            case 6:
                kaphein_geom3d_Vector3_setXyz(pointsOut->u.a, maxPoint.u.a[0], maxPoint.u.a[1], minPoint.u.a[2]);
                pointsOut++;
            break;
            case 7:
                kaphein_geom3d_Vector3_copyTo(maxPoint.u.a, pointsOut->u.a);
                pointsOut++;
            break;
            }
        }
    }

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getMinimumPoint(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *minOut
)
{
    kaphein_geom3d_Vector3_subtract(aabb->center.u.a, aabb->extent.u.a, minOut->u.a);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getMaximumPoint(
    const struct kaphein_geom3d_Aabb *aabb
    , struct kaphein_geom3d_Vector3 *maxOut
)
{
    kaphein_geom3d_Vector3_add(aabb->center.u.a, aabb->extent.u.a, maxOut->u.a);

    return kapheinErrorCodeNoError;
}

enum kaphein_ErrorCode
kaphein_geom3d_Aabb_getSupportingPoint(
    const void *aabb
    , const struct kaphein_geom3d_Vector3 *direction
    ,  struct kaphein_geom3d_Vector3 *pointOut
)
{
    struct kaphein_geom3d_Vector3 points[KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT];
    float max, dot;
    int i, index;
    int pointCount;

    pointCount = KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
    kaphein_geom3d_Aabb_getPoints((const struct kaphein_geom3d_Aabb *)aabb, points, &pointCount);

    for(
        max = -3.402823466e+38f, index = -1, i = 0;
        i < KAPHEIN_GEOM3D_Aabb_x_POINT_COUNT;
        ++i
    ) {
        kaphein_geom3d_Vector3_dot(points[i].u.a, direction->u.a, &dot);
        if(dot > max) {
            max = dot;
            index = i;
        }
    }

    kaphein_geom3d_Vector3_copyTo(points[index].u.a, pointOut->u.a);

    return kapheinErrorCodeNoError;
}
