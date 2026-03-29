#pragma once
#include <string>

struct Time {
    int hours;
    int minutes;

    Time(int h, int m) : hours(h), minutes(m) {}

    void addSlots(int slots) {
        minutes += slots * 30;
        hours += minutes / 60;
        minutes = minutes % 60;
    }

    std::string toString() const {
        char buf[6];
        snprintf(buf, sizeof(buf), "%02d:%02d", hours, minutes);
        return std::string(buf);
    }
};