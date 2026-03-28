# Problem Statement
### Project: TaskFlow — A CPU-Inspired Task Scheduler in C++
TaskFlow is a back-end C++ application that accepts a set of user-defined tasks and schedules them across a fixed time window (default: 10 hours / 600 minutes) using a selected scheduling algorithm adapted from classical CPU scheduling theory.

<img src="./Design/OO Design.drawio.png" height="500" style="margin-left:10; border-radius:2%;">

**Each task carries:**

- A name / description
- An estimated duration (in minutes)
- A priority level (1–5)
- An arrival index (the order in which it was added)

**The system will support the following scheduling strategies:**

- FCFS — tasks are scheduled in the order they arrived
- SJF (non-preemptive) — shortest tasks are scheduled first to maximise throughput
- Priority Scheduling — higher-priority tasks are scheduled first, with FCFS as a tiebreaker
- Round Robin (stretch goal) — tasks are given fixed time slices (quantum), cycling until complete or time runs out

**The scheduler will:**

- Build a schedule that fits within the selected time window
- Track which tasks were completed and which were left out
- Report a clean summary: scheduled tasks in order, total time used, and a list of deferred tasks

# Design Decisions 

## Models
- Tasks will be multiples of 30 minutes. This felt like a natural primitive unit of time 
- The 'CPU-burst' is the task duration
- Arrival times of tasks are not included because humans often have their tasks before making a schedule. This also means our scheduling algorithms can assume all tasks have the same arrival time.

## ISchedular Interface 
- 'schedule' method takes a vector of tasks as a constant reference, as to not unncessarily have mutable types. All types should be constant by default when programming.