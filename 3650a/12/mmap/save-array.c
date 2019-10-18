#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int
main(int _ac, char* _av[])
{
    int size = 10 * sizeof(int);

    int fd = open("./array.mem", O_CREAT|O_TRUNC|O_RDWR, 0644);
    assert(fd != -1);

    int rv = ftruncate(fd, size);
    assert(rv != -1);

    int* xs = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    assert(xs != (int*)-1);

    for (int ii = 0; ii < 20; ii++) {
        xs[ii] = ii * ii;
    }

    rv = munmap(xs, size);
    assert(rv != -1);

    rv = close(fd);
    assert(rv != -1);

    return 0;
}
