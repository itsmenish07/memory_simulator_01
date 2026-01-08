# Memory Management & Cache Simulator (C++)

A command-line based simulator implemented in **C++** that demonstrates core **Operating System memory management concepts** and a **multi-level cache hierarchy**.  
The project is designed for learning and experimentation, allowing users to visualize memory allocation, fragmentation, and cache performance.

---

## Demo video: https://drive.google.com/file/d/1ZnvRdLAW3XAyBDexYJ4IBVZRMVq1Hb2_/view?usp=sharing
## Video 2: https://drive.google.com/file/d/1KHExxikziieKRA2L9bewVutW-PHi6veF/view?usp=sharing
## Test Artifacts docs file: https://docs.google.com/document/d/1uweeHVJXwzO82ifcGRE2u22_DkPgWFMr/edit?usp=sharing&ouid=107229125839487798625&rtpof=true&sd=true
## the design.md file is in the docs folder of the project structure. 

## 🚀 Features

### 🧠 Memory Management
- Contiguous memory allocation simulation
- Supports multiple allocation strategies:
  - **First Fit**
  - **Best Fit**
  - **Worst Fit**
- Dynamic memory allocation and deallocation
- Coalescing of adjacent free blocks
- Tracks:
  - Used memory
  - Free memory
  - External fragmentation
  - Allocation success/failure

---

### 💾 Cache System
- Multi-level cache hierarchy:
  - **L1 Cache**
  - **L2 Cache**
- Tracks per-level:
  - Cache hits
  - Cache misses
  - Hit ratios
- Simulates:
  - Cache access latency
  - Miss penalty propagation to lower cache levels
- Maintains total cache access time across all accesses

---

## 🖥️ Build & Run
- In terminal, enter the following commands:
  make
  ./memsim
- The memory simulator will now start.

## 📟 Supported Commands
- init memory : initilaized desired bytes of memory
- set allocator <allocator>: allocator can be set to first_fit, best_fit or worst_fit
- free <block_id>: enter the id of the block to be deallocated
- access <address>: enter the address of the memory which needs to be accessed using multi-level cache system
- dump: gives the current memory layout
- stats: display memory and cache statistics
- exit: exit simulator

## Sample Output:
Memory Statistics:

Used Memory: 200

Free Memory: 824

External Fragmentation: 6.07%


Cache Statistics:

L1 Hits: 1

L1 Misses: 1

L2 Hits: 1

L2 Misses: 1

L1 Hit Ratio: 50%

L2 Hit Ratio: 50%

Total Cache Access Time: 102 cycles


## 🧩 Design Notes
- Memory is modeled as a list of contiguous blocks

- Allocation strategies determine which free block is selected

- Internal fragmentation is zero because memory is allocated exactly as requested

- Cache replacement policy is FIFO

- Cache miss at one level propagates to the next lower level

## ⚠️ Limitations
- Buddy allocation system not implemented

- Virtual memory and paging not simulated

- Single-threaded execution

- Cache associativity simplified

## 👤 Author:
- Naisha Rajput | Electrical Engineering | IIT Roorkee

