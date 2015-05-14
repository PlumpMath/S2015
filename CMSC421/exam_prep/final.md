# Ch.1: Overview
  ## What is an OS?  What is a kernel?
  An operating system, or OS, is a program responsible for managing the hardware of a system
  making it convenient for the user(s) to use applications without having to concern themselves
  with hardware level issues. The kernel is the core of the operating system that is *always*
  running. This distinction is made against things like the Unix toolchain, which is considered
  part of the operating system, but is only executed when the user chooses so.
  ## Computer system organization and architecture
  ## OS structure
    - multiprogramming and timesharing
  ## OS operations
  ## Process management
  ## Memory mgmt
  ## Storage mgmt
  ## Protection and security
  ## Some basic data structs used in the kernel

# Ch.2: Operating System Structures
  ## OS services
    - UI, program exec., I/O, file system, communications, etc.
  ## User's interface to the OS: system calls
  ## User mode and kernel mode
  ## Types of syscalls
  ## Interrupt-driven nature of OSs
  ## System programs
  ## OS design and implementation
  ## OS structure--multiple alternatives
    - simple (MS-DOS), UNIX, fully-layered, microkernel, etc.
  ## OS debugging
  ## System boot process, from BIOS to fully running system

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
