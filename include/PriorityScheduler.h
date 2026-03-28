#pragma once
#include "IScheduler.h"

class PriorityScheduler : public IScheduler {
public:
    ScheduleResult schedule(const std::vector<Task>& tasks, int timeLimitSlots) override;
};