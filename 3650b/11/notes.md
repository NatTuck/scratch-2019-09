
# Shell Assignment Strategy

 - Tokenize
     (Big string => List of Strings)
 - Parse
     (List of Strings => Abstract Syntax Tree)
 - Evaluate
     (AST => [Behavior])

## Cases

### Simple Command

```
    command1
    command1 arg1 arg2 arg3
```

Steps:

 - fork
   - in child, eval
 - wait on child
 - exit code is result from waitpid
 
### Case: builtin command

```
    exit
```

 - Just do that.

### Operator: ';'

```
    command1 ; command2
```

Steps:

  - eval command1
  - eval command2
  - Exit code is the result of command2

Problem:

```
    exit; echo one
```


### Operator: "||" 

Example:

```
    false || echo one
    command1 || command2
```

 - Eval command1
 - If result is non-zero, eval command2
 - Exit code is result of command1 if successful, else command2.

### Operator: "&&" 

```
    true && echo one
    command1 && command2
```

 - Eval command1
 - If result is zero, eval command2
 - Exit code is result of command1 if unsuccessful, else command2

### Operator: "&"

```
    command1 &
    command1 & command2
```

 - fork
   - eval command 1 in child
 - don't wait
 - eval command 2 (if any)

### Operator: ">"

```
    command1 > file
```

 - fork
   - in child
   - open file
   - replace stdout with file
   - eval command
 - wait on child
 
### Operator: "<"

```
    command1 < file
```

- fork
   - in child
   - open file
   - replace stdin with file
   - eval command
 - wait on child
 
### Operator: "|"

```
    command1 | command2
```

- fork
 - make a pipe
 - fork
   - close read end of pipe
   - replace stdout with write end of pipe
   - eval command1
 - fork
   - close write end of pipe
   - replace stdin with read end of pipe
   - eval command2 
 - wait for first child
 - wait for second child; that's our exit code
- wait for outer child






 
 
