.global main
.data
num: .space 8
prompt: .string "Enter a number:"
long_fmt: .string "%ld"
eol: .string "\n"
bigger: .string "bigger than 10"
not_bigger: .string "not bigger than 10"

.text

main:
    enter $0, $0

    mov $prompt, %rdi
    call puts

    mov $long_fmt, %rdi
    mov $num, %rsi
    mov $0, %al
    call scanf

    mov num, %rax

    // (%rax <= 10)
    cmp $10, %rax
    jle small

//else, not less or equal to than ten
    mov $bigger, %rdi
    call puts
    jmp main_done

small:
    mov $not_bigger, %rdi
    call puts

main_done:
    mov $0, %rax
    leave
    ret



