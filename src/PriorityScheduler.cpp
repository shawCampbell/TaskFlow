#include "PriorityScheduler.h"
#include <algorithm>

ScheduleResult PriorityScheduler::schedule(const std::vector<Task>& tasks, int timeLimitSlots) {
    std::vector<Task> sorted = tasks;
    std::sort(sorted.begin(), sorted.end(), [](const Task& a, const Task& b) {
        return static_cast<int>(a.priority) > static_cast<int>(b.priority);
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