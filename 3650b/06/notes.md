
# In C, local variables go on the stack

```
void
foo()
{
    long nn;
    
    // lea 8(%rsp), &r10
    long* nnp = &nn;
   
    // mov 8(%rsp), %r9
    long mm = nn;
}

Variable mapping:
  - nn is 8(%rsp)
  - mm is %r9
  - nnp = %r10


```

# System Calls

 - put arguments in %rdi, %rsi, ...
 - put syscall # in %rax
 - "syscall"
 - result in argument buffers / %rax

# Default file descriptor

 - 0 = stdin
 - 1 = stdout
 - 2 = stderror
 









