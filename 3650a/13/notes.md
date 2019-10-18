
# Sample Sort

Plan: A parallel version of Quicksort for many processors.

Strategy:

` - Partition our input near-evenly.
   - Processor 1 gets the lowest N/P items to sort.
   - Processor 2 gets the next lowest
   - ...
   - Can have each processor read whole input and select
     its own partition.
 - To pick (P-1) pivots for partitioning,
   - Randomly sample a reasonable subset of the elements
     - Definitely at least 3*P elements.
       - For assignment, exactly 3*P
     - Probably a lot more than that.
     - Optimally less than 1% on large inputs.
   - Sort the sample.
   - Pick perfect pivots from the sorted sample.
 - Once each processor has its data, it can sort that data
   sequentially (e.g. using normal quicksort).

# Problem: Data Races

Requirements:

 - Concurrent execution of at least two processes (or threads).
 - Shared memory.
 - At least one process must write to that shared memory.

Locks:

 - No two processes can have the same lock locked at the same time.
 - If we only access a shared object while holding a lock, we can
   control concurrent execution to avoid corrupted data.


# Problem: Deadlock

Requirements:

 - Circular wait.

Solutions:

 - Only have one lock.
 - Never hold two locks.
 - Enforce lock ordering: All locks must be taken in a single,
   globally consistent order.
 
