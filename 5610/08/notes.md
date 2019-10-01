

Plan A: Browser-Only

 - State is in the browser.
 - Users can play the game with no network traffic or server resources.
 
Problems:

 - State is lost if user closes the browser window.
 - User actually controls state and code.
 - Can't be multi-user because the state is stuck in that
   user's browser.


Plan B: Server-Side State
 
 - User needs network connection to play.
 - Takes server resources.

Plan B.1: State is associated with transient connection.

 - State is lost if user closes browser window.
 - Any crash in server code loses state.
 - Still difficult to have multiple users. 

Plan B.2: State is stored outside the connection.
 
 - Problem: Where do we put it?
 - This is a hard problem in general.
 - In Elixir, we don't have mutable variables, especially
   not mutable globals.
 - Elixir has some (actually a ton) of mechanisms for managing
   this sort of state.
 - We're going to look at the simplest one: Spawn a single dedicated
   process to store game states.

## Agents

 - An agent is a process that runs as part of our app
 - It manages a piece of state.
   - Conceptually, it simulates a mutable global variable
 - The agent provides an interface to get / update the state.
 - The agent guarantees sequential access to the state object.


## Backup Agent

Advantages:

 - We don't lose game states.
 - If a single connection / game crashes, we lose no states.

Disadvantages:

 - Scaling bottleneck


## Multiple state processes

 - We could have a backup agent *per game*.









