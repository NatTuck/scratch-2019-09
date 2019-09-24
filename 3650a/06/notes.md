
# CS3650 Lecture 6

## HW

```
void foo() {
  long aa;
  
  // mov 8(%rsp), %rax
  long bb = aa;
 
  // lea 8(%rsp), %rax
  long *bb = &aa;
}

/*
Variable mapping:
  - bb can be a register, %rax
  - aa can't be a register. why?
  - aa should be, e.g., 8(%rsp)
*/


mov (%r14,%r13,8), %rsi
%rsi = load 8 bytes from (%r14 + 8 * %r13)


```



## System Calls

Access to operating system services, like I/O is done using the
"syscall" instruction.

Process of doing a system call:

 - Put syscall # in %rax
 - Put args in arg registers
 - "syscall"

Standard file descriptors:

 - 0 stdin
 - 1 stdout
 - 2 stderr













