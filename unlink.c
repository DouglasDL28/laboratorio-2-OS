#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

int main(int argc, char const *argv[])
{
    int r;
    const char *name = "OS"; // name of shm object

    /* Unlink memory */
    r = shm_unlink(name);
    if (r != 0) {
        perror("shm_unlink");
        exit(1);
    }
    return 0;
}
