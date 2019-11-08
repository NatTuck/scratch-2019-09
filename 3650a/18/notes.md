
# Lecture 18: More on Memory Allocators

## Problem: Multiple Threads

Basic free list has global shared mutable data: the free list.

Simple plan: Add a lock.

Advantages:

 - Simple
 - Doesn't have any data races
 
Disadvantages:

 - Slow
 - malloc / free are common operations
 - threads are going to spend a bunch of time fighting over
   that lock.
 
Better solutions:

### Per-Thread Cache

We have one global freelist.

Also have a local freelist for each thread.

 - malloc goes to local list first
 - continues to global list on failure
 - continues to mmap if that fails

 - free goes to the local list first
 - sometimes moves things to global list
   - when? dunno.

 - only need lock on global list

Advantages:

 - No locks on many mallocs, most frees.
   - This makes things pretty fast.
 - Problem: It's hard to coalesce (can't combine blocks on differnet lists) so
   there's significant memory overhead.

Useful trick: Thread local storage.

 - To google "gcc thread local storage C"

```
__thread int x = 5;   // every thread gets its own x
```

## Multiple Arenas

When I say "Arena", I mean the data structure for a complete
single-threaded allocator.

A free list is an arena, as is the list of lists for buddy system or buckets.

For example, we could have 10 free lists (arenas).

 - Each arena gets its own mutex.
 - With enough arenas (at least one per thread) we can completley avoid
   contention for allocations within threads.
 - To free an object, you put it back in it source arena. This may still
   cause contention if the object was allocated in a different thread
   than the one where it was freed.

How to pick arena to allocate from:

 - Each thread starts with a random favorite arena.
 - When trying to lock an arena for malloc, first use pthread_trylock
   - If that fails we have contentoin on the arena we picked.
   - Switch to a different favorite arena (maybe favorite++ % A)
   - Only trylock once - do a real lock after that.
   - Over time, this should spread each thread out to a different arena.

## Real world allocators

ptmalloc: The GNU libc allocator

 - Loosely based on the traditional free-list design.
 - Uses per-thread arenas.
 - Tons of special-case optimizations.
 - Main design goal seems to be to prevent there from
   being noticable "worst cases".

tcmalloc: Google's Thread Caching Malloc

 - A bucket allocator
   - [8, 12, 16, 24, 32, ..., 64k, ..., 4m, ..., 4m]
 - Each thread has a cache with an array of the smaller buckets
   - [8, 12, 16, 24, 32, ...., 64k]
 - A garbage collector runs periodically to move items from thread
   caches back to the global list.

jemalloc: Facebook's Multi-Arena Allocator

 - A bucket allocator with multiple arenas
 - Arenas = 4 * CPU cores
 - Uses 2MB (rather than 4k) chunks.
 - Most of the optimization is chunk management.
   - They can fit multiple sizes per chunk through sheer bookkeeping.
 - Widely considered to be the fastest allocator today.

## madvise









