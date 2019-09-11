.global main

.text

main:
    enter $0, $0

    mov $40, %rax
    mov $30, %rbx
    mov $20, %rcx
    mov $10, %rdx

    mov %rdx, %rdi

    cqo
    idiv %rdi // (%rax = %rax / %rdx) = 4
              // (%rax = %rdx / %rax) = 0
              // crash? 

    mov $longfmt, %rdi
    mov %rax, %rsi
    mov $0, %al 
    call printf

    mov $0, %rax
    leave
    ret

.data
longfmt: .string "%ld\n"
