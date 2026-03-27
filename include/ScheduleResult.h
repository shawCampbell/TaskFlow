#pragma once
#include <vector>
#include "Task.h"

struct ScheduleResult {
    std::vector<Task> scheduledTasks;
    std::vector<Task> deferredTasks;
    int               totalTimeUsed;
};