#include "kaphein/geom3d/Vector3_internal.h"
#include "kaphein/geom3d/Ray.h"

int kapheinGeom3dRayGetDirection(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *directionOut
)
{
    kapheinGeom3dVector3ZzzSubtract(directionOut->u.a, ray->terminal.u.a, ray->origin.u.a);
    kapheinGeom3dVector3ZzzNormalize(directionOut->u.a, directionOut->u.a);

    return 0;
}

int kapheinGeom3dRayGetCenter(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *pointOut
)
{
    kapheinGeom3dVector3ZzzLerp(pointOut->u.a, ray->origin.u.a, ray->terminal.u.a, 0.5f);

    return 0;
}

int kapheinGeom3dRayGetPoint(
    const struct kapheinGeom3dRay *ray
    , struct kapheinGeom3dVector3 *pointOut
    , float ratio
)
{
    kapheinGeom3dVector3ZzzLerp(pointOut->u.a, ray->origin.u.a, ray->terminal.u.a, ratio);
    
    return 0;
}

//float kapheinGeom3dLineSegmentFindDistanceToPoint(
//    const struct kapheinGeom3dLineSegment *lineSegment
//    , struct kapheinGeom3dVector3 *point
//)
//{
    //const Vector3f relPoint = point - start_;
    //const Vector3f direction = end_ - start_;

    //const float relPointProjLine = relPoint.dot(direction);
    //const float relPointSq = relPoint.dot(relPoint);
    //if(relPointProjLine <= Zero<float>()) {
    //    return relPointSq;
    //}
    //else {
    //    const float dirSq = direction.dot(direction);
    //    if(relPointProjLine >= dirSq) {
    //        return relPointSq - 2.0f * relPointProjLine + dirSq;
    //    }
    //    else {
    //        return relPointSq - (relPointProjLine * relPointProjLine / dirSq);
    //    }
    //}
//
//    return -1.0;
//}
