#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    fork();
    fork();
    fork();
    fork();
    printf("%d\n", (int)getpid());
    return 0;
}