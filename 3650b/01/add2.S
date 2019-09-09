
.global main

.data
fmt: .string "%ld + 2 = %ld\n"

.text

// add2(%rdi) -> %rax

add2:
    enter $0, $0

    mov %rdi, %rax
    add $2, %rax

    leave
    ret


main:
    enter $0, $0

    // x = 5;
    // y = add2(x);
    // print "{x} + 2 = {y}"
    // = printf("%ld + 2 = %ld\n", x, y);
    //          %rdi, %rsi, %rdx

    mov $5, %rdi
    mov %rdi, %rbx

    call add2

    mov $fmt, %rdi
    mov %rbx, %rsi
    mov %rax, %rdx
    mov $0, %al
    
    call printf

    leave
    ret


