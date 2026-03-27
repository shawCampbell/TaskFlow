#pragma once
#include <memory>
#include "IScheduler.h"

enum class SchedulerType {
    SJF,
    Priority
};

class SchedulerFactory {
public:
    static std::unique_ptr<IScheduler> create(SchedulerType type);
};