#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    clock_t start;
    clock_t end;

    start = clock();

    int i;
    for (i = 0; i < 1000000000; i++) {}
    for (i = 0; i < 1000000000; i++) {}
    for (i = 0; i < 1000000000; i++) {}
    
    end = clock();

    double time = (end - start) / (double) CLOCKS_PER_SEC;
    printf("DELTA TIEMPO: %f\n", time);

    return 0;
}
