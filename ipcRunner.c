#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int p1;
    int p2;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    /* CHILD PROCESS */
    else if (pid == 0) {
        usleep(10000);
        p1 = execlp("./ipc", "ipc", "128", "A", (char *)NULL);
        if (p1 < 0) {
            perror("excelp");
            exit(1);
        }
    }
    /* PARENT PROCESS */
    else {
        p2 = execlp("./ipc", "ipc", "128", "B", (char *)NULL);
        if (p2 < 0) {
            perror("excelp");
            exit(1);
        }
        wait(NULL);
    }

    return 0;
}