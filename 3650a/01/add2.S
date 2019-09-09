
.global main

.text
// add2(%rdi) -> %rax

add2:
    enter $0, $0

    // long y = x;
    mov %rdi, %rax // copy

    // x += 2;
    add $2, %rax

    // return x;
    leave
    ret

main:
    enter $0, $0

    // long x = 5;
    mov $5, %rdi
    // safe register: %rbx
    mov %rdi, %rbx

    // long y = add2(x);
    call add2
    // result is in %rax
    
    mov $fmt, %rdi // string arg
    mov %rbx, %rsi // x
    mov %rax, %rdx // y
    mov $0, %al
    call printf
    // %rdi, %rsi, %rdx

    // println("{x} + 2 = {y}\n");
    // printf(string, x, y)

    leave
    ret

.data
fmt: .string "%ld + 2 = %ld\n"
