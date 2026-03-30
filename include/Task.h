#pragma once
#include <string>
#include "Priority.h"
#include "Time.h"

struct Task {
    int         id;
    std::string name;
    int         timeSlots;
    Priority    priority;
    Time releaseTime;
    Time deadline;
};