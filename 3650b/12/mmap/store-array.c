#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

    for (int ii = 0; ii < 10; ++ii) {
        xs[ii] = ii * ii;
    }

    rv = munmap(xs, size);
    assert(rv != -1);

    rv = close(fd);
    assert(rv != -1);

    return 0;
}
