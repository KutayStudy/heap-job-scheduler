# Job Scheduler (C++)

This is a simple job scheduling application written in C++.  
It uses a dynamic binary heap (priority queue) under the hood to decide which job should run next.

I built this project mainly to practice data structures, memory management, and system-style programming in C++.

---

##  How it works

Each job has:

• id  
• name  
• priority (higher = more important)  
• arrival time  
• duration  
• remaining time  
• optional deadline  
• start and completion times  

Jobs are stored in a 1-based dynamic binary heap.  
Their order is determined by this rule:

1. Higher priority first  
2. If equal → earlier deadline first  
3. If equal → earlier arrival time first  
4. If equal → smaller id first  

So the “most urgent” job always stays at the top.

Scheduling is non-preemptive — once a job starts, it runs until it finishes.

---

## Features

✔ Dynamic binary heap (automatic resize, copy/assign/destructor implemented)  
✔ Add and cancel jobs  
✔ Run one job or run everything  
✔ Basic command-line interface  
✔ Tracks completed jobs  
✔ Shows average waiting & turnaround time  

---

## Build & Run

You need a C++17 compatible compiler.

Compile:

```bash
g++ -std=c++17 -Wall -Wextra Job.cpp BinaryHeap.cpp Scheduler.cpp main.cpp -o scheduler
