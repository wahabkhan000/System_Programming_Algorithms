# System Programming Algorithms

A comprehensive collection of **operating system (OS) algorithms and simulations** implemented in C++. This project demonstrates core system programming concepts including process scheduling, memory management, deadlock prevention, and CPU scheduling algorithms.

## Overview

This repository contains 12+ standalone C++ programs covering:

- **CPU Scheduling Algorithms** – FCFS (First-Come-First-Served), Round-Robin
- **Memory Management** – Paging, frame allocation, logical-to-physical address translation
- **Deadlock Prevention** – Banker's Algorithm for safe resource allocation
- **System Simulations** – Complete OS simulators with process, CPU, and memory management

All programs are interactive console applications designed for learning and portfolio demonstration.

---

## Project Components

### 1. CPU Scheduling Algorithms

#### First-Come-First-Serve (FCFS)
**File:** `First_Come_First_Serve.cpp`
- Simplest non-preemptive scheduling algorithm
- Processes execute in arrival order
- Calculates:
  - Completion time
  - Turnaround time = Completion time - Arrival time
  - Waiting time = Turnaround time - Burst time
  - Response time (same as waiting time for non-preemptive)
- Displays execution order and performance metrics table

**Input:** Arrival time, burst time, completion time for 3 hardcoded processes

**Output:** Process execution order and scheduling metrics table

---

#### CPU Management with FCFS
**File:** `CPU_Management.cpp`
- Simulates CPU core operations with ready queue
- Dynamically generates processes with random PIDs and arrival times
- Maintains ready queue as linked list (FIFO)
- Tracks:
  - CPU core status (IDLE/BUSY)
  - Running process ID
  - Next process to execute
- Process lifecycle: Ready Queue → CPU Execution → Termination

**Features:**
- Automatic duplicate PID prevention
- Sorted arrival time queue
- Visual ready queue display
- Real-time CPU state transitions

---

### 2. Memory Management

#### Memory Management Unit (MMU)
**File:** `Memory_Management.cpp`
- Simulates physical memory with paging architecture
- Configurable RAM and frame sizes
- Automatically generates process allocation and page tables
- Core components:
  - **Physical Memory:** RAM divided into fixed-size frames
  - **Frame Manager:** Tracks frame status (Free/Occupied) and process ownership
  - **Page Table:** Maps logical pages to physical frames
  - **Memory Information:** Displays memory usage, free frames, allocated frames

**Input:** RAM size, frame size, number of processes

**Output:** 
- Frame table with status and occupancy
- Memory utilization statistics
- Free/occupied frame count

**Address Space:**
- Each process size = 2 × Page Size
- Frame allocation with collision avoidance

---

#### OS Paging Simulator
**Files:** `Operating_System_Paging_Simulator_v1.0.cpp`, `v1.1.cpp`
- Complete paging simulation with logical-to-physical address translation
- Binary bit representation for addresses
- Automatic page table generation

**Features:**
- Configurable RAM (1-16 bytes for education) and process sizes
- Automatic frame number calculation
- Page and frame offset bit computation
- Logical address → Physical address translation algorithm:
  1. Extract page number from logical address
  2. Look up page in page table
  3. Get frame number
  4. Combine frame number with offset
  5. Access physical memory

**Input:** RAM size, frame count, process size, CPU address demand

**Output:**
- Main memory frame contents
- Page table mapping
- Logical and physical addresses in binary
- Retrieved value from physical address

---

### 3. Deadlock Prevention

#### Banker's Algorithm
**File:** `Banker's_Algorithm.cpp`
- Deadlock avoidance algorithm for resource allocation
- Determines if resource allocation leads to safe state
- Hardcoded for 3 processes and 3 resource types (CPU, Printer, Memory)

**Algorithm Steps:**
1. Input available resources
2. Input allocated resources per process
3. Calculate remaining need for each process
4. Determine safe execution sequence
5. Identify unsafe allocations that cause deadlock

**Matrices Computed:**
- **Allocated Resources:** Resources given to each process
- **Max Need:** Maximum resources each process requires
- **Remaining Need:** Still-needed resources = Max - Allocated
- **Available Resources:** Free resources after allocation

**Output:**
- Process execution order (safe sequence)
- Resource availability at each step
- Deadlock warning if unsafe state detected
- Resource allocation table

---

### 4. Complete Operating System Simulators

#### OS Simulator v1.0
**File:** `Operating_System_Simulator_v1.0.cpp` (~28 KB)
- Integrated simulation of process, CPU, and memory management
- Single-core CPU with FCFS scheduling
- Physical memory with paging support

**Components:**
- Process Manager: PID generation, arrival/burst time
- CPU Manager: Ready queue, process execution, state tracking
- Memory Manager: RAM allocation, frame management, page tables

---

#### OS Simulator v1.1
**File:** `Operating_System_Simulator_v1.1.cpp` (~34 KB)
- Enhanced version with improved memory management
- Better process tracking and statistics
- Detailed process control block (PCB) information

---

#### OS Simulator v2.0 with Round-Robin Scheduling
**File:** `Operating_System_Simulator_v2.0.cpp` (~35 KB)
- Extends v1.1 with Round-Robin preemptive scheduling
- Time quantum-based process switching
- Circular ready queue for fair CPU allocation

**Scheduling Features:**
- Each process gets fixed time quantum
- When time expires, process returns to queue end
- Better responsiveness than FCFS

---

#### Full Feature: Process, CPU & Memory with Round-Robin
**File:** `Operating_System_Process,CPU & Memory_Management_with_Round_Robin_Algorithm_Simulator.cpp` (~50 KB)
- Most comprehensive simulator with all three management systems
- Round-Robin scheduling with configurable time quantum
- Complete paging and memory translation
- Process states and lifecycle management

---

#### Additional Large Simulator
**File:** `OS_caried_by_fazal_qadir.cpp` (~51 KB)
- Alternate comprehensive OS simulation
- Full integration of all OS concepts

---

### 5. Utility Programs

#### Binary Conversion
**File:** `input_to_8(bit)binary.cpp`
- Converts character input to 8-bit binary representation
- Useful for understanding address bit representation

**Input:** String of characters

**Output:** Each character converted to 8-bit binary

**Example:**
```
Input: AB
Output: 01000001 01000010
```

---

## Algorithms & Complexity Analysis

| Algorithm | Purpose | Time Complexity | Space Complexity |
|-----------|---------|-----------------|-----------------|
| **FCFS Scheduling** | Process scheduling | O(n) | O(n) |
| **Round-Robin** | Fair process scheduling | O(n) | O(n) |
| **Banker's Algorithm** | Deadlock avoidance | O(n × m²) | O(n × m) |
| **Page Table Lookup** | Address translation | O(1) | O(p) pages |
| **Frame Allocation** | Memory assignment | O(n) | O(f) frames |

*n = number of processes, m = number of resource types, p = pages, f = frames*

---

## Architecture Overview

### Process Management
```
Process Creation → Ready Queue → CPU Execution → Termination
       ↓               ↓               ↓
    Assign PID    FCFS/RR Order   Track State
    Arrival Time  Waiting          Completion Time
```

### Memory Management
```
Logical Address → Page Table → Frame Number + Offset → Physical Address
   (from CPU)      Lookup        (in main memory)
```

### CPU Scheduling (FCFS)
```
Ready Queue [P1] → [P2] → [P3]
    ↓
 Dispatch P1 to CPU
    ↓
 Execute for Burst Time
    ↓
 Remove P1, Dispatch P2
```

### CPU Scheduling (Round-Robin)
```
Ready Queue (Circular)
    [P1] → [P2] → [P3] → [P1] ...
    
Each process gets Time Quantum,
then moves to back of queue
```

---

## Building & Running

### Prerequisites
- C++11 or later compiler (g++, clang, MSVC)
- Standard library with STL support

### Compilation

**Single File Compilation:**
```bash
g++ -std=c++11 filename.cpp -o executable
./executable
```

**Examples:**

**FCFS Scheduling:**
```bash
g++ -std=c++11 First_Come_First_Serve.cpp -o fcfs
./fcfs
# Enter arrival time, burst time, completion time for 3 processes
```

**CPU Management:**
```bash
g++ -std=c++11 CPU_Management.cpp -o cpu_mgmt
./cpu_mgmt
# Enter number of processes (auto-generates arrival times and PIDs)
```

**Memory Management:**
```bash
g++ -std=c++11 Memory_Management.cpp -o mem_mgmt
./mem_mgmt
# Enter RAM size, frame size, number of processes
```

**OS Paging Simulator:**
```bash
g++ -std=c++11 Operating_System_Paging_Simulator_v1.0.cpp -o paging
./paging
# Enter RAM size, frame count, process size, CPU demand address
```

**Banker's Algorithm:**
```bash
g++ -std=c++11 "Banker's_Algorithm.cpp" -o banker
./banker
# Enter available resources, allocated, and max need for 3 processes
```

**Full OS Simulator v2.0:**
```bash
g++ -std=c++11 Operating_System_Simulator_v2.0.cpp -o os_sim
./os_sim
# Simulates full OS with process, CPU, and memory management
```

---

## Usage Examples

### FCFS Scheduling Output
```
=========== FCFS Scheduling ============

Enter the Arrival-Time for Process 1: 0
Enter the Arrival-Time for Process 2: 2
Enter the Arrival-Time for Process 3: 4

Enter the Burst-Time for Process 1: 8
Enter the Burst-Time for Process 2: 4
Enter the Burst-Time for Process 3: 2

Enter the Completion-Time for Process 1: 8
Enter the Completion-Time for Process 2: 12
Enter the Completion-Time for Process 3: 14

Processes will execute in this way: P1 P2 P3

--------------------------------------------------------------
| PSID | A-Time | B-Time | C-Time | T-Time | W-Time | R-Time |
|  P1  |    0   |    8   |    8   |    8   |    0   |    0   |
|  P2  |    2   |    4   |   12   |   10   |    6   |    6   |
|  P3  |    4   |    2   |   14   |   10   |    8   |    8   |
--------------------------------------------------------------
```

### Memory Management Output
```
============================================================
==================== PHYSICAL MEMORY ======================
============================================================

MEMORY CONFIGURATION
------------------------------------------------------------
RAM Size             : 16 KB
Page Size            : 8 KB
Frame Size           : 8 KB
Number of Frames     : 2

FRAME TABLE
------------------------------------------------------------
Frame No.       Status          Occupancy
------------------------------------------------------------
0                Occupied        PID 4521 - Page 0
1                Free            NONE
------------------------------------------------------------
Memory Usage       : 16 KB / 16 KB
Free Memory        : 0 KB
Occupied Frames    : 1
Free Frames        : 1
```

### CPU Management Output
```
============================================================
====================== CPU MANAGEMENT ======================
============================================================

CPU
------------------------------------------------------------
Core ID              : 0
Status               : IDLE
Running Process      : NONE

READY QUEUE
------------------------------------------------------------
Front -> [4521] -> [3829] -> [5104] <- Back
SCHEDULER
------------------------------------------------------------
Algorithm            : FCFS
Next Process         : 4521
============================================================
```

### Paging Simulator Output
```
====================== Main Memory Data =======================
Frame number 0: 7 2 4 8 1 3 2 9
Frame number 1: 5 1 9 6 3 8 2 7
==============================================================

====================== Page Table ==========================
Page number 0 is present in frame: 1
==============================================================

Total frame are: 2
Total page are: 2
Logical address: 00000101
Physical address: 10000101
Original value is: 5
```

### Banker's Algorithm Output
```
The availability of Resources are given below:
Process execution order: P1 P2 P3

--------------------------------------------
| PSID | Alloc Res | Max--Need | Remn-Need |
|  P0  |  3 3 2   |  3 3 2   |  0 0 0   |
|  P1  |  2 0 0   |  4 2 1   |  2 2 1   |
|  P2  |  3 0 1   |  5 1 1   |  2 1 0   |
--------------------------------------------
```

---

## Learning Outcomes

This project demonstrates proficiency with:

✓ **Process Scheduling** – FCFS and Round-Robin algorithms  
✓ **Memory Management** – Paging, frame allocation, address translation  
✓ **Deadlock Prevention** – Banker's Algorithm and safe states  
✓ **Data Structures** – Ready queues, page tables, frame managers  
✓ **System Concepts** – Process lifecycle, CPU states, memory hierarchy  
✓ **Bit Manipulation** – Binary address representation and translation  
✓ **Complex Simulations** – Integrated OS components working together  

---

## Key Concepts Implemented

### Process States
- **NEW** – Process created
- **READY** – Waiting in queue for CPU
- **RUNNING** – Executing on CPU
- **TERMINATED** – Completed execution

### Memory Concepts
- **Logical Address** – Address from process perspective (page number + offset)
- **Physical Address** – Actual RAM address (frame number + offset)
- **Page Table** – Maps logical pages to physical frames
- **Frame** – Fixed-size block of physical memory
- **Page** – Fixed-size block of process virtual memory

### Resource Allocation
- **Allocated** – Resources given to process
- **Max Need** – Maximum resources process will request
- **Remaining Need** – Still-required resources
- **Available** – Free resources in system

---

## Technical Notes

- **Memory Management:** Manual memory allocation with `new`/`delete` for educational clarity
- **Hardcoded Values:** Banker's Algorithm uses 3 processes and 3 resources for simplicity
- **Random Generation:** Process PIDs and memory values use `rand()` for variation
- **Educational Focus:** Prioritizes algorithm clarity over production optimization
- **Console-Based:** All programs are interactive terminal applications

---

## File Organization

**Core Algorithms (Small, Focused):**
- `First_Come_First_Serve.cpp` – ~2.5 KB
- `CPU_Management.cpp` – ~7 KB
- `Memory_Management.cpp` – ~6.5 KB
- `Banker's_Algorithm.cpp` – ~5 KB
- `Operating_System_Paging_Simulator_v1.0.cpp` – ~6 KB

**Integrated Simulations (Large, Comprehensive):**
- `Operating_System_Simulator_v1.0.cpp` – ~28 KB
- `Operating_System_Simulator_v1.1.cpp` – ~34 KB
- `Operating_System_Simulator_v2.0.cpp` – ~35 KB
- `Operating_System_Process,CPU & Memory_with_Round_Robin.cpp` – ~50 KB
- `OS_caried_by_fazal_qadir.cpp` – ~51 KB

**Utilities:**
- `input_to_8(bit)binary.cpp` – Binary conversion tool
- `Process_Management_and_Physical_Memory_Access_v1.0_In_Complete.cpp` – In-progress

---

## Getting Started

1. **Choose a Program:**
   - Start with `First_Come_First_Serve.cpp` for basic scheduling
   - Then explore `CPU_Management.cpp` for queue simulation
   - Proceed to `Operating_System_Simulator_v2.0.cpp` for full integration

2. **Compile & Run:**
   ```bash
   g++ -std=c++11 filename.cpp -o output
   ./output
   ```

3. **Follow Prompts:**
   - Enter system parameters (RAM size, process count, etc.)
   - Observe algorithm execution and statistics

4. **Review Code:**
   - Study how data structures manage OS concepts
   - Trace algorithm execution step-by-step

---

## Recommendations for Learning

| Level | Programs to Study |
|-------|-------------------|
| **Beginner** | Binary conversion, FCFS scheduling |
| **Intermediate** | CPU Management, Memory Management |
| **Advanced** | Banker's Algorithm, Full OS Simulators |

---

## License

Educational project. Free to use for learning and portfolio purposes.

---

**Repository Statistics:**
- **Created:** April 30, 2026
- **Last Updated:** September 7, 2026
- **Language:** C++ (100%)
- **Files:** 12+
- **Total Lines of Code:** ~10,000+
- **Focus:** OS algorithms, system programming, education
