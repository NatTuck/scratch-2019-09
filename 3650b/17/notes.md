
# Sorting Assingnments

 - Writing is faster if you call write less.
 - Reading is faster if you call read less.
 - Moral: System calls are slow-ish

# Memory Allocator

A memory allocator for C involves implementing two functoins:

 - malloc
 - free

Historically malloc was built using sbrk(2). Nobody's done that
in decades.

We allocate memory with mmap, specifically with MAP\_PRIVATE|MAP\_ANONYMOUS.

Minimum allocation size when allocating pages is 4k. If you ask for an uneven
number of pages, it'll effectively round up.

Two problems when implementing malloc using mmap:

 - We want to handle allocations under 1 page efficiently.
   - Rounding up all allocations to 4k is inefficient.
   - Doing a syscall for every allocation is slow.
 - We want to be able to free memory without passing in the size
   of the allocation.
   - free just takes a pointer
   - munmap takes (pointer, size)

Especially for small allocations, we want to reuse memory rather than
unmapping it and asking for it back.

Traditional solution: Free List

Logically, a free list is a list of free blocks of memory, storing
{ address, size } for each block.

Problem: How do we keep track of the size of allocated blocks of
memory?

Solution: We're the allocator. We can allocate extra space and keep
stuff there.

Problem: How do we allocate our free list?

Solution: We don't. We're the memory allocator, and this information
we're trying to track is blocks of free memory. We can put stuff in
there.

We'll use our free chunks to build a linked list.

```
struct free_list_node {
    size_t size;
    free_list_node* next;
};
```

# Malloc Example

 * Free list is empty.
 * User says a = malloc(100);
 * First, check free list, nope.
 * Then we'll mmap a page, address is 10000;
 * We can treat that as a free\_list\_cell: 10000 => { size: 4096; next = 0 }
 * Split this cell into:
   * a = 10000 => { size: 108; next: 0 }
   * 10108 => { size: 3988; next: 0 }
 * Malloc returns 10008
 * Free list becomes (head = 10108) => { size: 3988; next: 0 }

 * b = malloc(200)
 * Malloc returns 10116
 * Free list becomes (head = 10316) => { size: 3780; next: 0 }

 * free(b)
 * Free list becomes 
   * (head = 10108)
   *  => { size: 208, next: 10316 }
   *  => { size: 3780, next: 0 }

# Coalescing: Don't have adjacent elements on the free list, instead
# glue them together into one.

 * free(b)
 * Free list becomes 
   * (head = 10108)
   *  => { size: 3988, next: 0 }

# Big allocations

 * If a requested allocaiton is "big", we just delegate to mmap.
 * If a requested free is "big", we just delegate to munmap. 

How big is big?

 * At least 4k.
 * In general, we're talking more like 64k or a meg.

# When do we return memory on the free list to the operating system?

 * Maybe never?

## Design Considerations

Should our list be singly or doubly linked?

Why single?

 - Maybe easier to implement

```
struct list_cell {
   long size;
   ptr* next;
};
```

Why double?

 - Coalescing might be easier, but we probably just need to
   store previous pointer on forward traversal.

```
struct list_cell {
   long size;
   ptr* next;
   ptr* prev;
};
```

## Should free list be sorted?

If so, by what?

Sort list by memory address.

 - This makes coalescing easier.
 - Otherwise coalescing can require two (or more) list scans.
 - Either way free is O(n).

Sort list by size.

 - This makes allocation easier, or possibly just more efficient.
 - We can find the smallest free chunk big enough to fit without
   scanning the whole list.
 - Either way malloc is O(n).

Should we go out of our way to find the smallest free chunk where
our allocation fits to minimize fragmentation.

 - Sure.

# Free List Performance

 - malloc: O(n)
 - free: O(n)

Linked lists tend towards O(n).

Binary trees tend towards O(log n).

```
struct tree_node {
    size_t size;
    tree_node* left;
    tree_node* right;
};
```

Plan A: Binary tree is sorted on block size.

 * malloc is O(log n)
 * free is O(n)

Plan B: Binary tree is sorted on memory address.

 * malloc is O(n)
 * free O(log n)

```
struct tree_node {
    size_t size;
    tree_node* parent_size;
    tree_node* parent_addr;
    tree_node* left_size;
    tree_node* right_size;
    tree_node* left_addr;
    tree_node* right_addr;
};
```

Minimum allocation = 56B.

Combo Tree:

 * malloc is O(log n)
 * free is O(log n)








 
 
