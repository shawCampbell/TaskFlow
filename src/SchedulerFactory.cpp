#include "SchedulerFactory.h"
#include "SjfScheduler.h"
#include "PriorityScheduler.h"

std::unique_ptr<IScheduler> SchedulerFactory::create(SchedulerType type) {
    switch (type) {
        case SchedulerType::SJF:      return std::make_unique<SjfScheduler>();
        case SchedulerType::Priority: return std::make_unique<PriorityScheduler>();
        default: throw std::invalid_argument("Unknown scheduler type");
    }
}