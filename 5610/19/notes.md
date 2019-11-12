
# Web App Performance

 - User Experience: Slow websites are awful.
 - Hosting Cost: Most websites should fit fine on on server. Once you go beyond
   one server, you start having to pay more money for servers. Optimally this
   scales linearly (twice the servers is twice the performance), but linear
   scaling is infinitely worse than constant price (1 server).
 - Scaling: Once you get beyond what one server can do, we'll look at how
   sites scale.

## Performance: User Experience

One key metric: Time to react to user action.

Two cases:

 - Initial page load.
 - Subsequent actions.

Initial page load and bounce rate:

 - Websites that load slowly lose users: they "bounce", simply closing the tab.
 - "Fast" is ~500ms.
 - "Moderate" is ~2 seconds.
 - "Bad" is > 4 seconds.

Subsequent page loads:

 - We want this to take like 10ms.
 - Somewhere around 200ms is where people start thinking interactivity
   is slow.

What contributes to the delay?

 - Network latency for DNS lookup
   - Requires 1 RTT to the DNS server if not cached.
 - Network latency for the initial HTTP request.
   - Requires 1 RTT to setup the TCP link.
 - Time for server to generate the page.
   - Includes internal data processing (e.g. DB requests)
 - Transmission time for the HTML. 
 - Parse time for the HTML.
 - Network latency for the assets (e.g. JS, CSS, Images).
 - Transmission time for assets.
 - Parse time for JS/CSS.
 - Rendering time.

We have three categories of delay here:

 - Network / Bandwidth delay:
   - Mostly we can just control where the server is.
 - Server execution time:
   - We can improve this by improving our program.
 - In-browser execution time:
   - We can tell our users to get better computers. That usually
     goes over poorly.

## How to optimize programs

 - Step 1: Don't do it.
 - Step 2: For experts, don't do it until you've carefully profiled
   and identified the exact problem spot.

--

 - When you're writing code, make sure it isn't obviously slow / inefficent for
   no reason. Pick reasonable algorithms.
 - Then wait until you actually have a performance problem (in execution time,
   memory use, bandwidth, etc).
 - Then measure to find out *what* and *where* your performance problem is.
   - Measuring can be anything from simply adding "time.now()" printouts
     to using a dedicated profiler.
 - Once you've found the problem, try to fix it by optimizing that component.
 - After optimizing, measure to verify that you're helping.

## Content Delivery Networks

 - These companies put datacenters all over the world.
 - You can put parts of your site on their servers to speed up latency
   and data transfer times for nearby users.

CNN loaded from Singapore:

 - DNS lookup: From CDN
 - Initial HTTP request / response: Still to New York.
 - Static asset request / response: From CDN

This can speed up page load by an order of magnitutde. 

One step further: Caching CDN

 - We don't acutally need CNN.com to be up to date to the second.
 - So the CDN can actually serve the initial HTTP request too, from cache.
 - The cache expires periodically, triggering a full requst back
   to the main server.

## Back to last class: Denial of Service Attacks.

Example: Online password cracking attack.

 - Do enough concurrent login requests and our CPUs are spending
   100% of their time on password hashing.

Solution: Limit login requests. Prevent more than 100 logins per hour
per remote IP. After that, we no longer validate passwords sent.

Maybe we throttle *all* requests.

These attacks rely on the attacker finding some expensive operation
to get us to do.

What if they just have more bandwidth than we do?

 - They can saturate our network link.
 - There's nothing we can do about this on our server.
 - We might be able to do something on a router, but not really.

The only good solution is to have a comparable level of bandwidth to the
attacker.

CDNs providing proxy service also provide "DDOS protection".


## Hosting Cost

 - The smallest reasonable server (e.g. a 1GB VPS) can run pretty big apps (e.g.
   10,000 users).
 - VPSes scale up nicely - you can go to 64GB of RAM for 16x the price.
   - That's 100k users for $320/month.
 - Next step up is a rented dedicated server; these cost about the same per
   resource, topping out around 256GB.
 - After that you can get a custom server and colocate it.
   - You can get a 128-core server with 1TB of RAM for \$30,000.
   - Lease on that is \$1000/month + \$200/month for colocation.

You can't easily scale up further than that, which leaves you two choices:

 - Optimize your app.
 - Scale-out to multiple servers.

This tradeoff is non-trivial.

 - Developers cost on the order of \$100k/year, or about 10x as much as
   a high end commodity server.
 - Once you have more than 10 servers, hiring a developer to get a 10%
   performance increase is a good idea.

Two strategies:

 - Small: Optimize for programmer time. These companies love Ruby on Rails.
 - Big: Optimize for machine time. These companies love completely custom
   app stacks written in C++.

## Scaling

Traditional strategy: Stateless web servers.

 - Web servers get requests, talk to the DB, send a response.
 - No state outside the DB.

This lets us replicate our webservers "for free".





