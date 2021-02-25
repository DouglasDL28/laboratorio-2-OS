#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 32
#define READ_END 0
#define WRITE_END 1

void error_and_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[]) {
    pid_t pid;

    int n;
    char *x;
    int length;

    if (argc < 2) {
        n = 100;
        x = "a";
    }
    else {
        n = atoi(argv[1]);
        x = argv[2];
    }

    printf("I am %s\n", x);

    int r;
    const int SIZE = 128; // size (in bytes) of shm object
    const char *name = "OS"; // name of shm object

    int fd; // shm file descriptor
    char *ptr; // pointer to shm
    
    int pfds[2];
    char buf[BUFF_SIZE];

    /* create shared memory object */
    fd = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (fd == -1) {
        if (errno != EEXIST) {
            error_and_exit("shm_open");
        }
    }
    else {
        /* configure size of shm object */
        r = ftruncate(fd, SIZE);
        if (r == -1) {
            error_and_exit("ftruncate");
        }
    }


    char *cptr; //cptr copy

    /* Map memory */
    ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        error_and_exit("mmap");
    }

    /* second ptr */
    if (fd == -1) {
        if (errno == EEXIST){
            length = sprintf(ptr + (char)ptr[0], "File descriptor: %c\n", (char) fd);
            ptr[0] += length;
        }
    }
    else {
        ptr[0] = 1;
        length = sprintf(ptr + (char)ptr[0], "File descriptor created!\n");
        ptr[0] += length;
    }

    length = sprintf(ptr + (char)ptr[0], "Created PTR: %c\n", (char) *ptr);
    ptr[0] += length;
    length = sprintf(ptr + (char)ptr[0], "%s\n", x);
    ptr[0] += length;

    close(fd);

    /* Check for pipe error */
    if (pipe(pfds) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid==-1) {
        /* fork() er */
        perror("fork");
        exit(1); /* parent exits */
    }
    /* CHILD PROCESS */
    else if (pid==0) {
        usleep(10000);
        int i;
        close(pfds[WRITE_END]);
        for (i = 0; i < 10000; i++)
        {
            read(pfds[READ_END], buf, BUFF_SIZE);
            length = sprintf("%s", buf);
            ptr[0] += length;
        }
        
        close(pfds[READ_END]);
        exit(0);
    }
    /* PARENT PROCESS */
    else {
        int i;

        close(pfds[READ_END]);
        for (i = 0; i < SIZE; i++) {
            if (i % n == 0) {
                /* notify child */
                write(pfds[WRITE_END], x, strlen(x));
            }
        }

        close(pfds[WRITE_END]);
        wait(NULL);

        /* read from the shared memory object */
        printf("%s", (char *)ptr);
    }

    // /* Unlink memory */
    // r = shm_unlink(name);
    // if (r != 0) {
    //     error_and_exit("shm_unlink");
    // }

    return 0;
}
