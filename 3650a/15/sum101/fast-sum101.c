#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

// A billion
#define PP 10
const long TOP = 1000000000;

typedef struct sum_job {
    long r0;
    long r1;
    long sum;
} sum_job;

void*
thread_main(void* arg)
{
    sum_job* job = (sum_job*) arg;
    long sum = 0;
    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }
    job->sum = sum;
    return job;
}

int
main(int _ac, char* _av[])
{
    long NPP = TOP / PP;

    pthread_t kids[PP];
    int rv;

    for (long pp = 0; pp < PP; ++pp) {
        sum_job* job = malloc(sizeof(sum_job));
        job->r0 = NPP * pp;
        job->r1 = job->r0 + NPP;
        rv = pthread_create(&(kids[pp]), 0, thread_main, job);
    }

    long sum = 0;

    for (long pp = 0; pp < PP; ++pp) {
        void* ret;
        rv = pthread_join(kids[pp], &ret);
        sum_job* job = (sum_job*) ret;
        sum += job->sum;
    }

    printf("sum = %ld\n", sum);

    return 0;
}
