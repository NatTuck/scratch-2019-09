
# 3650: There's a Challenge Assignment

## Building The Shell

Basic plan for an interpreter:

 - Tokenize
     (Big string => Array of Strings)
 - Parse
     (Array of Strings => Abstract Syntax Tree)
 - Evaluation
     (Abstract Syntax Tree => Behavior)

### Behavior:

Base case: Built in command

```
    exit
```

 - call exit


Base case: Simple command

```
    command arg1 arg2
```

Execution sequence:

 - fork
 - in child: exec(command, [..., arg1, arg2])
 - in parent: wait on child - wait determines exit code of command


Semicolon case:

```
    command1 ; command2
```

Execution sequence:

 - First eval command1
 - Then eval command2


AND / OR case:

```
    true && echo "one"
    true || echo "two"
```

Execution sequence (OR):

 - eval command1
 - get exit code from wait
 - if exit code nonzero then eval command2

AND:

 - eval command1
 - get exit code from wait
 - if exit code is zero then eval command2
 

Background case:

```
    command1 &
    command1 & command2
```

Single argument case:

 - Fork
   - In child eval command1
   - Make sure child exits
 - Don't wait.

Two argument case:

 - Fork
   - In child eval command1
   - Make sure child exits
 - Don't wait
 - In parent: eval command 2
 
Redirect Out:

```
    command1 arg > file
```

 - fork
   - in child: close stdout
   - in child: open file as fd 1
   - eval command1
   - exit child
 - wait in parent for child

Redirect in:

```
    command1 arg < file
```

 - fork
   - in child: close stdin
   - in child: open file as fd 0
   - eval command1
   - exit child
 - wait for child

Pipe:

```
    command1 | command2
```

 - fork
   - open a pipe
   - fork
     - in child, close stdout
     - close pipe input
     - replace fd 1 with pipe output
     - eval command1
     - exit extra children
   - fork
     - close stdin
     - close pipe output
     - replace fd 0 with pipe input
     - eval command2
     - exit extra children
   - wait on both of child's children
   - exit
 - wait on child
   




 
