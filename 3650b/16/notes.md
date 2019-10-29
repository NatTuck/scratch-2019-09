
# 32-bit Page Tables (e.g. i386)

 - Each process has its own virtual address space
 - Each process has a page table mapping each virtual
   page to a physical page.
   
32 bit virtual address space

 - Addressable space 4GB
 - A page is 4k
 - How many pages? 1M

So the page table:

 - Has 1M rows.
 - Each row contains
   - 20 bits for the physical page #
   - A bunch of space for metadata (e.g. flags and stuff)
   - Call it 64 bits = 8 bytes
 - Is 8MB for each process.
 - A common memory size for a i386 machine was 4MB.

Observation: Most rows in the table are likely to be empty.

 - Real tempting to just use a hash table and have no (or maybe
   a factor of 2) space overhead.


## 64-bit page tables

 - 64-bit virtual address space
 - wait, no, 48-bit virtual address space

 - 48 - 12 (for the page offset) = 36 bit page #
 - 2^36 * 16 bytes = 2^40 = 1TB
 
 - not what they did: 12-bit table indexes
 - 2^12 * 16 bytes = 64 KB
 
 - what they did: 9-bit table indexes
 - 2^9 * 16 bytes = 8KB
 - That means 4-level tables.
 
# Avoiding the performance hit for translation.

If we did page table lookups on every memory access
it would be really expensive.

To speed things up, processors cache these lookup results.

This cache is called the "translation lookaside buffer" or TLB, and usually
stores 1536 entries.

Common example:

```
int xs[16384] = ...;
for (long ii = 0; ii < 16384; ++ii) {
    int sum += xs[ii];
}
```

For each page:

 * There are 1024 integers.
   * We need one memory read for each
 * We do one full page translation
   * Four memory reads.
 * Overhead = 1028 / 1024.0
   * That's 0.4%

Table in hardware. Each row has:

 * Virtual page #
 * Physical page #
 * Using phsical wires, we can lookup
   in constant time.

# Context Switches

 - Imagine we have a single core processor.
 - Imagine our computer is running two processes.
 - The timer interrupt fires, and the OS kernel needs
   to put the active process to sleep and schedule the
   other one.

In order to change processes

 - The kernel is going to push all the registers to the stack
   of the active process.
 - Save off the stack pointer into the process table.
 - Load the address of the page table for the new process
   into CR3.
 - Load the stack pointer for new process from process table.
 - Pop all the registers from the new process's stack.

This is one of the reasons why threads can be concretely faster
than processes, even on Linux.

Reasons to context switch:

 * Timer interrupt
 * Thread tries to do an I/O system call
 * Synchronization tools like mutexes, semaphores, message queues. 
 * ... 


## Laptop Specs

 * Intel Core i7 boosts up to ~ 4 Ghz
 * That means we have a clock cycle every 0.25 ns.

```
for (;;) { a += 5; }
```

This CPU has four ALUs, so it can execute 4 independent
adds per clock cycle.

```
for (;;) { a += 5; b += 5; c += 5; d += 5; }
```

Main Memory

 * Size: 16 GB
 * Throughput: 20 GB/s
 * Latency: 60ns = 240 cycles
 
L3 Cache:

 * Size: 8MB (shared)
 * Through: > 200 GB/s
 * Latency: 11ns = 44 cycles
 
L2 Cache: 

 * Size: 256KB (per core)
 * Throughput: > 400 GB/s
 * Latency: 3ns = 12 cycles
 
L1 Data Cache:

 * Size: 32KB (per core)
 * Throughput: > 1 TB/s
 * Latency: 1ns = 4 cycles

What if integeters are each requested seperately?

1 billion * 60 ns?
 = 1 minute

Caches operate in cache lines, which are 64 bytes.

How many ints fit in a cache line? 16

1 minute / 16.0 ?
  = 3.75 seconds

Prefetcher.

 - Tries to guess what you're going to access next,
   and get it into cache early.














 
 
 
 
 
 
 
 





















   
 
 
 
 



















