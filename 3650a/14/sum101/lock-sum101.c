#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

// A billion
#define PP 10
const long TOP = 1000000000;

pthread_mutex_t lock;
long sum = 0;

typedef struct sum_job {
    long r0;
    long r1;
} sum_job;

void*
thread_main(void* arg)
{
    sum_job* job = (sum_job*) arg;
    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            pthread_mutex_lock(&lock);
            sum += ii;
            pthread_mutex_unlock(&lock);
        }
    }
    free(job);
    return 0;
}

int
main(int _ac, char* _av[])
{
    long NPP = TOP / PP;

    pthread_t kids[PP];
    int rv;

    rv = pthread_mutex_init(&lock, 0);

    for (long pp = 0; pp < PP; ++pp) {
        sum_job* job = malloc(sizeof(sum_job));
        job->r0 = NPP * pp;
        job->r1 = job->r0 + NPP;
        rv = pthread_create(&(kids[pp]), 0, thread_main, job);
    }

    for (long pp = 0; pp < PP; ++pp) {
        rv = pthread_join(kids[pp], 0);
    }

    printf("sum = %ld\n", sum);

    return 0;
}
