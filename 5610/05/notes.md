
# React.js

## Rendering HTML programattically

 - Plan A: Templates
 
 ```
    <h1><%= @title %></h1>
    <p><%= @paragraph %></h1>
 ```

 - Plan B: Virtual DOM
 
   - Think about HTML as a tree.
   - Optimal update from old tree to new tree is calculating difference.
   - Data object: The state
     - When the state changes, we render a new HTML tree.
     
 - How to describe content: JSX
   - Embed XML in JavaScript.
   
```
    function foo(name) {
        return (
           <p>Hello there {name}</p> 
        );
    }
    
    function foo() {
       return (
          make_tag('p', {body: "Hello there " + name}); 
       );
    }
```
     
     
     
