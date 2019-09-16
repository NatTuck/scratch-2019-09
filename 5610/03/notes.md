

# Question: Why use a given language?

 - Language makes things easier for some task, either due
   to built in language features, libraries, or frameworks.
 - Performance (runtime property more than language, but...)
 - Good interoperability with other things we're using.
 - Security implications (not C for no buffer overflows).
 - Community / Documentation
 - Ease of use / development time
 - #1: You already know it and can't be bothered to learn anything
   else.

# Sequential & Concurrent Programming

 - Innate to web dev.
 - Eventually runs into locking issues.
 
# Elixir

 - Erlang
 - Primary goal: Reliability, implemented with hardware redundancy.
 - Hardware redundancy implies concurrency.
 - Lightweight processes
   - Isolated from each other
   - Communicate by message passing
 - "Let it crash"
 - Erlang syntax: Calling a user defined functoin from the condition
   of an if expression is a *syntax error*.
   
# What is this language?

Stuff Fundies 1 students recognize:

 - Functional language
   - Can't mutate data.
   - To create a new value, need to make a new object.
   - First class functions.
 - Linked list as core data type.
 - No loop statements.
   - Instead we have standard "loop functions": map, filter, reduce
 - Interactive REPL

Stuff they don't:

 - Separate function / variable namespaces.
 - Modules
 - Pattern matching
 - Side effects (like I/O)
 - Map data type
 - Processes, send/recive. 
 
 
 


   

