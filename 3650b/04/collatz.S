.global main
.text
//#include <stdlib.h>
//#include <stdio.h>

// Collatz Conjecture
//  - start with a number
//  - if it's even, take n/2
//  - if it's odd,  take 3*n+1
//  how many times repeat before get to 1?


/*
long
iterate(long x)
{
    if (x % 2 == 0) {
        return x/2;
    }
    else {
        return 3*x + 1;
    }
}

// Variable mappings:
// - x is %rdi
// - 2 is %r9
// - 3 is %r10
// - x%2 is %rdx
// - x/2 is %rax
// - 3*x is %rax
// - 3*x + 1 is %rax
*/

iterate:
    enter $0, $0
   
    mov %rdi, %rax 
    mov $2, %r9
    cqo
    idiv %r9

    //if (x % 2 == 0) {
    cmp $0, %rdx
    je iterate_then

iterate_else:
    //    return 3*x + 1;
    mov $3, %r10
    mov %rdi, %rax
    imul %r10
    add $1, %rax

iterate_then:
    // return x/2;
    // value already in %rax

    leave
    ret

/*
int
main(int argc, char* argv[])
{
    long x = atol(argv[1]);

    long i = 0;

    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }

    printf("i = %ld\n", i);
    return 0;
}
// Variables:
//  - argc is %rdi
//  - argv is %rsi
//  - x is %rbx
//  - i is %r12
//  - "%ld\n" is fmt
//  - "i = %ld\n" ifmt
*/

main:
    push %rbx
    push %r12
    enter $0, $0

    //long x = atol(argv[1]);
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rbx

    //long i = 0;
    mov $0, %r12

    //while (x > 1) {
main_loop:
    cmp $1, %rbx
    jle main_loop_done

    //    printf("%ld\n", x);
    mov $fmt, %rdi
    mov %rbx, %rsi
    mov $0, %al
    call printf

    //    x = iterate(x);
    mov %rbx, %rdi
    call iterate
    mov %rax, %rbx

    //    i++;
    add $1, %r12
    
    //}
    jmp main_loop

main_loop_done:

    //printf("i = %ld\n", i);
    mov $ifmt, %rdi
    mov %r12, %rsi
    mov $0, %al
    call printf

    //return 0;
    mov $0, %rax

    leave
    pop %r12
    pop %rbx
    ret 

.data
fmt: .string "%ld\n"
ifmt: .string "i = %ld\n"
