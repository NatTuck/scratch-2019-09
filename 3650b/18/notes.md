
# Lecture 18, More Memory Allocation

## Problem: Multiple Threads

A simple free list has global shared mutable state: the free list.

Data race that causes heap corruption - great.

Simplest solution: Add a lock.

 - Problem: Slow
 - Malloc / free are pretty common operations, so multiple threads
   are likely to call them simultaneously.
 - Slowdown 1: Memory allocations are sequentialized.
 - Slowdown 2: Contention on mutex.

### Faster Plan A: Per-Thread Cache

 - We have one shared global free list.
 - We have one "cache" free list per thread.

malloc:

 - Try the local cache first.
 - If not, try the global freelist.
 - If not, mmap.

free:

 - Just stick it on the local cache.
 - Maybe sometimes move stuff from the local cache to
   the global freelist.
   - How do we coalesce across threads?
   - Probably need a good answer for that.

How do we have a seperate free list for each thread?

 - Thread local storage.
 - Google "gnu thread local storage".
 
```
__thread int foo = 4;
```


### Faster Plan B: Multiple Arenas

"Arena" in the context of memory allocators means all the structures of a
functional single-threaded allocator.

So an arena could be:

 - A free list
 - A buddy-system / buckets style array of free lists.
 - Etc.

Each arena can have its own mutex.

 - Items are marked with which arena they were allocated from.
 - Items are always freed to their source arena.

We get best behavior if:

 - Each thread tends to do all its allocations from the same arena.
 - Each thread tends to allocate from a different arena.

How to pick which arena each thread uses.

 - Each thread starts with a random thread-local favorite_arena.
 - Threads try to allocate from their favorite arena.
   - Start by using try_lock on the mutex.
   - If try lock fails, they pick a new favorite arena (maybe the next one).
   - We only use try_lock once per attempt. After swithing favorites once
     we just use pthread\_lock on the next mutex.

```
int arena_count = 8;
free_list_node* head[65536];
pthread_mutex_t* lock[65536];
```

## Real World Allocators

ptmalloc: GNU Libc Malloc

 - Loosely based on the traditional free list design.
 - Uses per-thread arenas.
 - Tons of special case optimizations.
 - Design goal seems to be to prevent worst cases from being bad.


tcmalloc: Google's Thread Cache Malloc

 - A bucket allocator
 - There's a global bucket array with all the sizes.
   [8, 12, 16, 24, ..., 16M]
 - There's a local cache with the smaller sizes for each thread.
   [8, 12, 16, 24, ... 64k] 
 - There's a garbage collector that runs in separate threads to
   periodically move local cache blocks back to the global list
   and coalesce.


jemalloc: Facebook's Multi-Arena Allocator

 - Based on (and still is) the default FreeBSD allocator.
 - A bucket allocator with multiple arenas.
 - # of arenas = 4 * CPUs.
 - Works in 2MB chunks (rather than allocating single pages).
 - Most of the optimization is in chunk management.
   - e.g. More than one size can go in a single chunk.
 - This is probably the fastest general purpose allocator today.

























