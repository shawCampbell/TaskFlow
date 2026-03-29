#include "PriorityScheduler.h"
#include <algorithm>

static int urgencyBoost(const Task& task, const Time& current) {
    int slotsUntilDeadline = (task.deadline.toTotalMinutes() - current.toTotalMinutes()) / 30;
    if (slotsUntilDeadline <= 2) return 3;
    if (slotsUntilDeadline <= 4) return 2;
    if (slotsUntilDeadline <= 6) return 1;
    return 0;
}

static int effectivePriority(const Task& task, const Time& current) {
    return (static_cast<int>(task.priority) * 2) + urgencyBoost(task, current);
}

ScheduleResult PriorityScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) {
    std::vector<Task> remaining = tasks;

    ScheduleResult result;
    result.totalTimeUsed = 0;
    Time current = startTime;

    while (!remaining.empty()) {
        // find highest effective priority task that is feasible right now
        auto best = remaining.end();
        int bestPriority = -1;

        for (auto it = remaining.begin(); it != remaining.end(); ++it) {
            Time taskStart = (it->releaseTime > current) ? it->releaseTime : current;
            Time taskEnd   = taskStart;
            taskEnd.addSlots(it->timeSlots);

            bool withinTimeLimit = (result.totalTimeUsed + it->timeSlots) <= timeLimitSlots;
            bool meetsDeadline   = taskEnd <= it->deadline;

            if (withinTimeLimit && meetsDeadline) {
                int ep = effectivePriority(*it, current);
                if (ep > bestPriority) {
                    bestPriority = ep;
                    best = it;
                }
            }
        }

        // no feasible task found
        if (best == remaining.end()) break;

        Time taskStart = (best->releaseTime > current) ? best->releaseTime : current;
        Time taskEnd   = taskStart;
        taskEnd.addSlots(best->timeSlots);

        CompletedTask ct;
        ct.task           = *best;
        ct.startTime      = taskStart;
        ct.completionTime = taskEnd;
        ct.responseTime   = (taskStart.toTotalMinutes() - best->releaseTime.toTotalMinutes()) / 30;
        ct.waitingTime    = ct.responseTime;
        result.scheduledTasks.push_back(ct);
        result.totalTimeUsed += best->timeSlots;
        current = taskEnd;

        remaining.erase(best);
    }

    // anything left is deferred
    for (const Task& task : remaining) {
        result.deferredTasks.push_back(task);
    }

    return result;
}