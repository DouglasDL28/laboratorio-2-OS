#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid1;

    pid1 = fork();
    if (pid1==0)
    {
        /* HIJO */
        printf("CHILD PROCESS\n");
        int i;
        for (i = 0; i < 4000000; i++)
        {
            printf("%d\n", i);
        }
        
    }
    else
    {
        /* PADRE */
        while (1)
        {
            /* inf loop */
        }
        
    }

    return 0;
}

