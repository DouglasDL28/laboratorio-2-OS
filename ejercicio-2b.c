#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    clock_t start;
    clock_t end;

    start = clock();
    printf("%f\n", (double) start);

    pid1 = fork();
    if (pid1==0)
    {
        pid2 = fork();
        if (pid2==0)
        {
            pid3 = fork();
            if (pid3==0)
            {
                /* BISNIETO */
                int i;
                for (i = 0; i < 1000000000; i++) {}
            }
            else
            {
                /* NIETO */
                int i;
                for (i = 0; i < 1000000000; i++) {}
                wait(NULL);
            }   
        }
        else
        {
            /* HIJO */
            int i;
            for (i = 0; i < 1000000000; i++) {}
            wait(NULL);
        } 
    }
    else
    {
        /* PADRE */
        wait(NULL);
    }

    end = clock();
    double time = (end - start) / (double) CLOCKS_PER_SEC;
    printf("DELTA TIEMPO: %f\n", time);



    return 0;
}

