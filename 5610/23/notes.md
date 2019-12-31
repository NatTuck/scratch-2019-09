
# Today: Distributed Elixir

 * Erlang VM for Reliable apps

 * We're going to build a key-value store.
 * A key value store wants to be distributed for:
   * Scalability by sharding
   * Reliability by mirroring

## Stuff that we could add to KvStore

 * Proper m-of-n reads / writes.
   * Example: Must write to majority and read from majority. (consistency)
   * Example: Must write to at least one, read from at least one. 
     * Probably want nodes to communicate with each other to propagate updates.
 * That would let us explicitly trade off 
   CAP consistency vs. CAP availability.
 * Any of these changes would benefit from version numbers.
   * Really want vector clocks.
 * Eventual consistency: Accept writes, have the nodes propagate values
   between themselves.

