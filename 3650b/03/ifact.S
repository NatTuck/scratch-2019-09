.global main

.data
fmt: .string "%ld\n"

.text

main:
    enter $0, $0
    
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rdi

    // long xx = 1;  // xx is %rax
    mov $1, %rax
    mov $1, %rsi

loop:
    // for (int ii = 1; ii <= nn; ++ii) { // nn %rdi
    cmp %rdi, %rsi
    jg loop_done

    //   xx = xx * ii;     // ii %rsi
    imul %rsi
    // }

    add $1, %rsi
    jmp loop

loop_done: 
    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    leave
    ret
