#include "kaphein/mem/utils.h"
#include "kaphein/geom3d/Matrix4x4.h"

int kapheinGeom3dMatrix4x4CopyTo(
    const struct kapheinGeom3dMatrix4x4* src
    , struct kapheinGeom3dMatrix4x4* dest
)
{
    
    
    kapheinMemCopy(dest, sizeof(*dest), src, sizeof(*dest));

    return 0;
}

int kapheinGeom3dMatrix4x4SetZero(
    struct kapheinGeom3dMatrix4x4* mat
)
{
    
    
    kapheinMemFill(mat, sizeof(*mat), 0, sizeof(*mat));

    return 0;
}

int kapheinGeom3dMatrix4x4SetIdentity(
    struct kapheinGeom3dMatrix4x4* mat
)
{
    
    
    kapheinMemFill(mat, sizeof(*mat), 0, sizeof(*mat));

    mat->u.a[0] = 1.0f;
    mat->u.a[5] = 1.0f;
    mat->u.a[10] = 1.0f;
    mat->u.a[15] = 1.0f;

    return 0;
}
