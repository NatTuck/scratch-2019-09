
// $ ./ifact 1
// => 1
// $ ./ifact 5
// => 120

.global main

.data
fmt: .string "%ld\n"

.text

main:
    enter $0, $0

    mov 8(%rsi), %rdi
    call atol

    // nn = %rdi
    // yy = %rax

    // nn = atol(argv[1])
    mov %rax, %rdi

    // long yy = 1;
    mov $1, %rax

loop:
    cmp $1, %rdi
    jle out
    // while (nn > 1) { // nn is %rdi, yy is %rax

    imul %rdi
    //   yy = yy * nn;
    //   nn = nn - 1;
    sub $1, %rdi
    // }
    jmp loop

out:
    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret
