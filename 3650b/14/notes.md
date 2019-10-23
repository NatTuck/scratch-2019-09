
# Semaphores and Introducing Threads

## Review

Conditions for a data race:

 - Multiple processes executing concurrent.
 - You must have shared data accessed concorrently by those processes.
 - At least one has to be writing.

Solution: Locks

As long as we follow the rules for locks, we solve our data races:

 - For every piece of shared data, we must have an associated lock.
 - While accessing the shared data, we must hold the lock.
 - If we expect atomicity, we must do the entire atomic operation
   while holding the lock.

Conditions for deadlocks:

 - Need to lock more than one lock.
 - Multiple locks are locked in different order in different places,
   allowing a "circular wait".

Avoiding deadlock:

 - Create a global order for all locks in the program. Require that
   multiple locks always be locked in order.
 - Never lock more than one lock.
 - Some environments provide a feature to lock more than one lock at
   once deadlock free (e.g. C++ std::lock)

## Barrier

Pseudocode:

```
worker(ii, xs*, bb) {
    xs[ii] = ii;
    barrier_wait(bb);
    print(sum(xs));
    barrier_wait(bb);
    xs[ii] -= 1;
}

main {
   barrier bb(10);
   int xs[10] = {0...}; 
   for ii in 1 to 10:
     spawn worker(ii, xs, bb);
}

```

## Semaphores

A semaphore is an integer, with two operations:

 - sem_wait: Attempt to decrement, if this would bring the
             value below zero, block until the decrement
             can be completed.
 - sem_post: Increment the semaphore, this gives blocked
             processes the opportunity to retry their decrement
             and potentially continue past sem\_wait.















