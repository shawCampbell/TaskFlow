#pragma once
#include <memory>
#include <vector>
#include "IScheduler.h"
#include "Task.h"
#include "ScheduleResult.h"

class SchedulerContext {
public:
    explicit SchedulerContext(std::unique_ptr<IScheduler> scheduler);
    ScheduleResult run(const std::vector<Task>& tasks, int timeLimitSlots);

private:
    std::unique_ptr<IScheduler> scheduler_;
};