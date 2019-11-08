
```
# Same structure as.

# Timesheets.get_timesheet!(id) |> Repo.preload(:tasks)

{
    date: "2019/10/30",
    user_id: 7,
    tasks: [
       {job_code: "777", hours: 4}, 
       {job_code: "787", hours: 2}, 
    ],
}
```


# Lecture 18: Web APIs

Two kinds of API:

 - Browser <=> Server
   - Could be your server.
   - Could be a third party server.
 - (Server or Other) <=> Server
   - A script works the same as an Android app as a
     non-browser API client.

## Common Scenario: REST with JSON endpoints

 - JSON is a reasonable format for transfering arbitrary objects.
   - JSON models (and serializes) the standard in-memory data format
     for common dynamic programming languages.
   - Dynamic languages like JavaScript, Perl, Python, Ruby, Lua, Elixir,
     Clojure.
 - Alternatives: XML, CSV, custom binary format, etc.
 - REST is just a nice consistent convention for accessing resources.

# API Authentication

Two authentication scenarios:

 - You have an account with a provider, you authenticate yourself to the
   provider (e.g. so they can bill you).
 - You have an API account with a provider, but your users also have accounts
   with that provider you allow *users* to authenticate themselves to the
   provider in addition to authenticating your app.

## Just authenticating yourself / your app.

### Plan A: Tokens

 - This could be a crypographic thing like a Phoenix.Token. 
 - It could also just be a big password.
 - As the API user, these cases look the same.

You send this to the server on each request, usually in a header but sometimes
in a field in your submitted data.

Slight variation: JWTs

 - Standardized format for cryptographic tokens.
 - Potentially transparent to the user passing it around.

### Plan B: OAuth (specifically usually OAuth2)

OAuth2 allows a user to delegate access to their account to a third party
service (third party = you).

To the user, it looks like this:

 - You go to the third party service site.
 - You click "login with Github"
 - That link sends you to a Github page, on Github's site.
 - "Third Party Site wants to access your Github account. Ok? Cancel?"
 - Clicking OK brings you back to the third party site, which now
   has access to your account.

To the app, it looks like this:

 - We send the user off to github.
 - They come back on a GET request including a single-use code.
 - We POST to Github, sending the code (and our client ID and secret),
   and get back a token.
   - This is a server <=> server request, the user's browser isn't
     involved.
   - You're passing a client secret - that's a secret.
   - If the user gets your client secret they can impersonate your
     app - hopefully there's no billing to you for your use of the
     service.
   - If you would like some free stuff, check mobile app downloads
     for OAuth2 client secrets.
 - We can make future API requests with the token, using the user's
   delegated access, even if they aren't actively using our app.

## More API complications

 - Some APIs, e.g. Paypal, need to do postback requests.
 - You submit an API request, it doesn't resolve immediately,
   and then the remote server will POST to your server in order
   to announce the result of the earlier request.
 - Can happen with completely unexpected events as well.

Problem: Your development laptop probably doesn't have a public IP.

 - This may require developing / testing on a VPS.
 - If you're doing development, you shouldn't use your deployment
   user. Developing with your main login user (i.e. as you) makes
   sense.

# Browser <=> Server APIs

## Two cases

 - Having your browser code do API requests to your server.
 - Having browser code do requests to external APIs.

## External Authentication from Browser

### Tokens

 - These just don't work.
 - The token is supposed to authenticate your app.
 - But your *users* get to see (and therefore reuse elsewhere) your token.

### OAuth2

 - Can't use a client secret.
 - There's an alternate flow that excludes the secret.

 - User click "auth with provider" link.
 - User approves request on provider page.
 - User is redirected back with a code.
   - This is a full page load that hits your server.
 - Your in-browser JS makes a POST to the provider ot exchange
   the code for an access token.
   - Provider must have correclty configured CORS headers.

## Same-Origin Policy / CORS

Two HTTP APIs:

 * XMLHttpRequest (used by $.ajax in Jquery)
 * fetch

Same-Origin Policy:

 * Browsers only allow unrestricted HTTP requests from JS to
   the same site that provided the page that the JS is running on.
 * "Site" means {hostname, port, protocol}

Requests that potentially violate this are split into two categories:

 * Simple requests: GET, HEAD, and POST of simple forms when there are
   no weird request headers.
 * Preflighted requests: Anything else. This includes most things that are
   expected to cause side effects (e.g. POST of non-form data, DELETE, etc).


Simple request:

 - JS code does GET "http://api.example.com/foo"

Browser sends request, adding Origin header:

```
GET /foo HTTP/1.1
Host: api.example.com
Origin: http://www.example.com:8080
```

Server sends response:


```
HTTP/1.1 200 OK
Content-length: 100
Access-Control-Allow-Origin: http://www.example.com:8080

...
```

```
HTTP/1.1 200 OK
Content-length: 100
Access-Control-Allow-Origin: *

...
```

 
 







