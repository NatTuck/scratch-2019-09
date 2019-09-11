.global main

.text


// long add2(long x)
add2:
    enter $0, $0

    // argument is in: %rdi    

    // long y = x;
    mov %rdi, %rax

    // y = y + 2;
    add $2, %rax 

    // return y;
    // result: %rax

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

    mov $0, %rax
    leave
    ret

.data

fmt: .string "%ld\n"
