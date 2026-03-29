#include "SjfScheduler.h"
#include <algorithm>

struct TaskState {
    Task task;
    int  remainingSlots;
    bool completed;
};

ScheduleResult SjfScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) {
    // Build local state for each task
    std::vector<TaskState> states;
    for (const Task& task : tasks) {
        states.push_back({task, task.timeSlots, false});
    }

    ScheduleResult result;
    result.totalTimeUsed = 0;
    Time current = startTime;

    for (int slot = 0; slot < timeLimitSlots; slot++) {
        // Find all released, incomplete tasks that can meet their deadline
        TaskState* best = nullptr;
        for (TaskState& state : states) {
            if (state.completed) continue;

            bool released      = state.task.releaseTime <= current;
            Time projectedEnd  = current;
            projectedEnd.addSlots(state.remainingSlots);
            bool meetsDealine  = projectedEnd <= state.task.deadline;

            if (released && meetsDealine) {
                if (best == nullptr || state.remainingSlots < best->remainingSlots) {
                    best = &state;
                }
            }
        }

        // No eligible task this slot, advance time and continue
        if (best == nullptr) {
            current.addSlots(1);
            continue;
        }

        // Run the best task for one slot
        best->remainingSlots--;
        result.totalTimeUsed++;
        current.addSlots(1);

        // Check if task is now complete
        if (best->remainingSlots == 0) {
            best->completed = true;
            result.scheduledTasks.push_back(best->task);
        }
    }

    // Any incomplete task is deferred
    for (const TaskState& state : states) {
        if (!state.completed) {
            result.deferredTasks.push_back(state.task);
        }
    }

    return result;
}