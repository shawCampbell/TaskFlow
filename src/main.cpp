#include <iostream>
#include <vector>
#include "Task.h"
#include "Priority.h"
#include "ScheduleResult.h"
#include "SchedulerContext.h"
#include "SchedulerFactory.h"
#include "Time.h"
#include <algorithm>


const char* priorityToString(Priority p) {
    switch (p) {
        case Priority::VeryLow:  return "Very Low";
        case Priority::Low:     return "Low";
        case Priority::Medium:  return "Medium";
        case Priority::High:    return "High";
        case Priority::Critical:return "Critical";
        default:               return "Unknown";
    }
}

void printMetrics(const ScheduleResult& result) {
    if (result.scheduledTasks.empty()) return;

    float avgResponseTime = 0;
    float avgWaitingTime  = 0;

    for (const CompletedTask& ct : result.scheduledTasks) {
        avgResponseTime += ct.responseTime;
        avgWaitingTime  += ct.waitingTime;
    }

    int n = result.scheduledTasks.size();
    avgResponseTime /= n;
    avgWaitingTime  /= n;

    float totalHours = result.totalTimeUsed * 0.5f;
    float throughput = n / totalHours;

    std::cout << "\n========== Metrics ==========\n";
    std::cout << "Tasks completed:       " << n << "\n";
    std::cout << "Tasks deferred:        " << result.deferredTasks.size() << "\n";
    std::cout << "Avg response time:     " << avgResponseTime << " slots ("  << avgResponseTime * 30 << " mins)\n";
    std::cout << "Avg waiting time:      " << avgWaitingTime  << " slots (" << avgWaitingTime  * 30 << " mins)\n";
    std::cout << "Throughput:            " << throughput << " tasks/hour\n";
    std::cout << "==============================\n";
}

void printResult(const ScheduleResult& result, Time startTime) {
    std::cout << "\n========== Schedule ==========\n";
    std::vector<CompletedTask> ordered = result.scheduledTasks;
    std::sort(ordered.begin(), ordered.end(), [](const CompletedTask& a, const CompletedTask& b) {
        return a.startTime < b.startTime;
    });
    for (const CompletedTask& ct : ordered) {
        std::cout << "[" << ct.startTime.toString() << " - " << ct.completionTime.toString() << "]"
                  << "  " << ct.task.name
                  << "  (" << priorityToString(ct.task.priority) << ")\n";
    }

    std::cout << "\nTotal time used: " << result.totalTimeUsed * 30 << " mins\n";

    if (!result.deferredTasks.empty()) {
        std::cout << "\n========== Deferred ==========\n";
        for (const Task& task : result.deferredTasks) {
            std::cout << "  - " << task.name
                      << "  (" << priorityToString(task.priority) << ")\n";
        }
    }
    std::cout << "==============================\n";
}

int main() {
    std::vector<Task> tasks = {
    {1,  "Write project report",       6,  Priority::High,     Time(8, 0),  Time(20, 0)},
    {2,  "Reply to emails",            1,  Priority::Low,       Time(8, 0),  Time(10, 0)},
    {3,  "Team standup meeting",       1,  Priority::Critical,  Time(9, 0),  Time(10, 0)},
    {4,  "Code review",                4,  Priority::Medium,    Time(10, 0), Time(18, 0)},
    {5,  "Write documentation",        6,  Priority::VeryLow,   Time(8, 0),  Time(30, 0)},
    {6,  "Fix critical bug",           3,  Priority::Critical,  Time(8, 0),  Time(12, 0)},
    {7,  "Design database schema",     4,  Priority::High,      Time(8, 0),  Time(16, 0)},
    {8,  "Sprint planning",            2,  Priority::High,      Time(10, 0), Time(14, 0)},
    {9,  "Refactor auth module",       5,  Priority::Medium,    Time(12, 0), Time(24, 0)},
    {10, "Deploy to staging",          2,  Priority::High,      Time(14, 0), Time(18, 0)},
    {11, "Write unit tests",           4,  Priority::Medium,    Time(8, 0),  Time(20, 0)},
    {12, "Client call",                1,  Priority::Critical,  Time(11, 0), Time(12, 0)},
    {13, "Research new framework",     4,  Priority::Low,       Time(8, 0),  Time(36, 0)},
    {14, "Fix UI bugs",                3,  Priority::Medium,    Time(9, 0),  Time(20, 0)},
    {15, "Performance profiling",      4,  Priority::Medium,    Time(16, 0), Time(30, 0)},
    {16, "Security audit",             6,  Priority::High,      Time(8, 0),  Time(24, 0)},
    {17, "Onboard new developer",      3,  Priority::Medium,    Time(10, 0), Time(16, 0)},
    {18, "Update dependencies",        2,  Priority::Low,       Time(8, 0),  Time(20, 0)},
    {19, "Architecture review",        4,  Priority::High,      Time(12, 0), Time(22, 0)},
    {20, "Write release notes",        2,  Priority::VeryLow,   Time(8, 0),  Time(36, 0)},
    };

    int timeLimitSlots = 72;

    std::cout << "Select scheduler:\n";
    std::cout << "1. SJF (Shortest Job First)\n";
    std::cout << "2. Priority\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    std::cout << "Enter start hour (e.g. 8 for 08:00): ";
    int startHour;
    std::cin >> startHour;
    Time startTime(startHour, 0);

    SchedulerType type = (choice == 1) ? SchedulerType::SJF : SchedulerType::Priority;

    SchedulerContext context(SchedulerFactory::create(type));
    ScheduleResult result = context.run(tasks, timeLimitSlots, startTime);

    printResult(result, startTime);
    printMetrics(result);

    return 0;
}