#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

#define NN 10

// A billion
const long TOP = 1000000000;

//long sum = 0;
//pthread_mutex_t mutex;

typedef struct sum_job {
    long r0;
    long r1;
    long sum;
} sum_job;

void*
sum_range_thread(void* arg)
{
    sum_job *job = (sum_job*)arg;

    long sum = 0;
    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    job->sum = sum;
    return (void*) job;
}

int
main(int _ac, char* _av[])
{
    pthread_t threads[NN];
    long NPP = TOP / NN;

    for (long ii = 0; ii < NN; ++ii) {
        sum_job* job = malloc(sizeof(sum_job));
        job->r0 = NPP * ii;
        job->r1 = job->r0 + NPP;
        pthread_create(&(threads[ii]), 0, sum_range_thread, job);
    }

    long sum = 0;
    for (long ii = 0; ii < NN; ++ii) {
        void* tmp;
        pthread_join(threads[ii], &tmp);
        sum_job* job = tmp;
        sum += job->sum;
        free(job);
    }

    printf("sum = %ld\n", sum);

    return 0;
}
