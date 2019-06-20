#ifndef KAPHEIN_GEOM3D_Obb_H
#define KAPHEIN_GEOM3D_Obb_H

#include "Vector3.h"

struct kapheinGeom3dObb
{
    struct kapheinGeom3dVector3 center;

    struct kapheinGeom3dVector3 extent;

    union {
        struct kapheinGeom3dVector3 a[3];
        
        struct {
            struct kapheinGeom3dVector3 x;
            
            struct kapheinGeom3dVector3 y;

            struct kapheinGeom3dVector3 z;
        } v;
    } axis;
};

int kapheinGeom3dObbGetMinimum(
    const struct kapheinGeom3dObb *obb
    , struct kapheinGeom3dVector3 *minOut
);

int kapheinGeom3dObbGetMaximum(
    const struct kapheinGeom3dObb *obb
    , struct kapheinGeom3dVector3 *maxOut
);

int kapheinGeom3dObbGetNormalOfFacePlane(
    const struct kapheinGeom3dObb *obb
    , int faceIndex
    , struct kapheinGeom3dVector3 *normalOut    
);

#endif
