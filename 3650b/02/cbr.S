// Read in a number typed by the user.
// Figure out if it's greater than 10.

.global main

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
 
    // if (%rax <= 10) goto smaller
    cmp $10, %rax
    jle smaller 

    // bigger
    mov $bigger, %rdi
    call puts

    jmp main_done

smaller:

    mov $not_bigger, %rdi
    call puts

main_done:
    mov $0, %rax
    leave
    ret

.data
num: .space 8
prompt: .string "Enter a number:"
long_fmt: .string "%ld"
eol: .string "\n"
bigger: .string "bigger than 10"
not_bigger: .string "not bigger than 10"

