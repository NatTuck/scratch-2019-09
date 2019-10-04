
# CS3650: Tokens

## Today's Example: Calculator

```
1 + 2
=> 3
1 + 2 * 3
=> 7
1 + 1+1 + 1
=> 4
3 - 1 * 1
=> 2
9 / 2
=> 4
```

## Steps in an interpreter

 - Tokenize
   - Identify "tokens" in input and split them into a sequence,
     like a list or vector.
 - Parsing
   - Transform sequence of tokens into an "abstract syntax tree".
   - ["1", "+", "2", "*", "3"] => ```(+ 1 (* 3 2))```
 - Evaluation
   - Traverse the AST to produce a value.
 






