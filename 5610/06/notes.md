
# Code organization in React

Root component:

 - Application state
   - Methods to view and update that state
 - Root render method
   - This should delegate quickly to stateless subcomponents.

# Server Side Logic

- Problem 1: Secret Word
  - This is part of our applicaiton state.
  - If it's in our *react* state, it's in the browser - that's not really
    secret.
  - We can move our state to the server.
- Problem 2: Concurrency and distribution
  - If we have multiple versions of the state (sources of truth)
    we can have conflicts.
  - If we have concurrent updates, that allows race conditions.
  - The server can be our single source of truth.
- Problem 3: Cheating
  - Game logic needs to run on our machine.
  
# Our plan:

 - Move app state from root React component to server.
 - Implement rules in Elixir module.
 - When an input happens, send to server.
 - Server updates game state, sends back info.
   - Minimum amount of information nessisary for
     - The view to be rendered.
     - The user to be able to take actions.
   - So we send a "state view" for the user.
 - We want server to be able to initiate messages
   (send view even if not in response to user actions)
   - We'll use websockets

# Phoenix Channels

 - Provides an API for message passing over websockets.
   - Messages are a string tag and a JS object body.
 - Libraries are provided by default with Phoenix for both
   Elixir and JS sides.









