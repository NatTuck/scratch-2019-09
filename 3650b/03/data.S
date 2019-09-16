
.global main
.text

main:
    enter $0, $0

    mov $longfmt, %rdi
    mov $foo, %rsi
    mov $0, %al
    call printf

    mov $longfmt, %rdi
    mov $bar, %rsi
    mov $0, %al
    call printf

    mov $longfmt, %rdi
    mov $baz, %rsi
    mov $0, %al
    call printf

  

    leave
    ret



.data

longfmt: .string "%ld\n"
.align 16
foo:
    .space 24, 0
bar:
    .byte 10
baz:
    .int 20
    .int 30
    .int 40


