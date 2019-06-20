#include <stdio.h>
#include <stdlib.h>

#include <kaphein/coll/sort.h>

int compareInt(
    const void * lhs
    , const void * rhs
)
{
    return *((int *)lhs) - *((int *)rhs);
}

void swapInt(
    void * lhs
    , void * rhs
)
{
    int temp = *((int *)lhs);
    *((int *)lhs) = *((int *)rhs);
    *((int *)rhs) = temp;
}

void printIntArray(
    const int * elements
    , kaphein_SSize count
)
{
    for(; count > 0; ++elements, --count) {
        printf("%d ", *elements);
    }
}

int main(void)
{
    static const struct kaphein_coll_ElementTrait elementTrait = {
        KAPHEIN_NULL
        , KAPHEIN_NULL
        , swapInt
        , compareInt
        , sizeof(int)
    };
    int foo[] = {6, 5, 3, 1, 8, 7, 2, 4};
    
    printIntArray(foo, (kaphein_SSize)(sizeof(foo) / sizeof(*foo)));
    puts("");

    kaphein_coll_sortByBubble(
        &elementTrait
        , foo
        , (kaphein_SSize)(sizeof(foo) / sizeof(*foo))
    );

    printIntArray(foo, (kaphein_SSize)(sizeof(foo) / sizeof(*foo)));
    puts("");

    system("pause");

    return 0;
}
