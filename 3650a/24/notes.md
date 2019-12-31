
# Computer Systems

 - Systems programming
 - A system is: Operating System + Instruction Set Archetecture
 - Concretely: Linux on AMD64
 - Programmers generate a series of machine instructions, which
   run on a CPU.
 - Expecially notable instruction: syscall 

## Assembly Programming

 - C maps pretty directly to assembly.

## C Programming

 - One assignment: Data structures.
 - Specifically, Vectors and Hashmaps

## Processes and File Descriptors

 - fork
 - exec
 - File descriptor table
   - Can do input and output redirection
 - Assignment: Shell

## Virtual Memory and Memory Mapping

 - The system call that does everything: mmap
 - Every process has a page table.
 - Memory mapping:
   - Files
   - Inter-process communication with shared memory
 - We build some memory allocators

## The Great Mess: Concurrency with Shared Memory
 
 - Concurrency + Shared Memory + Writes = Data Races
 - Solution: Locks
 - Problem with locks: Deadlock

## OS Kernels

 - The OS kernel is always running
 - Managing access to shared resources for reliablity and security.
 - It provides access through system calls.
 - Homework: Walk though how a system call works from the kernel side.

## Filesystems

 - Long term data wants to get stored in some sort of heirarchical namespace.
 - Filesystems provide this as a tree of directories + files. 
 - We looked at how persistent storage hardware works / its properites.
 - We looked at specific structures for storing data on persistent storage 
   hardware.




