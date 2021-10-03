### Interpreter

- Revolves around turning strings into OOP based structures in a complicated processs

Interpreter: A component that processes structured text data. Does so by turning it into separate lexical tokens (lexing) and the interpreting sequences of said tokens(parsing).

### Summary

- Barring simple cases, an interpreter acts in two stages
- Lexing turns text into a set of tokens e.g. "3*(4+5)" -> Lit[3] Start Lparen Lit[4] Plus Lit[5] Rparen
- Parsing tokens into meaningful constructs :
```
-> MultiplicationExpression[
    Integer[3],
        AdditionExpression[
            Integer[4], Integer[5]
        ]
]
```
- Parsed data can then be traversed