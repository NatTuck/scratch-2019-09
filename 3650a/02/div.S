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
    idiv %rdi   // %rax = %rax / %rdx
   
    mov $longfmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret

.data
longfmt: .string "%ld\n"
