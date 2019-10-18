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
    int rv;

    int fd = open("./array.mem", O_RDONLY);
    assert(fd != -1);

    int* xs = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    assert(xs != (int*)-1);

    for (int ii = 0; ii < 12; ii++) {
        printf("%d * %d = %d\n", ii, ii, xs[ii]);
    }

    rv = munmap(xs, size);
    assert(rv != -1);

    rv = close(fd);
    assert(rv != -1);

    return 0;
}
