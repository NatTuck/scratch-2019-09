URL: proto (http) host (inkfish.ccs) path (/)

HTTP/1.0

Problems:

 - Only GET, POST
 - No way to host multiple sites/server
 - No way to recognize returning users / do user sessions.
 
HTTP/1.1 (port 80)

 - Adds some more methods (e.g. PUT, DELETE)
 - Adds "Host" header to specify which site to view.
 - Add Cookies. 
   - Cookies are a header containing key-valuepairs sent from 
     the server to the client.
   - When the browser makes another request to the same site, it
     sends back those cookies (unmodified).

SSL / TLS: (port 443)

 - Add encryption / authentication to HTTP = HTTPS
 - Current version is TLS 1.2, old versions horribly broken.
 
HTTP/2.0
 
 - Binary
 - Concurrent reqs
 
Websockets

 - Allows TCP connections to be set up from an HTTP connection.
 - Lets servers push data to clients.

HTML - HTML5

CSS - reasonably stable for a while now

JS - ES5 2011, ES6 2015


## JavaScript

 - Designed in two weeks in 1995 by a guy named Brandon Eich.
 - As different from Java as a language can be while still having curly braces.
 - Dynamically typed.
 - Hash oriented.
 - Prototype based object model.
 - Provides decent support for functional style.
 



