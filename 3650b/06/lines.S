// lines.S: read "msg.txt", count lines (= '\n') in it, print result
.global main

.text

main:
    push %r14    // fd
    push %r15    // size of file contnets
    enter $256, $0
    // 0(%rsp) is text buffer
    // 192(%rsp) is sprintf buffer

    // count length of intro message
    mov $intro, %rdi
    call strlen

    // print intro message
    mov $1, %rdi // stdout
    mov $intro, %rsi // intro msg
    mov %rax, %rdx
    mov $1, %rax // write
    syscall

    // open the file
    mov $file, %rdi  // file name 
    mov $0, %rsi     // flags
    mov $0, %rdx     // mode
    mov $2, %rax     // open
    syscall
    mov %rax, %r14

    // read whole file into buffer
    mov %r14, %rdi      // fd
    lea 0(%rsp), %rsi   // buffer ptr
    mov $192, %rdx      // buffer size
    mov $0, %rax        // read syscall
    syscall
    mov %rax, %r15  // bytes in file

    // loop through the buffer, counting newlines
    mov $0, %rcx
    mov $0, %rdx
loop_cond:
    cmp %r15, %rcx
    jge loop_done

    mov $0, %rax
    mov (%rsp, %rcx, 1), %al

    cmp $'\n', %al
    jne loop_next

    inc %rdx

loop_next:
    inc %rcx
    jmp loop_cond
loop_done:

    lea 192(%rsp), %rdi
    mov $fmt, %rsi
    // rdx is already count
    mov $0, %al
    call sprintf 

    // print the count
    mov $1, %rdi
    lea 192(%rsp), %rsi
    mov %rax, %rdx
    mov $1, %rax
    syscall
   
    // exit
    mov $0, %rdi
    mov $60, %rax
    syscall

/*
    mov $0, %rax 
    leave
    pop %r15
    pop %r14
    ret
*/

.data
intro: .string "counting lines in msg.txt...\n"
file: .string "msg.txt"
fmt: .string "lines = %ld\n"
