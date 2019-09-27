
# Web Dev


## First: Functional Programming Concepts Review

What is functional progrmaming?

 - A programming style.
 - Other styles include: Object Oriented, Procedural, Logic, etc
 - Languages can be style-specific, or enable multiple styles:
   - Java is an OO language.
   - Elixir is a functional language.
   - JavaScript is a "multi-paradigm", or "multi-style" language.
   
Constraints in programming:

 - First style: Structured programming
   - You should use explicit loops, rather than doing "goto" everywhere.
   - You shouldn't jump from one function to another.
 - Another style: Memory-safe code
   - We shouldn't have access to raw pointers except in exceptional cases.

```
function foo() {
   let xs = [1,2,3,4];
   bar();
   console.log(xs);
}
```

 - Another style: Object Oriented
  - behavior (methods) is associated with data
  - This allows access boundries to be enforced.
  - A "private" field in Java can only be accessed by code in the same
    class, usually in the same file.
  - This lets us enforce invariants easily.

 - Another style: Functional programming
  - The basic operation is transformation of data values. 
  - One core constraint:
    - Isolate side effects.
    - Secondary effect of that: No mutable data. 

Side effect:

 - A statemement in your code that does something that's visible
   outside the current function.
   - Printing to the console.
   - Mutating a global variable.
   - Mutating an object that other parts of the program hold a refernce to.
   - Making a network connection.
   - Changing the current HTML DOM tree.
 - Can't completely eliminate side effects.
 
"Pure Functions":

 - Pure functions don't access global / external state.
 - Pure functions have no side effects.
 - That means that pure functions must simply perform some calculation
   on their parameters to produce a return value.

Benefits of pure function:

 - Every pure function can be reasoned about seperately.
   - Other parts of the code don't break them.
   - They don't break other parts of the code.
 - Automated testing for pure functions is easy - all we need to do
   is verify the produce the right output for a given set of inputs.

```
// global variable
var numbers = [1,3,4,2];

// Our goal:
//  - Append a number, vv, to the arry.
//  - Then sort the array.
//  - Then print it.
//  - We actually want to do this to the global variable.


// procedural style
function append_sort_and_print(vv) {
    numbers.push(vv);  // side effect: mutate global
    numbers.sort();    // side effect: sorts in place
    console.log(numbers);
}

// functional style

// pure function does the computatoin
function append_and_sort(xs, vv) {
    let ys = xs.concat([vv]);  // produces a new array
    ys.sort();    // We're mutating a local varible
                  // this is a side effect, but not externally visible
    return ys;
}

// side effects are isolated
function append_sort_and_print(vv) {
    let ys = append_and_sort(numbers, vv);
   
    // Here's our side effects
    numbers = ys;
    console.log(numbers);
}
```

# Functional Programming with React

React is a rare beast: A very popular mainstream library resulting from at the
time esoteric programming language research.

React is based on this research concept called "functional-reactive programming"
or FRP.

In a game engine, generally we work from a model of the current game state and
then render it to graphical frames at 60 Hz.

Rendering can be accomplished as a pure function: (game state) => one frame

Complication: Stuff happening.

There are two kinds of events in Pong:

 - Player moves paddle (which player, up or down)
 - Time passes "tick event", (dt)
 
Event handlers are pure functions of (old state, input data) => new state


## FRP and React

We're writing one stateful react component.

Your job in building that is to write a couple of methods, these are
logically pure functions:

 - render (state) => DOM tree

For each event (user clicks a kind of button, time passes, recieved network
message):

 - event handler: (state0, event info) => state1

Getting real pure functions:

```
render() {
    return pure_render(deepCopy(this.state));
}

onEvent(ev) {
    let data = read_event_data(ev); // values, not DOM references
    let state1 = pureOnEvent(deepCopy(this.state), data);
    this.setState(state1);
}
```

React relies on objects that are part of the state not being mutated.



















