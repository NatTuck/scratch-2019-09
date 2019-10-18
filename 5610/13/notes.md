
# First

Project questions.

# Lens Photo Sharing App

Last time:

 - New App
 - Install Bootstrap
 - Deploy!
 - User resource

Resource:

For users, we get a path: "/users"

Variants of that path and HTTP methods let us do seven operations:

 - show
 - create
 - update
 - new
 - index
 - delete
 - edit

 - CRUD


# User Sessions
 
 - Photos belong to users.
 - Users need to log in, so we know which user owns a new photo.

"Sessions" are a resource.

We need three paths:

 - create: To actually log in.
 - delete: To log out
 - new: The log-in form

Don't want to store sessions in the DB. We're going to store them
in a cookie.













