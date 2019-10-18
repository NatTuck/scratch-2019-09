
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <assert.h>


int
main(int _ac, char* _av[])
{
    int* xs = mmap(0, 4096, PROT_READ|PROT_WRITE,
                  MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    assert(xs != (int*)-1);

    for (int ii = 0; ii < 10; ++ii) {
        xs[ii] = ii;
    }

    int cpid;
    if ((cpid = fork())) {
        //sleep(1);

        printf("mutating array\n");
        for (int ii = 0; ii < 10; ++ii) {
            xs[ii] = 100 * ii;
        }

        waitpid(cpid, 0, 0);
    }
    else {
        printf("Printing array 1:\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", xs[ii]);
        }
        printf("\n");

        //sleep(2);

        printf("Printing array 2:\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", xs[ii]);
        }
        printf("\n");
    }

    munmap(xs, 4096);

    return 0;
}
