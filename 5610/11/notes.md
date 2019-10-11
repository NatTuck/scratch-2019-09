
# Web Dev: Web Assembly

## Running Code in the Browser

### Java Applets

 - May, 1995
 - Allowed java archives to be embedded in a web page
 - Ran in a sandbox for security
 - Integrated into browser through a plugin

### JavaScript

 - September, 1995
 - Scripting language interpreted directly by the browser itself.

### Going forward from three

 - Over the next 20 years these were the options
   - JavaScript
   - Plugin: Java applets got replaced by Flash

## Native Code in the Browser

Story starts in 2010

### NACL

First team, at Google, released NACL in 2011.

 - Created a new platform that C/C++ compilers could target.
 - Subset of 32-bit x86 machine code called NaCL
 - Had a standard library that was basically desktop Linux
 - Could be easily sandboxed by static analysis
 - Problem: Only works on hardware that natively executes x86 code.

### asm.js

Second team, at Mozilla, released ASM.js is 2013.

 - Created a new platform that C/C++ compilers could target.
 - A subset of JavaScript
 - Subset specifically designed to:
   - Be a good compiler target
   - Be easy to optimize for the existing JavaScript JIT compilers

```
     let foo = 45|0;
```

 - Disadvantage: Weird

## Why not just write JavaScript

 - C code is potentially faster
   - C can manipulate memory and we can use optimal memory
     layouts.
   - No calls to the garbage collector


### WebAssembly

 - A binary code format that can run in web browsers.
    - Kind of like Java byte code, but designed to very efficiently
      JIT to machine code.
    - An associated assembly language is provided.
 - There's already a JIT, the JS JIT, so it's specified to use
   an easily modified version of that.
 - Runs compiled native code in the browser with usually not more than a 20%
   speed penalty over running native code directly.
   - Exceptions: Vector instructions, threads
 - For code that cares about memory layout, this can be 2-5x faster than JS.

Quake demonstrated two things:

 - Graphically / computationally intensive programs.
 - The ability to recompile existing C/C++ programs for the browser.

Two more things to consider:

 - Web app frontends don't need to be written in JavaScript.
 - Web app fonntends don't need to be written in HTML / CSS.




















