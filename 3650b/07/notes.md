
# Data Structures in C

## Two data structures in HW:

 - Variable Length Array
   - vector, ArrayList
 - Key-Value Map
   - HashMap, unordered_map, hash, dictionary


(Functional programs prefer linked lists to vectors)


# Vectors

Operations:

 - Get and put at specific index.
 - Get size.
 - A "push back" operation that appends a new element to the end of the array.
 
C Arrays are:

 - Fixed length
 - Don't know their size.

Goals:

 - Retain continguous memory layout.


## Are we slow?

```
  vector xs = [];
  for (int ii = 0; ii < 100; ++ii) {
     xs.push_back(ii);
  }
```

How about with doubling capacity?

  - Claim: O(n) total.
 
  - Concretely: 227 operations
  - 100 to insert 100 elemnets
  - copies: 1 + 2 + 4 + 8 + 16 + 32 + 64
  
How many operations without doubling?

  - O(n) for each push_back
  - O(n) for the loop
  = O(n^2)

  - Concretely: 5050
  - 1 + 2 + 3 + ... + 100 = (n * (n+1)) / 2 = 5050 for n = 100

Hint:

 - check out "man 3 realloc"
  
  












