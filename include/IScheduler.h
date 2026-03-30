#pragma once
#include <vector>
#include "Task.h"
#include "ScheduleResult.h"

class IScheduler {
public:
    // Each concreate scheduler will make it's own internal copy if it needs to sort
    virtual ScheduleResult schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) = 0;
    virtual ~IScheduler() = default;
};

