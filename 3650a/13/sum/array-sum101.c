#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>

void*
malloc_shared(size_t size)
{
    return mmap(0, size, PROT_READ|PROT_WRITE,
                MAP_SHARED|MAP_ANONYMOUS, -1, 0);
}

void
free_shared(void* ptr, size_t size)
{
    munmap(ptr, size);
}

int
main(int _ac, char* _av[])
{
    // A billion
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    printf("Summing numbers divisible by 101 from 0 to %ld.\n", TOP - 1);

    pid_t kids[10];

    // exactly one shared resource: sum
    long* sum = malloc_shared(10 * sizeof(long));
    for (int ii = 0; ii < 10; ++ii) {
        sum[ii] = 0;
    }

    // lock protects shared resource: sum
    //sem_t* lock = malloc_shared(sizeof(sem_t));
    //sem_init(lock, 1, 1);

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // do nothing
        }
        else {
            int i0 = NPP*pp;
            int iN = NPP*(pp + 1);

            for (long ii = i0; ii < iN; ++ii) {
                if (ii % 101 == 0) {
                    sum[pp] += ii;
                }
            }

            munmap(sum, sizeof(long));
            exit(0);
        }
    }

    long total = 0;
    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
        total += sum[pp];
    }

    printf("Sum = %ld\n", total);

    munmap(sum, sizeof(long));

    return 0;
}
