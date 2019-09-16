
# A recipe for assembly programs

 - Figure out at least one function that your program
   needs.
 - Use the function recipie below to write it.
 - If you discover more functions, write them too.

# A recipie for an assembly function

 1. Signature

     long add1(long xx);

 2. Pseudocode

     {
        return xx + 1;
     }


 3. Variable mappings
 
   - xx goes in %rdi
   - (xx + 1) goes in %rax

 4. Skeleton

    // prologue (label, push safe regs, enter)
    add1:
        enter $0, $0

    // body, code goes here

    // epilogue (reverse prologue)
        leave
        ret


 5. Write the function body.

        mov %rdi, %rax
        add $1, %rax 


# Variable conventions

Temporary registers:

 - Arg regs: %rdi, %rsi, %rdx, %rcx, %r8, %r9
 - Return reg: %rax
 - Pure temporaries: %r10, %r11

Safe registers:

 - %rbx, %r12, %r13, %r14, %r15






