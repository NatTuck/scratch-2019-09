.global main

.text

// How to arguments and return values work.

// long add2(long x)
add2:
    enter $0, $0

    // input in %rdi 

    // long y = x;
    mov %rdi, %rax

    // y = y + 2;
    add $2, %rax

    // return y;
    // result in %rax

    leave
    ret

main:
    enter $0, $0

    mov $5, %rdi
    call add2

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret


.data
fmt: .string "%ld\n"
