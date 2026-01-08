# 2. Design Document  
## Memory Management and Cache Simulator (C++)

---

## 2.1 Memory Layout and Assumptions

The simulator models main memory as a **contiguous linear address space** of fixed size (e.g., 1024 units). Memory can be initialized on starting the simulator using the **'init memory_size'** command. If not specified, it is assumed to be 1024 bytes as a defualt size. Memory is internally represented as a list of variable-sized memory blocks, each defined by:

- Starting address  
- Block size  
- Allocation status (free/used)  
- Unique block identifier which are postive integers.

### Assumptions:
- Memory is **byte-addressable** using integer indices. This basically means that memory is being treated like a long array where each address is represented by an integer. This resembles real computers as they are also byte addressable and the use of integers in this project keeps the simulator simple and yet realistic.
- Allocation of memory is done as a **continous block**. the malloc() function separtes a block into two blocks: free[] and used[]. This assumption is used to model **heap allocations** in operating systems. 
- Memory size is **fixed at initialization**. It cannot be changed once the simulator is running. This resembles the real operating system as they also have a finite memory. 
- The simulator is **single-threaded** as the commands are processed sequentially. No two CLI command can run at the same time. 
- Memory blocks are split on allocation if the target block is bigger in size then the requested memory. If two consequent blocks are free on deallocation of memory, they are merged. This is known as **coalescing**. This prevents excessive fragmentation and this is actually how real operating systems work. 

This abstraction enables the study of memory allocation strategies and fragmentation behavior.

---

## 2.2 Allocation Strategy Implementations

The simulator implements **three dynamic memory allocation strategies**, which are selectable at runtime using the 'set allocator desired_allocator' command:

### First Fit
Allocates the first free block that is large enough to satisfy the request.

- **Fast allocation** as it does not need to check all the available blocks and allocates memory in the first block which is found free and large enough.
- Can **increase external fragmentation** as it can lead to the creation of multiple smaller blocks in the memory. 

### Best Fit
Allocates the smallest free block that can satisfy the request.

- **Reduces** immediate wasted space as it checks all the blocks and allocates memory in the one which has the least size and is also large enough to allocate the requested memory.
- May **increase fragmentation** over time because it leaves behind many tiny free blocks that are too small to be reused.

### Worst Fit
Allocates the largest free block available.

- Preserves larger contiguous free blocks
- Can **waste memory** for small requests 

The allocation strategy is stored as an enumeration and applied during the block selection phase of allocation.

---

## 2.3 Deallocation and Coalescing

During deallocation:
- The specified memory block is marked as free.
- Adjacent free blocks are **coalesced** to reduce external fragmentation.

This ensures efficient memory reuse and minimizes fragmentation.

---

## 2.4 Buddy System Design - (Not Implemented)


## 2.5 Cache Hierarchy and Replacement Policy

The simulator models a **two-level cache hierarchy**:

| Cache Level | Description |
|------------|------------|
| L1 Cache | Small, low-latency cache |
| L2 Cache | Larger, higher-latency cache |

### Cache Design:
- **Fully associative** as any memory address can go into any cache slot. The cache is being treated like a simple list of fixed size.
- Each cache level can only store a **fixed number of entries**.
L1 can store 2 entries and L2 can store 4 entries.
- **FIFO** replacement policy is applied which means that the oldest entry in the cache is removed first and the new enrty is stored at the back. 
- **Tracks hits, misses, and access counts per level**. Hit refers to when the requested entry is found in the particular cache level. Miss refers to when it is not found, and access count refers to the total attempts of accessing a particular entry in the cache level. The access counts is important for calculating the Hit ratio of the cache levels.

### Latencies: Time taken to access a cache level (this is fixed for this project)
- L1 Cache: 1 cycle  
- L2 Cache: 10 cycles  
- Main Memory: 100 cycles  

---

## 2.6 Cache Access Flow and Miss Propagation

Memory access follows this sequence:

1. Address is checked in L1 cache
2. On L1 miss, L2 cache is accessed
3. On L2 miss, main memory is accessed
4. Data is inserted into L2 and promoted to L1
5. Access latency is accumulated at each level

This flow accurately models **miss penalty propagation** across cache levels.

---

## 2.7 Cache Performance Metrics

The simulator tracks **cumulative cache statistics** across all memory access commands:

- Cache hits and misses per level
- Hit ratio per cache level
- Total cache access time
- Miss penalty contribution to access time - when a cache miss happens at one level, the time cost of accessing the next lower level is added to the total access time.

Statistics represent workload-level behavior and are not reset per access.

---

## 2.8 Virtual Memory Model - (Not Implemented)


## 2.9 Fragmentation Metrics

The simulator computes and reports:

### Internal Fragmentation
Unused memory within allocated blocks due to allocation size differences. This is **always 0** in my project because everytime an empty block is allocated it gets split into a free block and a used block. So, there is never any unused space left in the block. 

### External Fragmentation
Free memory split into non-contiguous blocks that cannot satisfy large allocation requests.

**Fragmentation is reported as a percentage of total memory.**

---

## 2.10 Limitations and Simplifications

- No buddy allocator implementation
- No paging or TLB
- Fully associative caches only
- FIFO replacement policy
- Fixed access latencies
- Fixed cache level sizes
- No write-back or coherence modeling

These simplifications were chosen to balance correctness and implementation complexity.

---

## 2.11 Summary

The simulator provides a functional framework for analyzing:

- Dynamic memory allocation strategies
- Fragmentation behavior
- Cache hierarchy performance
- Cache hit/miss statistics
- Memory access latency propagation


The design is modular and extensible, allowing future enhancements such as buddy allocation and virtual memory support.
