#include "Task.h"
#include "Priority.h"
#include "Time.h"
#include <vector>
    
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