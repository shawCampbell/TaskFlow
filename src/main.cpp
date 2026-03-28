#include <iostream>
#include <vector>
#include "Task.h"
#include "Priority.h"
#include "ScheduleResult.h"
#include "SchedulerContext.h"
#include "SchedulerFactory.h"

void printResult(const ScheduleResult& result) {
    std::cout << "\n--- Scheduled Tasks ---\n";
    for (const Task& task : result.scheduledTasks) {
        std::cout << "[" << task.id << "] " << task.name
                  << " | Slots: " << task.timeSlots
                  << " (" << task.timeSlots * 30 << " mins)"
                  << " | Priority: " << static_cast<int>(task.priority) << "\n";
    }

    std::cout << "\nTotal time used: " << result.totalTimeUsed << " slots ("
              << result.totalTimeUsed * 30 << " mins)\n";

    if (!result.deferredTasks.empty()) {
        std::cout << "\n--- Deferred Tasks ---\n";
        for (const Task& task : result.deferredTasks) {
            std::cout << "[" << task.id << "] " << task.name << "\n";
        }
    }
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

    SchedulerType type = (choice == 1) ? SchedulerType::SJF : SchedulerType::Priority;

    SchedulerContext context(SchedulerFactory::create(type));
    ScheduleResult result = context.run(tasks, timeLimitSlots);

    printResult(result);

    return 0;
}