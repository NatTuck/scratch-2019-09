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
    int rv;
    int size = 10 * sizeof(int);

    int fd = open("./array.mem", O_RDONLY);
    assert(fd != -1);

    int* xs = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    assert(xs != (int*)-1);

    for (int ii = 0; ii < 10; ++ii) {
        printf("%d * %d = %d\n", ii, ii, xs[ii]);
    }

    rv = munmap(xs, size);
    assert(rv != -1);

    rv = close(fd);
    assert(rv != -1);

    return 0;
}
