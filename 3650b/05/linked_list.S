.global main
.text

/*
   A LinkedList is one of:
   - 0 (a null pointer), for an empty list
   - The (non-zero) address of a Cell

   A Cell is a struct with two fields:
   - head: A long
   - tail: A LinkedList
*/

cons:
    enter $0, $0
    mov $16, %rdi
    push %rdi
    push %rsi
    call malloc
    pop %rsi
    pop %rdi
    mov %rdi, 0(%rax)
    mov %rsi, 8(%rax)
    leave
    ret

// first
car:
    //enter $0, $0
    mov 0(%rdi), %rax 
    //leave
    ret

// rest
cdr:
    //enter $0, $0
    mov 8(%rdi), %rax 
    //leave
    ret 

/*
(define (sum xs)
    (if (==? xs 0) 
        0
        (+ (car xs) (sum (cdr xs)))))
Variables:
 - xs: %r12
 - (car xs): %r13
*/
sum:
    push %r12
    push %r13
    enter $0, $0
    mov %rdi, %r12

    cmp $0, %r12
    je sum_base

    mov %r12, %rdi
    call car
    mov %rax, %r13 

    mov %r12, %rdi
    call cdr
    
    mov %rax, %rdi
    call sum

    add %r13, %rax 
    jmp sum_done

sum_base:
    mov $0, %rax

sum_done:
    leave
    pop %r13
    pop %r12
    ret


main:
    enter $0, $0

    mov $10, %rdi
    mov $0, %rsi
    call cons

    mov $20,%rdi
    mov %rax, %rsi
    call cons
    
    mov $30,%rdi
    mov %rax, %rsi
    call cons
   
    mov %rax, %rdi
    call sum

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

.data
fmt: .string "sum = %ld\n"

