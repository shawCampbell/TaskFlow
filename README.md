# TaskFlow — A CPU-Inspired Task Scheduler in C++

TaskFlow is a back-end C++ application that accepts a set of user-defined tasks and schedules them across a fixed time window using scheduling algorithms adapted from classical CPU scheduling theory. Tasks are scheduled in half-hour slots, and any tasks that cannot fit within the window or meet their constraints are flagged as deferred.

<img src="./Design/OO Design.drawio.png" height="500" style="margin-left:10; border-radius:2%;">

---

## Task Model

Each task carries:

- A name
- A duration in half-hour slots (e.g. 2 slots = 1 hour)
- A priority level: `VeryLow`, `Low`, `Medium`, `High`, `Critical`
- A release time - the earliest the task may start
- A deadline - the latest the task must finish by

Arrival times are not modelled because in personal scheduling, all tasks are known upfront. This means all scheduling algorithms can safely assume equal arrival times.

---

## Scheduling Algorithms

### Shortest Job First (SJF)

Tasks are sorted by duration, shortest first. In the case of a tie, the higher priority task runs first. The scheduler greedily fills the time window, skipping any task that cannot finish before its deadline. This algorithm maximises throughput - the number of tasks completed - but may deprioritise important long tasks.

### Priority Scheduling

Rather than a static sort, this scheduler re-evaluates each task's effective priority at every scheduling step using:

```
effectivePriority = (userPriority * 2) + urgencyBoost
```

The urgency boost increases as a task's deadline approaches:

| Slots until deadline | Boost |
|---|---|
| <= 2 | +3 |
| <= 4 | +2 |
| <= 6 | +1 |
| > 6  |  0 |

This is a form of **aging** - a classical technique that prevents high-priority tasks from being starved as time runs on. The scheduler always selects the feasible task with the highest effective priority at the current moment.

Both algorithms are **non-preemptive** - once a task starts, it runs to completion. This is appropriate for human task scheduling where interrupting work mid-task is undesirable.

---

## Performance Metrics

After scheduling, TaskFlow reports:

- **Response time** - time from release until the task first starts
- **Waiting time** - total time spent not running (in non-preemptive scheduling this equals response time)
- **Throughput** - tasks completed per hour

---

## Design

TaskFlow uses two classical design patterns to keep the architecture clean and extensible.

### Strategy Pattern

Each scheduling algorithm is encapsulated in its own class that implements the `IScheduler` interface. The client never depends on a concrete scheduler — it only ever calls `schedule()` on the interface. Adding a new algorithm requires no changes to existing code.

### Factory Pattern

`SchedulerFactory` is responsible for instantiating the correct scheduler based on user input. This keeps object construction out of `main` and in one dedicated place.

```
Client (main)
    -> SchedulerFactory::create(SchedulerType)
        -> returns unique_ptr<IScheduler>
    -> SchedulerContext(strategy)
    -> context.run(tasks, timeLimit, startTime)
        -> returns ScheduleResult
```

### Key Design Decisions

- `IScheduler::schedule()` takes tasks as a `const` reference — schedulers make their own internal copy if sorting is needed, leaving the caller's data untouched
- `Task` is a plain `struct` — it holds data only, with no behaviour
- `CompletedTask` is separate from `Task` — scheduling metadata (start time, completion time, metrics) does not pollute the input model
- `TaskState` is a local struct inside each scheduler — transient scheduling state has no reason to exist outside the algorithm that uses it

---

## Project Structure

```
TaskFlow/
├── CMakeLists.txt
├── include/
│   ├── Priority.h
│   ├── Task.h
│   ├── Time.h
│   ├── CompletedTask.h
│   ├── ScheduleResult.h
│   ├── IScheduler.h
│   ├── SchedulerContext.h
│   ├── SchedulerFactory.h
│   ├── SjfScheduler.h
│   └── PriorityScheduler.h
└── src/
    ├── main.cpp
    ├── SchedulerContext.cpp
    ├── SchedulerFactory.cpp
    ├── SjfScheduler.cpp
    └── PriorityScheduler.cpp
```

---

## Sample Results

Both schedulers were run against the same 20-task set over a 36-hour window starting at 08:00.

### SJF

```
[09:00 - 09:30]  Team standup meeting  (Critical)
[11:00 - 11:30]  Client call  (Critical)
[14:00 - 15:00]  Deploy to staging  (High)
[15:00 - 16:00]  Update dependencies  (Low)
[16:00 - 17:00]  Write release notes  (Very Low)
[17:00 - 18:30]  Fix UI bugs  (Medium)
[18:30 - 20:30]  Architecture review  (High)
[20:30 - 22:30]  Performance profiling  (Medium)
[22:30 - Day2 00:30]  Research new framework  (Low)
[Day2 00:30 - Day2 03:30]  Write documentation  (Very Low)

Tasks completed: 10  |  Deferred: 10  |  Throughput: 0.69 tasks/hour
Avg response time: 390 mins  |  Avg waiting time: 390 mins
```

SJF completed 10 tasks by favouring short ones, but deferred several important tasks including `Fix critical bug (Critical)` and `Write project report (High)` because their durations pushed them down the sort order.

### Priority

```
[09:00 - 09:30]  Team standup meeting  (Critical)
[09:30 - 11:00]  Fix critical bug  (Critical)
[11:00 - 11:30]  Client call  (Critical)
[11:30 - 12:30]  Sprint planning  (High)
[12:30 - 15:30]  Write project report  (High)
[15:30 - 16:30]  Deploy to staging  (High)
[16:30 - 19:30]  Security audit  (High)
[19:30 - 21:30]  Architecture review  (High)
[21:30 - Day2 00:00]  Refactor auth module  (Medium)
[Day2 00:00 - Day2 02:00]  Performance profiling  (Medium)
[Day2 02:00 - Day2 04:00]  Research new framework  (Low)
[Day2 04:00 - Day2 05:00]  Write release notes  (Very Low)

Tasks completed: 12  |  Deferred: 8  |  Throughput: 0.60 tasks/hour
Avg response time: 402.5 mins  |  Avg waiting time: 402.5 mins
```

Priority completed 2 more tasks and scheduled all three Critical tasks early. Throughput is lower than SJF because it willingly schedules longer high-priority tasks rather than optimising for count. The urgency boost visibly influenced the order - lower priority tasks with approaching deadlines were pulled forward over higher priority tasks with more time to spare.

---

## Building and Running (Windows)

```powershell
# First time only
mkdir build
cd build
cmake .. -G "MinGW Makefiles"

# Every subsequent change
mingw32-make
.\TaskFlow.exe
```
