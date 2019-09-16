.global main

.data
fmt: .string "%ld\n"

.text

main:
    enter $0, $0
    
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rdi

    call fact

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret

fact:
    push %rbx
    enter $8, $0
    // Allocates two slots on the:
    //  - 0(%rsp)
    //  - 8(%rsp)

    // long fact(xx):   // xx = %rdi
    //   if (xx < 2): return 1;
    cmp $2, %rdi
    jl fact_base

    //   else: return xx * fact(xx-1);
    mov %rdi, %rbx
    sub $1, %rdi
    call fact

    imulq %rbx
    jmp fact_done

fact_base:
    mov $1, %rax

fact_done:
    leave
    pop %rbx
    ret
