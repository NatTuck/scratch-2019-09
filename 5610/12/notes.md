
# Web Dev Lecture 12: Boring Apps

The project, and our previous assignments, have some properties:

 - Dynamic view updates.
 - Multiple simultaneous users.
   - Any user can trigger a state change and trigger a display
     update, even for other users.
 - Realtime interaction
 - Ephemeral server-side state - data is lost when server reboots.

I think apps like this are especially interesting, but most apps look
a bit different.

Consider a photo sharing site:

 * Users upload photos
 * Other users see the photos when they visit the site.
 * Nothing needs to update dynamically. When a new photo is uploaded
   or someone makes a new comment, it's OK that people already on the
   page don't see it immediately.
 * State wants to be persistent. We don't want to lose state when the
   server reboots.

If we generalize enough, there are a lot of apps that look like this:

 * We have some important data.
 * The app consists of looking at and modifying that data.
 
Other examples:

 * An online store
 * Most social media sites, at least before ~2015.
 * Control panels for online services
 * Online banking
 * Customer service ticket systems

The important data is the core of our app, so we need a reliable and efficient
way to store it. We have a good solution: A Relational Database Management
System (aka. SQL Database).

 * Our data comes as a set of well defined types.
   * e.g. A user name, an email address, some other fixed fields.
 * There are defined relationships between our data.
   * e.g. A photo belong to a user, and a photo has many comments.
 * We want to be able to validate our data and relationships.
   * Otherwise we end up with corrupted data, which is a serious problem.
 * We want to be able to query data based on the relationships.
   * e.g. Get all comments associated with a photo.

Photo sharing has one edge case that doesn't fit 100% smoothly with a RDBMS:
Photos themselves are big chunks of data. A SQL database *can* store big chunks
of data, but it's not the best tool in this case. For storing big files, we're
going to use the filesystem.

A RDBMS stores a collection of tables:

 * Each table stores records of one type, with an associated schema.
 * Each table has a mandatory field, a unique numeric ID called "id". 
 * A table can have fields which reference records in other tables, by
   storing the "id" of the row in the other table.

We can treat our photo sharing site as a database (& our photos as files) plus a
user interface that allows us to do CRUD operations: Create, Retreive, Update,
Delete.

What tables?

 - users:
   - email
   - name
   - password? not yet
 - photos:
   - user_id
   - filename
   - description

A resource in our router adds 7 paths:

 - index - lists all instances of the resource
 - [R] show - show one user
 - edit - shows the form to edit a user
 - [U] update - updates a user
 - new - show the form to create a user
 - [C] create - create a user
 - [D] delete - delete a user
 
REST routing convention. 



