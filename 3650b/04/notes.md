
# 3650 lecture 4 Notes

# Recipie for an assembly program

 - Figure out at least one function you need.
 - Write all the functions you need, expecting to
   find more as you go.

# Recipe for a function

## Signature

 - Write down names and types for arguments.
 - Type of return value.
 - Name of function

## Pseudocode

 - Thinking in ASM is hard.
 
## Variable Mapping

Explicitly write down where each value produced/used in the function
is stored.

Registers:

 - Is is already in an argument register? %rdi, %rsi, %rdx, ... 
 - Do we want to return this? %rax
 - Is this a temporary that doesn't need to survive function calls?
   %r8, %r9, %r10, %r11
 - Does it need to survive a function call?
   %rbx, %r12-%r15
 - Keep in mind that instructions can clobber %rax, %rdx

Memory:

 - Is it a global? Reference by label.
 - On the stack? We can allocate extra slots 0(%rsp), 8(%rsp), ...
   Every +16 to $X in enter adds two slots.
 - Is this part of a data structure? 8(%rsi), 18(%rcx)

## Skeleton

```
label:
    // any time we've mapped a safe register, save it here.
    push %rbx // each push uses 8 bytes
    push %r12
    ...
    enter $X, $0 // if push even number of regs, X = 0
                 // otherwise, X = 8

    leave
    ...
    pop %r12
    pop %rbx
    ret
```


```
  // enter $X, $0 is the same as
  push %rbp
  mov %rsp, %rbp
  sub $X, %rsp
  // waste 8 clock cycles
```

```
  // leave is
  mov %rbp, %rsp
  pop %rbp
```

## Write the Body

 - There is a 1:1 (or 1:small constant) mapping between C
   and assembly code.
 - Every C statement (e.g. "if", "while") can be translated by
   filling in an ASM "template".
 
### Example: Variable assignments

```
int a = 5;
int b = 3 * a + 1;

// Variable mapping
//  - a is %rax
//  - b is %rax
//  - (3 * a) is %rax
//  - %r9 is 3
```

```
  # int a = 5;
  mov $5, %rax
  
  # int b = 3 * a + 1;
  mov $3, %r9
  imul %r9
  add $1, %rax
```


