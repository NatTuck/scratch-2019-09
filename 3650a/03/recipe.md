

# How to write ASM programs.

 - A program is a collection of functions.
 - Figure out what functions you need and write them.

# How to write a function.

 1. Signature

    long add1(long xx);

 2. Pseudocode

    {
        return xx + 1;
    }

 3. Variable Mappings

    - xx is %rdi
    - (xx + 1) %rax

Which registers:

Safe registers (survive function calls):

 - Five safe registers: %rbx, %r12, %r13, %r14, %r15

Temporaries (get clobbered by function calls):
 
 - Two pure temporaries: %r10, %r11
 - Six function arg registers (temporaries): 
   - %rdi, %rsi, %rdx, %rcx, %r8, %r9
 - Return value register: %rax

 4. Skeleton

    // prologue (label, save save regs, enter)
    add1:
        enter $0, $0





    // hole for function body 

    // epilogue  (reverse prolog)
        leave
        ret 


 5. Write the body code.

        mov %rdi, %rax  
        add $1, %rax





