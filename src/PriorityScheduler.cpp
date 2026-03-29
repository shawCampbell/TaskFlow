#include "PriorityScheduler.h"
#include <algorithm>

struct TaskState {
    Task task;
    int  remainingSlots;
    bool completed;
};

static int urgencyBoost(const TaskState& state, const Time& current) {
    Time projectedEnd = current;
    projectedEnd.addSlots(state.remainingSlots);
    int slotsUntilDeadline = (state.task.deadline.toTotalMinutes() - current.toTotalMinutes()) / 30;

    if (slotsUntilDeadline <= 2) return 3;
    if (slotsUntilDeadline <= 4) return 2;
    if (slotsUntilDeadline <= 6) return 1;
    return 0;
}

static int effectivePriority(const TaskState& state, const Time& current) {
    return (static_cast<int>(state.task.priority) * 2) + urgencyBoost(state, current);
}

ScheduleResult PriorityScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) {
    std::vector<TaskState> states;
    for (const Task& task : tasks) {
        states.push_back({task, task.timeSlots, false});
    }

    ScheduleResult result;
    result.totalTimeUsed = 0;
    Time current = startTime;

    for (int slot = 0; slot < timeLimitSlots; slot++) {
        TaskState* best = nullptr;
        int bestPriority = -1;

        for (TaskState& state : states) {
            if (state.completed) continue;

            bool released     = state.task.releaseTime <= current;
            Time projectedEnd = current;
            projectedEnd.addSlots(state.remainingSlots);
            bool meetsDeadline = projectedEnd <= state.task.deadline;

            if (released && meetsDeadline) {
                int ep = effectivePriority(state, current);
                if (ep > bestPriority) {
                    bestPriority = ep;
                    best = &state;
                }
            }
        }

        if (best == nullptr) {
            current.addSlots(1);
            continue;
        }

        best->remainingSlots--;
        result.totalTimeUsed++;
        current.addSlots(1);

        if (best->remainingSlots == 0) {
            best->completed = true;
            result.scheduledTasks.push_back(best->task);
        }
    }

    for (const TaskState& state : states) {
        if (!state.completed) {
            result.deferredTasks.push_back(state.task);
        }
    }

    return result;
}