#include "kaphein/math/def.h"

#if KAPHEIN_MATH_PROCESSOR_TYPE == 1
    #include <xmmintrin.h>
#endif

#include "kaphein/math/matrix.h"

enum kaphein_ErrorCode
kaphein_math_addMF32(
    float * mOut
    , const float * lhs
    , const float * rhs
    , int n
)
{
#if KAPHEIN_MATH_PROCESSOR_TYPE == 0

    int i;

    for(i = n; i > 0; ) {
        --i;

        *mOut++ = *lhs++ + *rhs++;
    }
    
    return kapheinErrorCodeNoError;

#elif KAPHEIN_MATH_PROCESSOR_TYPE == 1

    __m128 lhsAligned, rhsAligned, outAligned;
    float temp[4];
    float * curTemp;
    int i, r;

    for(i = n >> 2, r = n - (i << 2); i > 0; ) {
        --i;

        lhsAligned = _mm_load_ps(lhs);
        rhsAligned = _mm_load_ps(rhs);
        outAligned = _mm_add_ps(lhsAligned, rhsAligned);

        _mm_store_ps(mOut, outAligned);
        
        mOut += 4;
        rhs += 4;
        lhs += 4;
    }

    if(r > 0) {
        lhsAligned = _mm_load_ps(lhs);
        rhsAligned = _mm_load_ps(rhs);
        outAligned = _mm_add_ps(lhsAligned, rhsAligned);

        _mm_store_ps(temp, outAligned);

        for(curTemp = temp; r > 0; ) {
            --r;

            *mOut++ = *curTemp++;
        }
    }

    return kapheinErrorCodeNoError;

#endif
}
