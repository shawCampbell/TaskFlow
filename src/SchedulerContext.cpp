#include "SchedulerContext.h"

SchedulerContext::SchedulerContext(std::unique_ptr<IScheduler> scheduler)
    : scheduler_(std::move(scheduler)) {}

ScheduleResult SchedulerContext::run(const std::vector<Task>& tasks, int timeLimitSlots, Time startTime) {
    return scheduler_->schedule(tasks, timeLimitSlots, startTime);
}