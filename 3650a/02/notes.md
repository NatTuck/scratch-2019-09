
# 3650 Lecture 2: Assembly in more depth

Intel 4004 display controller.

 - 8 bit microprocessor
   - 8 bit memory address = 256 bytes of RAM max

CPU operation:

 - read an instruction from memory @ IP
 - execute that instruction
 - increment IP 
 - repeat

CPUs can store numbers internally in "registers".

 - We have 6 registers:
   - A, B, C, D
   - IP - stores address of next instruction to execute
   - FLAGS - results from CMP instruction

Kinds of instruction:

 - add %c        (a = a + c), because a is the "accumulator"
 - AND %c        (a = a (bitwise and) c)
 - mov %a, %c    (c = a)
 - mov (%a), %c  (load the value in memory at address in %a into %c)
 - mov %c, (%a)  (store the value in %c ...) 
 
 - cmp %a, %b
 - jge label\_if_bigger
 

The 8086 was a 16-bit microprocessor.

 - It had a 16-bit data bus, registers, etc.
 - Maximum addressable RAM = 2^16 = 64k
 - It had 9-ish registers.
   - general purpose: ax, cx, dx, bx, si, di, bp, sp
      - x = extended, i = index, p = pointer
      - can access lower half of %ax with %al, upper with %ah
   - special purpose: ip, flags
   
 - It really had a 20-bit data bus.
   - 20^20 = 1 megabyte
   - the top 360k was reserved for stuff like the graphics controller
   - Actual RAM was limited to 640k
 - It had a "segment register", which indicated which 16-bit
   memory area addresses referred to.

The Intel 80386 was a 32-bit microprocessor (the first modern "intel x86")

 - 32-bit data bus 
 - 4 gigabytes

 - Registers: %eax, %ecx, %edx, %ebx, %esi, %edi, %esp, %ebp
   - %eip, %flags
 - %ax = lower 16 bits of %eax, %al = lower 8 bits

The AMD Athlon 64 was a 64-bit microprocessor, backwards compatible with
the 80386 and 8086.

 - It has a 48-bit data bus, extendable to 64 bits.
   - How much RAM with 48-bit addresses? 256 TB
   - Some Intel machines have a 57-bit data bus.
 - 64-bit registers.
   - %rax, %rcx, %rdx, %rbx, %rdi, %rsi, %rbp, %rsp
     - %eax, %ax, %al
   - %r8 .. %r15 
 

# Passing conventions:

 - Arguments are passed in %rdi, %rsi, %rdx, %rcx, %r8, %r9
 - Values are returned in %rax (and %rdx, conceputally)


 - Safe: %rbx, both pointers, effectively, %r12..r15
 
