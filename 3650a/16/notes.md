
# Page Tables

 - Each process gets its own virtual address space.
 - Virtual memory is managed in pages.
 - Each process has its own page table, mapping virtual
   pages to physical pages.

## 32-bit Page Tables (e.g. Intel i386)

How many potential 4k pages fit in a 32-bit address space?

 - 2^32 bytes is = 4 GB
 - That's 2^20 = 1M 4k pages
 
A row in the page table needs to store:

 - Physical page number: 20 bits =~ 3 bytes
 - Permissions and flags: ???
 - Total is at least 8 bytes.

So if a row is 8 bytes, and there are 1M entries, how big
is a table?

 - One page table takes 8MB.
 - A reasonable i386 computer had 4MB of RAM.

Important observation: Most page table rows aren't used.

Solution: Multi-level page tables.

 - Split the table into multiple levels
   - 2 for 32-bit
   - 4 for 64-bit
   
Problem: This slows down memory access. 

 - We need to have a physical address to actually read memory.
 - Software uses virtual addresses.
 - Translation needs to happen on every memory access.

Solution: Cache translations

 - This cache is called the "translation lookaside buffer".
 - It stores about 1536 page table mappings.

Consider a common workload:

```
int xs[...] = ...;
for (long ii = 0; ii < 10M; ++ii) {
    sum += xs[ii];
}
```

 - Each page is 4KB
 - That's how many ints? 1024
 - So for every 1024 integers:
   - We have 1024 loads to get the integers
   - We have 4 loads for the page table lookup.
   - 1028 / 1024.0 = 1.004
   - Overhead is 0.4%
   

## Context Switches

 - Consider a single-core processor running two processes
 - Well, actually running one.
 - The OS kernel decides to switch to the other one.
 - The kernel code starts running due to a hardware interrupt,
   e.g. from the scheduling timer.

Context switch:

 - Kernel pushes process registers to that process's stack.
 - Kernel saves where stack was to the process table.
 - Set CR3 = the page table of the new process.
 - Kernel loads stack pointer from process table.
 - Kernel pops registers from the new stack.
 - Basically just return.
 
By changing CR3, we've invalidated our TLB.
 
 - All memory accesses will be taking +4 accesses for a while.

This is a concrete advantage to threads. A context switch between
threads works the same, but doesn't change the page table.

Context switches are caused by:

 - Timer interrupt
 - Interprocess communication mechanisms, like semaphores and message queues.
 - Blocking on I/O.
 - ...

This laptop:

 - 1.9 GHz
 - Boosts up to 4 GHz for sequential tasks. 
 - One clock cycle takes: 0.25 ns 
 - An add operation can complete in one cycle.

```
for(;;) { a += 5; }
```

Each core has 4 ALUs, each can do an add per cycle if not
depending on the result of another ALU's operation.

```
for(;;) { a += 5; b += 5; c += 5; d += 5; }
```

Main Memory:

 * 16 GB of DDR3 2133
 * Throughput: 20 GB/s
 * Latency: 60ns = 240 clock cycles

L3 Cache:

 * Size: 8 MB (shared)
 * Throughput: > 200 GB/s
 * Latency: 11ns = 44 clocks

L2 Cache:

 * Size: 256 KB (per core)
 * Throughput: > 400 GB/s
 * Latency: 3ns = 12 clocks

L1 Data Cache:

 * Size: 32 KB (per core)
 * Throughput: > 1000 GB/s
 * Latency: 1ns = 4 clocks

Cache operates in Cache Lines, which are 64 bytes.

If every int was requested separately, it would take

500M * 60ns = 30s * 2 arrays = 60s

60s / 16.0 = 3.75 seconds
 














 
