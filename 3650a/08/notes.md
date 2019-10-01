
# CS3650 Lecture 8: Hash Tables

## Key-Value Map

Ways to build one:

 - Association list
   - Just a list of {key, value} pairs.
   - Can insert with "cons".
     - Or can scan for duplicates.
   - Lookup requires an O(n) scan of the list.
 - Tree structure (e.g. a balanced binary tree)
   - Operations are all O(log n)
 - Most popular: hash table
   - Operatoins are all expected amortized O(1).
     - N operations on a hash table tend to take O(n).


