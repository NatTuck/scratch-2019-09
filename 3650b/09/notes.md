
# 3650: Tokens



# An interpreter

 - Tokenize
   - Convert an input string into a sequence (e.g. list or vec) of strings.
 - Parse
   - Convert the sequence of tokens into an abstract syntax tree (AST).
   - Example: "1 + 2 * 3" => ```(+ 1 (* 2 3))```
 - Evaluate
   - Convert the abstract syntax tree into a value.
   -  ```(+ 1 (* 2 3))``` => 7

Our example: A simple arithmetic expression calculator

```
1 + 1
=> 2
1+1
=> 2
10 - 5 * 2
=> 0
9 / 2
=> 4
```



