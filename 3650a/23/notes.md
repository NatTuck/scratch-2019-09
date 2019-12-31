
# Today: More Filesystems

## Important FS Assignment Hint

 - The data.nufs file mapped into memory isn't memory, it's a
   disk image.
 - So you don't want to store pointers in the disk image.

# Solid State Drives

Flash SSDs have some weird properties:

 - Pretend to be harddrives, so they expose 512B or 4kB logical blocks as
   their interface.
 - They actually write in physical pages, which tend to be larger than
   logical blocks (e.g. 8kB).
 - Can only write to "clean" pages that either haven't been written or
   have been erased.
 - Erased (dirty -> clean) in multi-page blocks (e.g. 16kB).
 - Erases are limited. After a physical block is erased too many times it can no
   longer be erased. With QLC flash this might be 1 - 5000 erases per block.

If SSDs really exposed physical flash cells as logical blocks, popular
locations would get their erases used up immediately.

Solid state drives don't do that. Instead they provide a virtual -> physical
mapping of logical blocks, handled in the drive firmware.

Firmware manages the flash on the drive to optimize for:

 - Available clean write pages.
 - Even distribution of erases across all blocks.
 - Garbage collection is used.
 - Wear leveling is perfomed.

## Optane

 * Similar to ReRAM
 * Byte addressable.
 * Very low latency.
 * More rewrites than flash, but not unlimited.
   * 256GB of Optane might give you 250 PB of writes.
   * They expect it to last about 5 years in heavy-ish use.
 * Optane *is* doing flash-style address indirection.

Two configs:

 * As flash-style SSDs
 * As DDR4 form DIMMs, two use cases:
   * Fit more memory in a server.
   * Intel provides an API for storing to the Optane RAM kind of like
     a key-value store.




