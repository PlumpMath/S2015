# Ch.1: Overview
## What is an OS?  What is a kernel?
  An operating system, or OS, is a program responsible for managing the hardware of a system
  making it convenient for the user(s) to use applications without having to concern themselves
  with hardware level issues. The kernel is the core of the operating system that is __always__
  running. This distinction is made against systems programs (ex. `grep`, `cat`), which are considered
  part of the operating system, but are only executed when the user chooses so.
## Computer system organization and architecture
## OS structure
  - multiprogramming: increases CPU utilization by ensuring there is always a job to run.
  - timesharing (aka multitasking): extension of multiprogramming where the CPU executes
    multiple jobs by switching between them.

## OS operations
## Process management
A program is __not__ a process. A program is a _passive_ entity, just code. A process is an
_active_ entity, it is actually executed and does work.

## Memory mgmt
To improve utilization of the CPU and the speed of responses to users, the operating system
keeps numerous processes in memory and manages:
  - which parts of memory are being used and by whom
  - deciding which processes (or parts thereof) and data to move into and out of memory.
  - allocating and deallocating memory space as needed.

## Storage mgmt
The OS abstracts the physical properties of storage devices to define a logical storage unit,
the *file*. Storage can be on a number of different media: magnetic disks, optical disks, magnetic
tape, etc.

A file is a collection of related information defined by its creator. The operating system manages:
  - creating and deleting files
  - creating and deleting directories to organize files
  - supporting primitives for manipulating files and directories
  - mapping files onto secondary storage
  - backing up files on stable (nonvolatile) storage media

The operating system also handles __caching__ (temporary, fast storage of data). Caches have limited
size, so this needs to be aggressively managed.

## Protection and security
The operating system provides protection and security in a number of ways.
  - user identifiers (user IDs, or security IDs in Windows)
  - group identifiers
  - privileges

## Some basic data structs used in the kernel
Basic data structures used in the kernel include linked-lists (these are everywhere!), red-black
trees (and other balanced tree implementations) for file systems.

# Ch.2: Operating System Structures
## OS services
  - For the user:
    - UI (CLI, batch, GUI)
    - program exec.
    - I/O
    - file system
    - communications
    - error detection

  - For efficient system operation:
    - resource allocation
    - accounting
    - protection and security


## User's interface to the OS: system calls
There are shells (like `bash`) which allow the user to interact using very precise commands. There
are also graphical user interfaces, or GUIS, which allow the user to interact using a
mouse-and-window based system. The choice of which to use comes down to personal preference.

No matter which type of interface is used, __system calls__ are made which make direct requests of
kernel level resources. Most programmers never have to deal with these calls directly, due to layers
of abstraction.

## User mode and kernel mode
The OS has two main modes, which are typically governed by the presence or absence of a single bit.
These are user mode and kernel mode. In user mode, interactions with kernel utilities is greatly
restricted. When a system call is made, the OS temporarily switches into kernel mode, executes the
command, then switches back into user mode.

## Types of syscalls
There are six major categories of system calls:
  - process control
  - file manipulation
  - device manipulation
  - information maintenance
  - communications
  - protection

## Interrupt-driven nature of OSs
Modern OSs are interrupt-driven. To the average user, it may appear that all applications are being
run simultaneously. In reality, a process is run for a very short amount of time, interrupted, and
another process is allowed to run. Whenever a system call is made, the OS cedes control to that
call. This is how processes switch, files are written and read, etc.

## System programs
Along with system calls, there are system programs. These can be interfaces to system calls, or more
complex programs. They are divided into categories:
  - file management
  - status information
  - file modification
  - programming language support
  - program loading and execution
  - communications

## OS design and implementation
There are two types of design goals in operating systems: user goals and system goals. For users,
the system should be easy-to-use, reliable, safe and fast. The system should (similarly) be easy to
design, implement, maintain and operate. It should be flexible, reliable, error free and efficient.
These "goals" are usually vague and can be interpreted in a number of ways.

An important principle is the separation of __policy__ from __mechanism__. Mechanism is _how_
something is done. Policy is _what_ will be done.

## OS structure - multiple alternatives
  - simple (MS-DOS): most functionality in least space, not modular
  - UNIX and other fully-layered systems: system broken up into layers of functionality.
    Layer 0 is hardware, layer N is the user interface.
  - microkernel: all non-essential functionality is moved from the kernel to system and user-level
    programs.

## OS debugging
  - Failure analysis: when a process fails, error information is written to a log file. The
    operating system can also take a __core dump__, which is a snapshot of the memory of the
    process. When the kernel fails, it is called a crash. These generate __crash dumps__, which are
    analogous to core dumps.

## System boot process, from BIOS to fully running system
  - Bootstrap program/loader: locates the kernel, loads it into memory, starts execution. Kernel
    handles the rest of initialization.

# Ch.3: Processes
## Concept of a "process"
## Process structure in memory
## Process states and transitions
## Process control block (PCB)
## Proc scheduling, queues, short-term and long-term schedulers
## Context switch
## Operations on procs
## UNIX fork()/exec(), parent/child proc. relationships
## Interprocess communications (IPC)
  - implementations: shared mem, message passing,

## Producer/consumer problem
  - Bounded buffer solution

## Direct vs. indirect IPC
## Synchronous vs. asynchronous communications
## Sockets, remote procedure calls (RPCs)
  - especially UNIX pipes

# Ch.4: Threads
## What is a thread?
## Motivation for using threads
## Multicore programming
## Memory structure of multithreading
## Multithreading models
  - one-to-one, many-to-one, many-to-many

## Thread libraries, e.g. POSIX Pthreads
## Implicit threading
## Threading issues
## OS e.g.s

# Ch.5: Process Synch
## Race condition    
  - Should be familiar with extended Bounded Buffer problem, trying
    to use every buffer element

## Critical-section problem
  - Necessary properties of any complete solution to the critical-section prob.

## Peterson's soln
## Synchronization hardware
  - Atomic operations, and why they're important
  - pseudocode version of test-and-set, compare-and-swap atomic ops

## Mutex locks using spinlocks
  - acquire() and release()

## Semaphores
  - wait()/signal() (or P()/V())
  - both counting semaphores, and mutexes through binary semaphores
  - semaphore implementation with no busy waits: using block() and wakeup()

## Deadlock and starvation
  - should be able to give examples
  - some (possibly unrealistic) solutions to deadlock

## Classic problems of synchronization:
  - Bounded-buffer problem, solution w/semaphores
  - Readers and writers problem, solution w/semaphores
  - Dining philosophers problem (not solved with semaphores)

## Monitors
  - general definition
  - high-level (i.e., not very detailed) understanding of condition vars
  - Using monitors to solve Dining Philosophers

## Sync e.g.s
## Alt. approaches

# Ch.6: CPU Sched
## Purpose of scheduling
## Scheduling criteria: factors we can maximize/minimize
## Sched algs:
  - First Come/First Serve (FCFS)
  - Shortest-Job-First (SJF)
    - with preemption: becomes "shortest-remaining-time-first"

## CPU burst prediction
  - Exponential averaging
  - Be able to draw Gantt charts

## Priority Scheduling
## Round Robin -- implies preemption
## Multi-level Scheduling
## Processor Affinity --just basic concept and motivation
## Real-time Scheduling--basic concepts
## Scheduling algorithm evaluation
  - More important ones: deterministic modeling, and simulation

# Ch.7: Deadlock
## Resource allocation graphs
## Handling Deadlocks:
  - prevention vs. avoidance
  - Deadlock prevention: the four conditions
  - Deadlock Avoidance:
    - Safe state definition
    - Single-instance algorithm: Resource-allocation-graph algorithm
    - Multi-instance algorithm: Banker's algorithm
  - Deadlock detection
    - Single-instance: wait-for graph
    - Multi-instance: related to Banker's alg.

# Ch.8: Memory Management
## H/W versions:
## Protection: base and limit registers
## Strategies for relocating code
## Logical vs. Physical address spaces
## Memory Management Unit (MMU)
## Relocation register
## Swapping
## Continuous memory allocation: first fit, best fit, worst fit
## Fragmentation: internal vs. external
## Segmentation
  - H/W: segment table structure

## Paging
  - Basic concept, comparison to contiguous relocation and segmentation
  - Page table
  - Translation lookaside buffer
  - Hierarchical page tables
  - Hashed page tables, Inverted page tables--just basic concept
  - Don't need to memorize any specific architectures

# Ch.9: Virtual Memory
## Basic concept
## Sparse page tables
## Demand paging
  - Page faults--details of basic mechanism
  - Instruction restarts
  - Page fault rates, calculating paging overhead
  - Page replacement strategies
    - FIFO vs. Optimal vs. LRU
    - LRU approximations
    - Second chance algorithm
    - Reference string-based evaluation

## Allocation strategies
  - Equal, proportional

## Thrashing
  - What is it, when does it occur
  - Working sets

# Ch.10: Storage Management
## Know the basic types of storage
## Disk-based storage:
  - Disk layout (cylinder, head, sector)
## Disk scheduling
  - FCFS, Shortest Seek Time First (SSTF), SCAN/C-SCAN, LOOK/C-LOOK
## RAID: basic concept, plus know at general level:
  - Level 0: striping; Level 1: mirroring; Level 5: distributed parity
  - For each, what speed and reliabiltiy pros and cons are

# Ch.11: File System Interface
## What is a file?
## File attributes
## Access methods: Sequential vs. Direct
## Directories:
  - Single level vs. two-level vs. multi-level tree vs.
    - directed acyclic graph (DAG) vs. general graph
    - Features of each type

## File system mounting
## UNIX protection (user, group, world RWX permissions)

# Ch.12: File Sytem Implementation
## Boot block, Volume control block, file control block
## Allocation methods:
  - Contiguous, Extent-based, Linked, and...
  - Indexed allocation:
    - Index block
    - Direct and indirect pointers
    - The UNIX inode multi-level block index

## Free block list representations
  - Bitmap, linked list, UNIX's hybrid linked list (mentioned in lecture)

# Ch.13: I/O systems
## Multi-bus architecture model
## I/O control: I/O ports and special cmds, vs. memory-mapped I/O
## I/O control models:
  - Polled
  - Interrupt-driven
  - DMA

## Block vs. character devices
## Non-blocking and asynchronous I/O

# Ch.14: Protection
## General knowledge of concepts:
## Principle of least privilege
## Domain of protection
## Access matrix
## Implementation: access lists for objects vs. Capability lists for domains
  - (Don't need to know about lock-key mechanism)

# Ch.15: Security (only if covered in class)
## General knowledge of concepts:
## Basic security problem definition
## Man in the middle
## Social engineering
## Trojan horse
## Trap door
## Buffer overflow attack
## Cryptography:
  - Symmetric encryption: what is it?
    - Key exchange problem
  - Assymetric (public key) encryption: what is it?
    - How is it used?
    - How can it be used for authentication
    - What is key distribution problem?
