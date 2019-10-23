#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define NN 10

void*
thread_main(void* arg)
{
    int *xx = (int*) arg;
    *xx += 10;
    return (void*) xx;
}

int
main(int _ac, char* _av[])
{
    int nums[NN];
    int rv;
    pthread_t threads[NN];

    printf("Main: starting %d threads.\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        nums[ii] = ii;
        rv = pthread_create(&(threads[ii]), 0, thread_main, &(nums[ii]));
        assert(rv == 0);
    }

    printf("Main: started %d threads.\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        void* ret;
        rv = pthread_join(threads[ii], &ret);

        int yy = *((int*) ret);
        printf("Main: Joined thread: %d, ret = %d\n", ii, yy);
    }

    return 0;
}
