#include <stdlib.h>
#include <stdio.h>

int rand(int min, int max)
{
    if (max <= min)
        return min;

    return min + rand() % (max - min);
}