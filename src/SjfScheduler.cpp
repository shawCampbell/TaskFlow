#include "SjfScheduler.h"
#include <algorithm>

ScheduleResult SjfScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots) {
    std::vector<Task> sorted = tasks; // Make a copy to sort
    std::sort(sorted.begin(), sorted.end(), [](const Task& a, const Task& b) {
        return a.timeSlots < b.timeSlots;
    });

    ScheduleResult result;
    result.totalTimeUsed = 0;

    for (const Task& task : sorted) {
        if (result.totalTimeUsed + task.timeSlots <= timeLimitSlots) {
            result.scheduledTasks.push_back(task);
            result.totalTimeUsed += task.timeSlots;
        } else {
            result.deferredTasks.push_back(task);
        }
    }

    return result;
}