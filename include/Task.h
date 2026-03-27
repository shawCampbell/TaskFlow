#pragma once
#include <string>
#include "Priority.h"

struct Task {
    int         id;
    std::string name;
    int         durationHalfHours;
    Priority    priority;
};