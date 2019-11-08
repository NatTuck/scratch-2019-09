
# Lecture 19: Solutions for Concurrency and Parallelism

 - Want concurrency / parallelism.
 - End up using shared memory.
 - Data races.
 - Solve with locks
 - Deadlock
 - Only solution is coding conventions

## We want concurrency

Consider a GUI app that does network stuff.

At any time, we could:

 - Get a mouse click.
 - Get a network packet.

We can solve this with concurrent programming:

 - One thread handles the GUI
 - Another thread handles the network

## We need parallelism for performance

New phones have like 8 cores (e.g. 4 slow cores + 4 fast cores)

If you get a decent workstation, you're talking more like 128 cores.

If we want performance, we need parallel code.

## What do we have to build on to avoid data race issues?

CPUs give us atomic instructions.

The key one for synchronization is

 - atomic-compare-exchange

## Conditions for a Data Race

 - Multiple threads (or processes) running concurrently.
 - Shared data.
 - At least one process writes.

# Plan A: Concurrency without Parallelism

If we don't run multiple chunks of code in parallel, then they run in *some*
order. We still can have data races, but we can't have data races *within*
chunks of code. Single "tasks" execute atomicly.

Disdvantage: Can still have data races across multiple tasks.
Disavantage: No parallel speedup.

Example: JavaScript

# Plan B: Eliminate Shared Data

Idea: Message passing

 - Don't share objects
 - When one thread is done with an object, it sends it to the other,
   and then only the second thread has a reference to it.

Example would be: Go

# Plan C: Make Shared Data Immutable

Example Language: Rust


# Plan D: Just Ban Everything

Example Language: Elixir

Elixir as a language that run on the Erlang virtual machine.

Erlang's goal: Reliability, Redunancy, Distributed System, Concurrency and
Parallelism

Core ideas:

 - Functional language
 - Concurrent processes
 - Message passing

Erlang is the only language I ever gave up on because its syntax
was so painful.

 - A user defined function cannot be called in the condition of
   an if expression.

