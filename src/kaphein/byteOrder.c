#include "kaphein/byteOrder.h"

enum kapheinByteOrder kapheinGetByteOrder()
{
    static const int v = 1;

    return (enum kapheinByteOrder)(!((((const uint8_t *)(const void *)&v)[0]) == 0));
}
