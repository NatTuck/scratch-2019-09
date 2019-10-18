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
    int rv;
    int* shared = mmap(0, 4096, PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(shared != (int*)-1);

    for (int ii = 0; ii < 10; ++ii) {
        shared[ii] = ii;
    }

    int cpid;
    if ((cpid = fork())) {
        printf("parent: sleep 1\n");

        volatile long x;
        for (long ii = 0; ii < 1 * 1000 * 1000 * 1000; ++ii) {
            x++;
        }

        printf("parent: mutating array\n");
        for (int ii = 0; ii < 10; ++ii) {
            shared[ii] = ii * 100;
        }

        waitpid(cpid, 0, 0);
    }
    else {
        printf("child: array contents 1");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d: %d\n", ii, shared[ii]);
        }

        volatile long x;
        for (long ii = 0; ii < 2 * 1000 * 1000 * 1000; ++ii) {
            x++;
        }

        printf("child: array contents 2");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d: %d\n", ii, shared[ii]);
        }
    }

    rv = munmap(shared, 4096);
    assert(rv != -1);
    return 0;
}
