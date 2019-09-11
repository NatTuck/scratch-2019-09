# CS3650 Lecture 2: More Assembly

In case you missed it: http://khoury.neu.edu/~ntuck/


# Intel Processor Archeology

The mists of time: The Intel 4004 graphics controller, might have looked
something like:

 - A 8-bit CPU
   - That's 8 address wires connected to RAM.
   - Max RAM = 2^8 bytes = 256 bytes
 - In addition to RAM, a CPU also has registers, or places that
   can store single (8-bit) numbers.
   - a, b, c, d 
   - ip - instruction pointer
   - flags - stores results of cmp instructions

What a CPU does:

 - Read an instruction from RAM @ IP
 - Execute that instruction
 - Increments IP
 - Repeat

Kinds of instructions:

 - mov %a, %b     // copy value in one reg to another
 - mov \$4, %b     // set immediate value
 - mov (%a), %b   // load value from RAM
 - mov %a, (%b)   // store value in RAM
 
 - add %a, %b     // %b = %a + %b
 - add %b         // %a = %a + %b
 - sub
 - xor

 - cmp $5, %c     // is c >= 5?
 - jge label      // if so, jump to label "label"

 - call a sub // not strictly nessisary
 - ret
 - jmp


The 8086 was a 16-bit microprocessor.

 - Had a 16-bit memory bus.
   - Max memory: 64k = 65536
 - Had 16-bit registers:
   - %ax, %cx, %dx, bx, si, di, sp, bp
     - x = extended, i = index, p = pointer
     - %al = low 8 bits of %ax, %ah = high 8 bits
   - ip, flags
 
 - Had a 20-bit memory bus.
   - Max memory: = 2^20 = 1MB
   - Needed a "segment register" which stored the high
     4 bits of memory addresses.
   - the top 360k was reserved for other hardware,
     so max 640k of RAM.


# The Intel 80386 was a 32-bit microprocessor, backwards compatible with the 8086.

 - 32 bit memory bus
   - Max memory: 4GB
 - It had 32-bit registers
   - %eax, %ecx, %edx, %ebx, %esi, %edi, %ebp, %esp
   - Old names still work.
     - %ax = lower 16 bits of %eax
     - %al is lower 8 bits of %eax

# The AMD Athlon 64 was a 64-bit microprocessor, backwards ...

 - It has a 48-bit data bus, expandable to 64-bit
   - Max memory: 256 TB
   - Intel ships servers with a 57-bit physical data bus
 - It has 64-bit registers
   - %rax, %rcx, %rdx, %rbx, %rsi, %rdi, %rbp, %rsp
   - %r8 .. %r15
   - %eax, %ax, %al all still work as expected.


#  Powers of two

1024 = 2^10 = 1k 1024^2 = 2^20 = 1M 2^30 = 1G 2^40 = 1T











