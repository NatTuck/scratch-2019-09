
# CS3650 - Semester Review

This semester we covered systems programming.

 - Platform: Operating System + Instruction Set Archetecture
 - Concretely: Linux on AMD64
 - Computer programs are sequences of machine instructions.
 - One especially interesting one: syscall

## Assembly Programming

 - Main idea: Understanding that C code can be compiled to
   a series of machine instructions

## C Programming

 - Homework: Vectors and Hashmaps
 - Processes have address spaces

## Processes and File Descriptors

 - processes created with fork
 - programs are started with exec
 - file descriptor table
 - can do redirects by messing with the table
 - Homework: Shell

## Virtual Memory and Memory Mapping

 - CPU and OS conspire to forge memory address
 - Page Table 
 - This translation lets us to memory mapping:
   - Files
   - Shared memory 
 - One syscall to rule them all: mmap

## A big mess: Shared memory

 - Concurrency + Shared Memory + Writes = Data Races
 - Solution: Locks
 - Locks lead to deadlock

## Memory Allocation

 - We want to be able to malloc and free. 

## OS Kernels

 - Kernels are the code that's running all the time when
   the computer is on, without any of that safety stuff.
 - Kernel manages shared resources, enforces limitations
   on userspace processes.
 - Is where the implementation of syscalls live.
 - Homework: See how system calls work from the kernel side.

## Filesystems

 - Data sometimes want to last longer than a process, or even longer than the
   system stays turned on.
 - Long lived data wants to be stored in a human understandable heirarchy.
 - Common structure: Tree of files and directories.
 - We looked at persistent storage hardware: HDDS, SSDs.
 - We looked at specific filesystem formats: FAT32, EXT*, Log Structured FS




