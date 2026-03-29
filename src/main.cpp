#include <iostream>
#include <vector>
#include "Task.h"
#include "Priority.h"
#include "ScheduleResult.h"
#include "SchedulerContext.h"
#include "SchedulerFactory.h"
#include "Time.h"


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

void printResult(const ScheduleResult& result, Time startTime) {
    std::cout << "\n========== Schedule ==========\n";
    Time current = startTime;
    for (const Task& task : result.scheduledTasks) {
        Time end = current;
        end.addSlots(task.timeSlots);
        std::cout << "[" << current.toString() << " - " << end.toString() << "]"
                  << "  " << task.name
                  << "  (" << priorityToString(task.priority) << ")\n";
        current = end;
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
        {1, "Write report",        4, Priority::High},
        {2, "Reply to emails",     1, Priority::Low},
        {3, "Team meeting",        2, Priority::Critical},
        {4, "Code review",         3, Priority::Medium},
        {5, "Documentation",       5, Priority::VeryLow},
        {6, "Fix critical bug",    2, Priority::Critical},
    };

    int timeLimitSlots = 12; // 12 slots = 6 hours

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
    ScheduleResult result = context.run(tasks, timeLimitSlots);

    printResult(result, startTime);

    return 0;
}