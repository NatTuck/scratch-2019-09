
# Lecture 14: Semaphores & Thread Intro

## Review

Data races. Conditions:

 - Concurrent execution of multiple processes / threads.
 - Shared memory / objects
 - Concurrent access must occur
 - At least one process must write to the shared data

Any program with concurrency + shared data can be assumed to be broken.

Locks let us avoid data races if we follow the lock rule:

 - Each piece of shared data has an associated lock.
 - We only access the data while holding the lock.
 - Any atomic modification we want to do occurs between locking
   and unlocking.

Deadlock conditions:

 - Multiple locks.
 - Locks are locked in different order in different parts of the
   program, allowing for "circular wait".

Avoiding deadlock:

 - Never hold more than one lock.
 - Lock ordering: Define a global order among all locks in the program,
   and always take multiple locks in that order.
 - If your system has a mechanism to take multiple locks at once
   without deadlock, you can use that.

Barrier:

 - A barrier is a mechanism that syncronizes execution of multiple
   processes in time.
 - Either the processes are executing code before the barrier or code
   after the barrier, but never both concurrently.

Pseudocode:

```
worker(xs*, ii) {
    xs[ii] = ii;
    barrier_wait(); 
    print(sum(xs));
}

main() {
    shared_array xs[10];
    spawn 10 processes of worker(&xs, ii);
}
```

## Semaphores

A semaphore is an integer + two associated operations:

 * sem_wait: Attempt to decrement, but if this would bring the value
             below zero, block instead until we can decrement
             without dropping the value below zero.
 * sem_post: Increment the integer, waking up anyone who was
             previously blocked.

   


