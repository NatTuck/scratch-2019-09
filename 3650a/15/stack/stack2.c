#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

// Our stack
int stack[5];
int stptr = 0;
pthread_mutex_t mutex;
pthread_cond_t  condv;

void
stack_push(int xx)
{
    pthread_mutex_lock(&mutex);
    // precondition: stptr < 5
    while (stptr >= 5) {
        pthread_cond_wait(&condv, &mutex);
    }
    stack[stptr++] = xx;
    pthread_cond_broadcast(&condv);
    pthread_mutex_unlock(&mutex);
}

int
stack_pop()
{
    pthread_mutex_lock(&mutex);
    while (stptr <= 0) {
        pthread_cond_wait(&condv, &mutex);
    }
    int yy = stack[--stptr];
    pthread_cond_broadcast(&condv);
    pthread_mutex_unlock(&mutex);
    return yy;
}

void*
producer_thread(void* _arg)
{
    for (int ii = 0; ii < 1000; ++ii) {
        stack_push(ii);
    }
}

int
main(int _ac, char* _av[])
{
    pthread_t threads[2];
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&condv, 0);

    for (int ii = 0; ii < 2; ++ii) {
        pthread_create(&(threads[ii]), 0, producer_thread, 0);
    }

    for (int ii = 0; ii < 2000; ++ii) {
        int yy = stack_pop();
        printf("%d\n", yy);
    }

    return 0;
}
