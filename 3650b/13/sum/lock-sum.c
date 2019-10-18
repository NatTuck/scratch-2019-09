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
    return mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
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

    long* sum = malloc_shared(sizeof(sum));
    *sum = 0;

    sem_t* lock = malloc_shared(sizeof(sem_t));
    sem_init(lock, 1, 1);

    pid_t kids[10];

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // do nothing
        }
        else {
            long i0 = NPP * pp;
            long iN = i0 + NPP;

            for (long ii = i0; ii < iN; ++ii) {
                if (ii % 101 == 0) {
                    sem_wait(lock); // lock the lock
                    *sum += ii;
                    sem_post(lock); // unlocking the lock

                    //   process 1          process 2
                    // mov *sum, %r1
                    //                      mov *sum, %r1
                    // add ii, %r1
                    //                      add ii, %r1
                    // mov %r1, *sum
                    //                      mov %r1, *sum
                }
            }

            munmap(sum, sizeof(long));
            exit(0);
        }
    }

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    printf("Sum = %ld\n", *sum);

    munmap(sum, sizeof(long));
    return 0;
}
