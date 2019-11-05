
# SPAs, Part II

## User Registration and Sessions

 - We're skipping registration.
 - Sessions are a little more interesting.

Option 1: Use Phoenix sessions and cookies

 - User submits username and password via AJAX.
 - We retrieve user and validate password.
 - Use put\_sessoin to set a cookie
 - That sends a set-cookie header.
 - Logout requires a DELETE request to the server.

This works great, Phoenix + the browser handle the hard bit.

Option 2: Use a secure token.

 - User submits login form.
 - We retrieve user and validate password.
 - We generate a secure session token Phoenix.Token module.
 - Send the token back to the client-side code.
 - Client side code sends token on future requests.
 - Logout is just the browser code forgetting the token.
 
Some advantages to tokens:

 - The browser code can be a separate application from the server code,
   maybe even hosted on a different domain.
 - The client doesn't even need to be in the browser. It could be an
   Android app.
 - You can even do both with the same API.

localStorage methods:
 
 - setItem("key", String);
 - getItem("key");
 - removeItem("key");
 - clear();

