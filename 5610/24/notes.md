
# Web Dev: Semester Wrap-Up

Project questions?

Do TRACE:

 - They help improve the course.

## Next (up to) 4 meetings: Presentations

 - Project is due Sunday
 - Presentation is due Monday
 - Presentation should be 10-15 minutes
 - There are 10 teams and a class meeting is 100 minutes,
   so we should be able to finish presentations in two
   meetings.
 - Presentations will be scheduled in random order, to be announced
   next Tuesday in class.
 - On time attendence is mandatory for all presentation meetings.

## Today: What did we do this semester?

Web development:

What is the web?

 - Collection of web sites
 - Built on top of HTTP
 - Accessed with Web Browsers

What's web dev?

 - Anything involving HTTP or Web Browsers
 - That could really be anything.

What did we cover?

 - Mostly websites
 - Started with a game
   - Realtime view updates in browser
   - Realtime communication with the server
 - Then you built a multiplayer game project.
 - Then we built a CRUD app.
   - Two versions: Multi-page and Single-page
 - Final project is another large application with CRUD elements.

By the end of the semester, you should have at least three interesting apps
deployed on the public internet.

## Administrating Your own Server

 - First thing we did: Deploy your own virtual server
 - You're now prepared to look at Dev Ops.
 - Prepared to evaluate tools like Heroku.
   - Tradeoff: You build applications in a constrained way.
   - Benefit: Heroku automates deployments and handles ops for your
     production server.
 - Prepared to evaluate tools like Amazon AWS.
   - Benefit: Give you some extra capabilities.
   - Tradeoff: Those capabilities are vendor specific, so you're locked in.
 - You can run one or more physical servers if you want. 

## Browser Technology

 - HTML, CSS, JS + DOM
 - Images, Videos, Audio
 - Canvas, WebGL, WebAssembly, etc

## Elixir

 - A functional programming languages
 - Runs on the Erlang VM
 - Reasonable library support for web development

The Erlang VM gives us:

 - Lightweight processes for native concurrency.
 - "Let it crash" for error handling.
 - Unique patterns for state management.
 - Built in clustering support.

Disadvantages:

 - Working in a functional style takes some getting used to.
 - Not quite as popular as languages like PHP, JavaScript, Python,
   or Ruby.
 - Not quite as fast as well-optimized C++, Rust, C#, or Java

Four tiers of performance:

 - Slow: PHP, Python, Ruby
 - Intermediate: (should be slow, but optimized runtime) Elixir, JavaScript
 - Static VM: Java, C#
 - Compile to machine code: C, C++, Rust, Go

Next steps:

 - Go write more web apps as personal projects.
 - Definitely use Elixir / Phoenix / React for more stuff.
 - But, you should also try a bunch of other stuff.
   - Use personal projects as an excuse to try new tools.
   - NodeJS is popular on servers. Try it.
   - Ruby on Rails is like twice as productive as Phoenix for
     traditional stateless apps. Give it a go.
   - It's worth building a project using a low level language
     like C++ or Rust.

## Phoenix

```
request
|> router
|> pipeline
|> controller action
|> view
|> template
```

Neat functionality:

 - Phoenix Channels
 - Ecto + Generators
 - Assets with Webpack

## Webpack, Babel, Extended JS

Babel lets us use variants of JS and CSS:

 - JSX
 - SCSS

Webpack helps package assets in a way that's
useful efficient.

## React

React is an in-browser rendering framework based on the old idea of Functional
Reactive Programming.

 - We have some application state.
 - Rendering is a pure function from state => view.
 - In React, the view is a "Shadow DOM".
 - The real DOM can be efficiently updated from the shadow DOM.
 - When events happen, we update the state and trigger a re-render.

Alternatives to React:

 - React is a rendering library, you can combine it with stuff like
   Redux, React-Router, React-Bootstrap, etc. to "build your own framework".
 - We could use a full framework instead: Angular, Ember
 - If you just want dynamic templating: Vue
 - If you just want templating: moustache / handlebars
 - Another option is Elm: A functional language for the browser that
   goes even harder on FRP than React.

WebSockets:

 - New in the last 5 years.
 - Broad support maybe two years ago.
 - Allows new plan: Server -> browser push updates.
 - In the medium term, I expect this to slowly replace AJAX-style calls.






