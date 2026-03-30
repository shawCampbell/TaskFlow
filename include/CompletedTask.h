#pragma once
#include "Task.h"
#include "Time.h"

struct CompletedTask {
    Task task;
    Time startTime;
    Time completionTime;
    int  responseTime;   // slots from release to first start
    int  waitingTime;    // slots spent not running
};