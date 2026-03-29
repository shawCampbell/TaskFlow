#include "SjfScheduler.h"
#include <algorithm>

ScheduleResult SjfScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) {
    std::vector<Task> sorted = tasks;
    std::sort(sorted.begin(), sorted.end(), [](const Task& a, const Task& b) {
        if (a.timeSlots != b.timeSlots)
            return a.timeSlots < b.timeSlots;
        return static_cast<int>(a.priority) > static_cast<int>(b.priority);
    });

    ScheduleResult result;
    result.totalTimeUsed = 0;
    Time current = startTime;

    for (const Task& task : sorted) {
        Time taskStart = current;
        
        // respect release time
        if (task.releaseTime > current) {
            taskStart = task.releaseTime;
        }

        Time taskEnd = taskStart;
        taskEnd.addSlots(task.timeSlots);

        bool withinTimeLimit = (result.totalTimeUsed + task.timeSlots) <= timeLimitSlots;
        bool meetsDeadline   = taskEnd <= task.deadline;

        if (withinTimeLimit && meetsDeadline) {
            CompletedTask ct;
            ct.task           = task;
            ct.startTime      = taskStart;
            ct.completionTime = taskEnd;
            ct.responseTime   = (taskStart.toTotalMinutes() - task.releaseTime.toTotalMinutes()) / 30;
            ct.waitingTime    = ct.responseTime; // non-preemptive: waiting = response time
            result.scheduledTasks.push_back(ct);
            result.totalTimeUsed += task.timeSlots;
            current = taskEnd;
        } else {
            result.deferredTasks.push_back(task);
        }
    }

    return result;
}