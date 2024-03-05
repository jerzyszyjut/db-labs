#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include "opt_invsqrt.h"
#include "invsqrt.h"

int main()
{
    float number = 4.0f; // sqrt(number) = 0.5

    printf("simple_rsqrt(%f) = %f\n", number, simple_rsqrt(number));
    printf("opt_simple_rsqrt(%f) = %f\n", number, opt_simple_rsqrt(number));
    printf("q_rsqrt(%f) = %f\n", number, quick_rsqrt(number));

    int simple_rsqrt_time = 0, opt_simple_rsqrt_time = 0, quick_rsqrt_time = 0;
    clock_t start, end;

    start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        simple_rsqrt(number);
    }
    end = clock();
    simple_rsqrt_time = (end - start);


    start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        opt_simple_rsqrt(number);
    }
    end = clock();
    opt_simple_rsqrt_time = (end - start);

    start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        quick_rsqrt(number);
    }
    end = clock();
    quick_rsqrt_time = (end - start);

    printf("simple_rsqrt time: %d\n", simple_rsqrt_time);
    printf("opt_simple_rsqrt time: %d\n", opt_simple_rsqrt_time);
    printf("quick_rsqrt time: %d\n", quick_rsqrt_time);

    return 0;
}