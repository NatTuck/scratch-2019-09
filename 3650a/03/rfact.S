
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

    call fact

    mov $fmt, %rdi
    mov %rax, %rsi
    mov $0, %al
    call printf

    mov $0, %rax
    leave
    ret

fact:
    push %rbx
    enter $8, $0
    
    // long fact(long xx) // xx = %rdi, 
    //  if (xx == 1) { 
    //    return 1;
    //  }
    cmp $1, %rdi
    je ret1

    //  else {
    //    return xx * fact(xx - 1);
    //  }
    mov %rdi, %rbx
    sub $1, %rdi
    call fact

    imul %rbx
    jmp done

ret1:
    mov $1, %rax

done:
    leave
    pop %rbx
    ret
