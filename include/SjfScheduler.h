#pragma once
#include "IScheduler.h"

class SjfScheduler : public IScheduler {
public:
    ScheduleResult schedule(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) override;
};