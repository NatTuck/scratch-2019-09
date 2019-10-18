
# Next homework: Sample Sort

# Today: Let's add up some numbers.

## Problem 1: Data Races

Conditions:

 - Multiple processes executing concurrently (or, later, threads).
 - Shared data.
 - At least one process writes to the shared data.

Potential solution: Locks

 - Lock invariant:
   - Each piece of shared data has an associated lock
   - Any process that access the shared data first locks the lock.
   - When the process is done (any sequence of operations intended to be atomic
     is completed) it unlocks the lock.

## Problem 2: Deadlocks

Conditions for deadlock:

 - More than one lock.
 - Two or more processes take the locks in an order such that
   we have a cycle of waiting processes.

Solutions:

 - Only have one lock.
 - Never take more than one lock at a time.
 - Lock ordering: Assign a global order to all locks in a program. You're never
   allowed to lock an earlier lock after a later lock.


