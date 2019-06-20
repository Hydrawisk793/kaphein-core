#include "kaphein/geom3d/Capsule.h"

int kapheinGeom3dCapsuleGetCenter(
    const struct kapheinGeom3dCapsule *capsule
    , struct kapheinGeom3dVector3 *centerOut
)
{
    //axis_.getPoint(0.5f);
    
    return 0;
}

int kapheinGeom3dCapsuleGetSupportingPoint(
    const void *capsule
    , const struct kapheinGeom3dVector3 *direction
    ,  struct kapheinGeom3dVector3 *pointOut
)
{
    //const Vector3f normalizedDirection = direction.normalized();
    //const Vector3f center = getCenter();
    //const float dirDotStart = normalizedDirection.dot(axis_.getStart() - center);
    //const float dirDotEnd = normalizedDirection.dot(axis_.getEnd() - center);

    //return ((dirDotStart >= dirDotEnd) ? axis_.getStart() : axis_.getEnd()) + (normalizedDirection * radius_);

    return 0;
}
