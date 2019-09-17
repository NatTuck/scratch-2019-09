# The recipie for programs

 - Figure out some functions you need.
 - Write them.
 - That may add functions.
 - Keep going until done.


# The recipe for a function

 - Signature
 - Pseudocode
 - Variable Mappings
 - Skeleton
 - Write function body
 
# Variable mapping

Where do we put values?

Registers:

 - Is it already an argument? Maybe we can leave it in %rdi, %rsi, %rdx, ...
 - Is this the value we're returning? Maybe %rax
 - Does this value not need to survive function calls? %r8..%r11
 - Does it need to survive function calls? %rbx, %r12..%r15 
 - Keep in mind that %rax, %rdx are extra unsafe - 
   some instrucitons clobber them.

Memory:

 - Is it global? Reference it's label.
 - Is it easier to not allocate a register? 0(%rsp), 8(%rsp), ...
 - Is this in a data structure? Maybe we can figure out that
   since the struct pointer is %rdi, the field we want is 18(%rdi).

## Skeleton

We've got our variables mapped.

```
label:
    push %rbx  // 8 bytes
    push %r12  // 8 bytes
    ... // up to 5 saved registers
    enter $X, $0   // X = 0 if number of saved registers is even
                   // X = 8    "                         is odd

    leave
    pop %r12
    pop %rbx
    ret
```

```enter $X, $0 ``` is

```
    push %rbp
    mov %rsp, %rbp
    sub $X, %rsp
    // waste 8 clock cycles
```

When you call a function:

 - Pushes the return address
 - Jumps to label


```
  // leave does:
  mov %rbp, %rsp
  pop %rbp
```

# Write the body

 - C-ish pseudocode (or C) maps directly 1-(constant) to assembly.
 - Each statement in C can be mapped to a "template" of assembly code.


## Variables, Temporaries, Assignments

```
    long a = 5;
    long b = 3 * a + 1;
```

Variable mapping:

 * a is -8(%rbp)
 * b is -16(%rbp)
 * (3 * a) is %rax

```
  # long a = 5;
  mov $5, -8(%rbp)
  
  # long b = 3 * a + 1;
  mov $3, %rax
  imul -8(%rbp)
  add $1, %rax, -16(%rbp)
```












