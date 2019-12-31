



This week:

 - Two lectures on support concepts.

Next week:

 - Last normal lecture.
 - Thanksgiving
 - Project is due that Sunday.

After that:

 - Presentations
 - Random teams will be selected to present each day.
 - There will be an online peer evaluation component - bring a laptop.
 - You're required to show up for the presentations.


# Lecture 22: Persistent Storage Complications

## Kinds of State

 * Server-side, transient state: GenServer
 * Server-side, persistent state: Postgres
 * Client-side, transient state: Redux, JavaScript variable
 * Client-side, persistent state: localStorage


# How to do persistent server-side state?

## Plan A: Files on the Filesystem

 * This is the "normal" way to store long term persistent data.
 * Files are a reasonably efficient way to map a heirarchical key
   structure to arbitrarily large chunks of data.
   
Advantages:

 * Files work with any programming tools.
 * There are a lot of tools for manipulating files, like backup
   programs.

Problems:

 * Opening files is kind of slow. Filesystems need to maintain standard
   semantics (e.g. POSIX).
 * Files have non-trivial overhead, e.g. 4k block size.
 * Concurrency isn't handled by default = data races.
   * Filesystems do have lock mechanisms.
 * Solving all these things results in building a key-value store.
 * Scaled poorly beyond one machine.

We could build Lens with files:

 * users
 * photos
 * tags (including photo_tags)
 
## Plan B: Key-Value store 

This is a library or service that associates keys with values.

Minimally, two operations:

 * Get
 * Put

Advantages:

 * Can optimize without worrying about the rules for files.
 * Can enforce atomicity for get, put, and even atomic read-modify-write.
   * e.g. with per-key locks
 * Can be made to scale easily with key based sharding
 * Can be made redundant with m-of-n replicas.
 * CRUD operations map well to REST.

Disadvantages:

 * Multi-key operatons aren't atomic.
 * Efficient and powerful queries can be hard, especially joins between
   different kinds of records.
 * Can't get all the guarantees you really want for reliability, especially
   data consistency across multiple resources.

Solving lens:

 * users
 * photos
 * tags (including photo_tags)


## Plan C: Relatonal Database

 * MySQL
 * Postgres
 * MSSQL
 * Oracle
 * SQLite

Key concept: ACID properties

 - Atomic: All transactions - operations that mutate data in the DB - are
   atomic, even if several different tables are updated.
 - Consistent: All queries see the data in a consistent state - each other
   transaction has either happened completely or not at all. Transactions
   appear to be applied in a globally consistent sequential order.
 - Isolation: Queries don't see the result of other transactions until those
   transactions are guaranteed to have successfullly completed.
 - Durability: Once a transaction is successfully completed, even power
   loss won't unexpectedly undo it.

Advantages:

 - We want the ACID properties.
 - SQL DBs validate schemas.
 - Foreign key references make joins possible.
 - Transactions let us atomicly mutate multiple tables.
 - Indexes are easy.

Disadvantages:

 - Scaling to multiples machines is hard.
 - Providing a bunch of guarantees costs performance.
 - Schemas are mandatory and changing them is annoying. 
 - This is innately pretty complicated. 

Scaling:

 - Buy a bigger server.
 - Try cluster solutions.
 - Do manual (or possibly system-supported) sharding.
   - This loses us foreign key validation and joins.
 - Consider doing it with something other than a SQL DB.

## Plan Z: NoSQL Databases

### Example 1: MemcacheD

 - This is a cache.
 - Good way to improve performance on multi-page websites.
 - Occasionally generate pages and store them in the K-V store.

### Example 2: Redis

 - String key to structured value (e.g. list, hash table, ordered set, etc)
 - Clusters by simple sharding.
 - Operations that make sense on values are efficient.
 - Data can be persisted to disk occasionally, but without hard guarantees.
 - Use: common for queues & small caches.

### Example 3: MongoDB

 - JSON document store (string keys)
 - Optional schemas, which enable limited join queries
 - Schema-based indexes
 - Eventually synced to disk
 - Historically bad reputation
 - This is not an SQL replacement 
 - Ebay uses this for media metadata

Scaling:

 - Sharding by key
 - Replicas: Default majority read and write.


### Problem: A perfect distributed datastore is impossible

The CAP theorem

 - The problem is that Partition Tolerance is required.

So we must pick one:

 - Consistency
 - Availability

Two solutions:

 - Strong consistency: Refuse unconfirmed writes.
 - Strong availability: Always allow writes, accepting that
   some readers may get old data.

### Example 4: CouchDB

 * JSON document store (string keys)
 * No transaction guarantees
 * Eventual consistency by versioning
 * This leaves a problem with concurrent writes.
 * Notes can write without permission.
 * Eventually synced to disk.
 * Map-Reduce indexes.
 * Users: This is where NPM package metadata is stored.

Offline support:

 * You can put a couchDB node on a client device (e.g. a user's phone)
   this allows offline app usage.
 * There's also PouchDB, which is a node written in JavaScript that
   can run in the browser.
 * Of course a local node will only contain that user's data.


### Riak KV:

 * Another one.
 * String key to blob value.
 * User: Uber for car dispatch
 
Neat idea: CRDTs 
 
 * We can do two updates to the same data.
 * When we combine those update later, we get the correct combined result.
 * Counter, Set


### Cassandra

 * A lot like an SQL database without ACID transactions.
 * Uses sharding and replicas instead.
 * Majority required for writes.
 * Guarantees durability.
 * Can't support some SQL queries (e.g. some joins).
 * Users: Netflix (shows) 
 
## Other options

### CockroachDB: A distributed SQL database

 * Appears to use sharding and replicas.
 * Has horizontal scaling, even for writes.
 * Writes require a majority of replicas to confirm.
 * Doesn't support all SQL queries.
 * Still has some performance weirdness.
 * Repeatedly updating the same row is really slow.









