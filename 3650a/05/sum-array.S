.global main

.text

/*
long
sum_array(long* xs, long nn)
{
    long sum = 0;
    for (long ii = 0; ii < nn; ++ii) {
        sum = sum + xs[ii];
    }
    return sum;
}
Mapping:
 - xs: %rdi
 - nn: %rsi
 - sum: %rax
 - ii: %rcx
*/

sum_array:
    enter $0, $0

    //    long sum = 0;
    mov $0, %rax

    //    for (long ii = 0; ii < nn; ++ii) {
    mov $0, %rcx
sum_loop:
    cmp %rsi, %rcx
    jge out_of_the_loop

    //      sum = sum + xs[ii];
    add (%rdi,%rcx,8), %rax    

    //    }
    add $1, %rcx   // or inc %rcx
    jmp sum_loop 

out_of_the_loop:
    //return sum;

    leave
    ret


/*
int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("usage: ./sum_array N");
        return 1;
    }

    long nn = atol(argv[1]);
    //long* xs = malloc(nn * sizeof(long));
    long* xs = alloca(nn * sizeof(long));

    for (long ii = 0; ii < nn; ++ii) {
        int count = scanf("%ld", &(xs[ii]));
        if (count != 1) { abort(); }
    }

    printf("sum = %ld\n", sum_array(xs, nn));

    //free(xs);
    return 0;
}
Mapping:
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
     if (argc != 2) {
        puts("usage: ./sum_array N");
        return 1;
    }
    */
    cmp $2, %rdi
    jne bad_output

    // long nn = atol(argv[1]);
    // long* xs = alloca(nn * sizeof(long));
    
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %rbx

    mov %rbx, %rdi
    imul $8, %rdi, %rdi

    // alloca
    sub %rdi, %rsp
    mov %rsp, %r12

    // force stack to be aligned reguardless of current value
    mov $15, %rcx
    not %rcx
    and %rcx, %rsp


    //for (long ii = 0; ii < nn; ++ii) {
    //    int count = scanf("%ld", &(xs[ii]));
    //    if (count != 1) { abort(); }
    //}
    mov $0, %r13
main_loop: 
    cmp %rbx, %r13
    jge main_loop_done
    
    mov $longfmt, %rdi
    lea (%r12,%r13,8), %rsi
    mov $0, %al
    call scanf

    cmp $1, %rax
    jne abort_now

    inc %r13
    jmp main_loop

main_loop_done: 
    
    //printf("sum = %ld\n", sum_array(xs, nn));
    mov %r12, %rdi
    mov %rbx, %rsi
    call sum_array

    mov $outfmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    jmp main_done

abort_now:
    call abort

bad_output: 
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
usage_msg: .string "usage: ./sum_array N"
longfmt: .string "%ld"
outfmt: .string "sum = %ld\n"
