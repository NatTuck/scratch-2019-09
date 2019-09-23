.global main
.text

/*
long
sum_array(long* xs, long nn)
{
    long result = 0;
    for (long ii = 0; ii < nn; ++ii) {
        result += xs[ii];
    }
    return result;
}
Mapping:
  - xs: %rdi
  - nn: %rsi
  - result: %rax
  - ii: %rcx
*/

sum_array:
    enter $0, $0

    //long result = 0;
    mov $0, %rax

    //for (long ii = 0; ii < nn; ++ii) {
    mov $0, %rcx
sum_loop:
    cmp %rsi, %rcx
    jge end_of_the_loop 

    //    result += xs[ii];
    add (%rdi,%rcx,8), %rax 

    add $1, %rcx
    jmp sum_loop
    //}
    //return result;
end_of_the_loop:
    leave
    ret

/*
int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Usage: ./sum_array N");
        return 1;
    }

    long nn = atol(argv[1]);
    long* xs = malloc(nn * sizeof(long));

    for (long ii = 0; ii < nn; ++ii) {
        int count = scanf("%ld", &(xs[ii]));
        if (count != 1) { abort(); }
    }

    printf("sum = %ld\n", sum_array(xs, nn));

    free(xs);
    return 0;
}
Mappings:
 - argc: %rdi
 - argv: %rsi
 - nn: %rbx
 - xs: %r12
 - ii: %r13
 - count: %rax
*/

main:
    push %rbx
    push %r12
    push %r13
    enter $8, $0

    /*
    if (argc != 2) {  // argc = %rdi
        puts("Usage: ./sum_array N");
        return 1;
    }
    */
    cmp $2, %rdi 
    jne give_up

    /*
    long nn = atol(argv[1]); // argv = %rsi, nn = %rbx
    long* xs = malloc(nn * sizeof(long)); // xs = %r12
    */
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rbx
     
    mov %rax, %rdi
    imul $8, %rdi

    // alloca
    sub %rdi, %rsp
    mov %rsp, %rax

    // force stack alignment
    mov $15, %rcx
    not %rcx
    and %rcx, %rsp

    //call malloc
    mov %rax, %r12

    /*
    for (long ii = 0; ii < nn; ++ii) { // ii = %r13, nn = %rbx
        int count = scanf("%ld", &(xs[ii])); // xs = %r12, count = %rax
        if (count != 1) { abort(); }
    }
    */
    mov $0, %r13
main_loop: 
    cmp %rbx, %r13
    jge end_of_main_loop 

    mov $longfmt, %rdi
    lea (%r12,%r13,8), %rsi
    mov $0, %al
    call scanf

    cmp $1, %rax
    jne explode

    inc %r13
    jmp main_loop
  
end_of_main_loop:

    //printf("sum = %ld\n", sum_array(xs, nn)); xs = %r12, nn = %rbx
    mov %r12, %rdi
    mov %rbx, %rsi
    call sum_array 

    mov $sumout, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf 

    //mov %r12, %rdi
    //call free
    
    mov $0, %rax
    jmp main_done

explode:
    call abort

give_up:
    mov $usage_msg, %rdi
    call puts
    mov $1, %rax

main_done:
    leave
    pop %r13
    pop %r12
    pop %rbx
    ret


.data
usage_msg: .string "Usage: do it right"
longfmt: .string "%ld"
sumout: .string "sum = %ld\n"
