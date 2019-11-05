
# Lecture 17: Memory Allocation

## What's a memory allocator?

An implementation of:

 - malloc
 - free

Why?

A new program starts with no heap space allocated.

To get heap space, you make a system call.

 - Traditionall that was sbrk(2).
 - Nobody's used sbrk to implement malloc in decades.
 - We allocate our memory with mmap
 - Specifically mmap(..., MAP\_PRIVATE|MAP\_ANONYMOUS, ...)
 - The kernel allocates in 4k pages. Requests smaller than that
   effectively get rounded up to the next page size.

So a memory allocator wants to use mmap to get memory from the OS, but we need
to fix a couple of sharp edges in the process:

 - We want to efficiently handle allocations under one page.
 - We want to be able to free memory without remembering the size
   of the allocation.
 - Especially for small allocations, we want to reuse memory rather than
   returning it to the OS and asking for it back.
   - System calls are slow.

Traditional solution: A free list.

 - This is a list of free blocks with, logically, location and size of each.

Problem: We don't track allocated memory, so we need a way to recover size
when it's freed.

Solution: Include the size of an allocation directly in the memory we allocate.

For example:

 - User requests 32 bytes.
 - We actually allocate 40 bytes (32 + sizeof(size_t))
 - The size field goes at the beginning
 - We return a pointer to right after the size field.

Problem: How do we allocate the free list?

Solution: We're the memory allocator, the thing we're tracking
is free blocks of memory. We can store stuff there.

Plan: Use the free blocks as nodes in a linked list.

```
struct free\_list\_node {
    size_t size;
    struct free\_list\_node* next;
};

struct fee_list_node* free_list_head = 0;
```

How do we handle a = malloc(100)?

 - Check free list for appropriate chunk.
   - If so, use that.
 - If nothing on freelist, mmap a page.

A page can be seen as a free-list-node 
  0x1000 => { size = 4096; next = 0; }

 - Slice an appropriate sized chunk off the chunk we found.
   - Break that up into:
     1000 => { size = 108, next = 0; }
     1108 => { size = 3988, next = 0; }

 - our malloc(100) returns 1008.
 - Global free list (head) is assigned 1108.

How do we then handle free(a)?

 - cons it onto the free list.
 - free-list-head => 1000 { size = 108; next = 1108 } => {size = 3988; next = 0 }
 - Problem: Fragmentation
 - Solution: Coalesce adjacent memory blocks on the free list.
 - We want the result: head => 1000 { size = 4096; next = 0 }


Big Allocations:

 - a = malloc(1G)
   - call mmap (for 1G + 8 bytes, we still want the size field)
 - free(a) 
   - look at the size field, it's big
   - call munmap
   
Design considerations:

## Single or doubly linked list?

Doubly linked list advantages:

 * There are some cases where having a back pointer helps a lot.
 * Specifically: coalescing.

Singly linked list advantages:

 * Simpler code overall
 * Minimum block size is smaller.

If user says malloc(4), we need to give them:

 - Size + Next = 16 bytes with singly linked list.
 - Size + Next + Prev = 24 bytes with doubly linked list.

## Ordered or Unordered List?

Ordered by what?

 - Order by address
   - List coalescing is easier.
   - List coalesing can be done in O(n) instead of O(n^2).
 - But ordering by size might be faster for malloc?
   - Can stop once you've passed where the block would be.
   - Also helps you find the smallest block where your object fits.

## Which item should we select for allocation:

 - The first one we find?
   - O(n) - but scan less of the list.
 - The smallest one that works?
   - O(n)

## Do we actually coalesce on every free, or do we only merge ajacent 
## items occasionally?

 - Delaying may actually be more expensive, since it can build up
   more work to do and may require a complete list traversal.

## How big is your "big" allocation cutoff?

 - Absolutely can't be smaller than 4k.
 - Probably should be bigger than that, since otherwise 5k allocaions are pretty
   wasteful.
   
## When do we return small allocation memory to the OS?

 - Never is easiest.

## What we have:

 - malloc is O(n)
 - free is O(n)

## What if we use a balanced binary tree

```
struct tree_node {
  size_t size;
  tree_node* left;
  tree_node* right;
};
```

Ordered by memory address:

 * malloc is O(n), we need to find a big enough chunk
 * free is O(log n)

Ordered by size:

 * malloc is O(log n)
 * free is O(n)
 
```
struct tree_node {
  size_t size;
  tree_node* parent_addr;
  tree_node* parent_size;
  tree_node* left_size;
  tree_node* right_size;
  tree_node* left_addr;
  tree_node* right_addr;
};
```

 * malloc is O(log n)
 * free is O(log n)
 * Minimum allocation size is 56 bytes 

Buddy System

 * Rule: We only allocate power-of-2 sizes.



# Bucket Allocator

 - Array of free lists
 - Each free list is a fixed size, selected at build time.
   - (e.g. 16, 24, 32, 48, 64, 96, ...)
 - malloc(40) -> 48, use bucket 48
 - If bucket 48 is empty, mmap another page of 48's.
 - Everything is O(1).



















