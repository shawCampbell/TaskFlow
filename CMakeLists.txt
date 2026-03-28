cmake_minimum_required(VERSION 3.15)
project(TaskFlow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(TaskFlow
    src/main.cpp
    src/SchedulerContext.cpp
    src/SchedulerFactory.cpp
    src/SjfScheduler.cpp
    src/PriorityScheduler.cpp
)