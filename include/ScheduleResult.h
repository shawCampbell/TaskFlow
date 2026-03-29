#pragma once
#include <vector>
#include "Task.h"
#include "CompletedTask.h"

struct ScheduleResult {
    std::vector<CompletedTask> scheduledTasks;
    std::vector<Task> deferredTasks;
    int               totalTimeUsed;
};