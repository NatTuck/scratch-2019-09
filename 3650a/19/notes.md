
# Lecture 19: Solutions for Concurrency and Parallelism

Problem: Data races

Solution: Locks

Problem: Deadlocks

Solution: Radically restrict how we write our programs


## Modern programs tend to be logically concurrent

Consider a program:

 - With a GUI
 - That makes / recieves network requests

Sequential program: forced choice one of

 - Listen for a mouse click
 - Listen for a network packet

## We've got multi-core computers now

Even phones come with like 8 cores now.

A workstation with a lot of cores has 128 of them.

If we want to make programs run fast, we need to use those cores.

## Primitives and Abstractions

How do we build the stuff we need to write correct parallel programs?

 - The hardware gives us atomic instructions.
 - The key instruction that lets you do everything
   is atomic-compare-exchange.

## Conditions for a Data Race

 - Multiple threads run concurrently.
 - Shared access to the same location.
 - At least one thread writes.

# Plan A: Eliminate Actual Parallel Execution

Downside: Can't get parallel speedup.

Workaround: Fork and do different things.

Example: JavaScript

# Plan B: Eliminate Shared Data

 * Communicate by message passing.
   - Either the object is *moved*, or we made a copy.

Example language: Go

This solves the data race issue, but makes some algorithms
more complex.


# Plan C: Make shared data immutable

Example language: Rust

 - Rust doesn't just make the data immutable.
 - It uses static analysis to make sure you haven't made any mistakes
   that make it angry.


# Plan D: Ban everything

Example language: Elixir

 - No mutable data, at all.
 - No (observable) shared data, instead we use message passing.

Erlang was developed for reliablity, which means reduancy, which means
a distributed system, which means concurrency & parallelism.

It turns out we needed languages that were good at concurrency, even on single
machines.

 - Erlang syntax is *bad*. You can't call a user defined function in the
   conditoin of an "if" expression - as a syntax rule.
 - Elixir is another language on the VM.



