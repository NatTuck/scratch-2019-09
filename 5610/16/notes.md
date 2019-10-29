
# Single Page Applications

Traditional applications:

 - Two types of action: Submit form, click link
 - Both cause a full page reload
 
This has some downsides:

 - You need to watch the page reload - definitely a blank
   white screen or a loading bar or something happens.
 - Most client-side state is lost.

Alternative: SPAs

 - Don't do real page loads.
 - Data from the server is fetched by AJAX APIs (or, now, websockets).
 - Generally we simulate the normal look and feel of a multi-page site
   using JavaScript.

Why?

 - We get better control over the user experience.
   - e.g. page transitions
 - SPAs can feel (or sometimes even, be) faster.
   - Especially if we can cache local data in some application
     specific way.

Why not?

 - SPAs are generally slower on first load than traditional web pages.
 - SPA frameworks exist, but the culture tends to focus on customizability,
   so you frequently need to do things by hand.
 - It's easy to break the back button and other stock browser UI.
   - This can be fixed by hand or with libraries.

## Initial Version

 * Pages are simulated - entirely in browser.
 * That means that our current path is part of the application state.
 * We're using React-Router, so
   * We're going to store the path in the URL bar.

## Resources

Bad plan: We're going to put photos in the DB.

Benefit: No need to worry about separate files or insert atomicity.

Base64 means 133% of normal size.


## Redux

 - Previously, app state went in root component.

With Redux:

 - Our single state object goes into an object called the store.
 - We build code following a pattern for updating that state based
   on events.
 - State should still be immutable, but the redux pattern helps us
   manage that.
 - The react-redux library feeds pieces of our state into our react
   components, avoiding threading state through in props.













 
