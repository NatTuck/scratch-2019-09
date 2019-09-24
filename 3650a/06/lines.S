/* lines.S: Read a file called "msg.txt", count lines ("\n") in it, print result */

.global main
.text

main:
    push %r14 // fd
    push %r15 // # of bytes read from input file
    enter $256, $0
    // 0(%rsp) is the buffer

    // calculate length of message
    mov $intro, %rdi
    call strlen
    mov %rax, %rdx

    // print intro msg
    mov $1, %rax     // write syscall
    mov $1, %rdi     // stdout
    mov $intro, %rsi  // buf
    syscall
 
    // open file
    mov $file, %rdi   // file name
    mov $0, %rsi      // flags: READ_ONLY
    mov $0, %rdx
    mov $2, %rax   // syscall = open
    syscall
    mov %rax, %r14   // %r14 is fd

    // read content of file into buffer
    mov %r14, %rdi
    lea 0(%rsp), %rsi 
    mov $192, %rdx
    mov $0, %rax     // syscall = read
    syscall
    mov %rax, %r15

    // loop, to count newlines
    mov $0, %rcx
    mov $0, %rdx
loop_cond:
    cmp %r15, %rcx
    jge loop_done

    mov $0, %rax
    mov (%rsp,%rcx,1), %al

    cmp $'\n', %al
    jne loop_next

    inc %rdx

loop_next:
    inc %rcx
    jmp loop_cond
loop_done:

    // print the number
    lea 192(%rsp), %rdi
    mov $fmt, %rsi
    // count is already in rdx
    mov $0, %al
    call sprintf

    mov $1, %rdi   // stdout
    lea 192(%rsp), %rsi
    mov %rax, %rdx // number of bytes sprintf wrote
    mov $1, %rax   // write
    syscall

    // exit
    mov $0, %rdi
    mov $60, %rax // exit
    syscall
  
    leave
    pop %r15
    pop %r14
    ret 



.data
intro: .string "lines in msg.txt\n"
file: .string "msg.txt"
fmt: .string "lines = %ld\n"
