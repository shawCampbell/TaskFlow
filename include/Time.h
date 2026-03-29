#pragma once
#include <string>

struct Time {
    int hours;
    int minutes;

    Time(int h, int m) : hours(h), minutes(m) {}

    Time() : hours(0), minutes(0) {}

    void addSlots(int slots) {
        minutes += slots * 30;
        hours += minutes / 60;
        minutes = minutes % 60;
    }

    // Convert to total minutes for easy comparison
    int toTotalMinutes() const {
        return hours * 60 + minutes;
    }

    bool operator<(const Time& other) const {
        return toTotalMinutes() < other.toTotalMinutes();
    }

    bool operator<=(const Time& other) const {
        return toTotalMinutes() <= other.toTotalMinutes();
    }

    bool operator>(const Time& other) const {
        return toTotalMinutes() > other.toTotalMinutes();
    }

    bool operator>=(const Time& other) const {
        return toTotalMinutes() >= other.toTotalMinutes();
    }

    bool operator==(const Time& other) const {
        return toTotalMinutes() == other.toTotalMinutes();
    }

    std::string toString() const {
        char buf[6];
        snprintf(buf, sizeof(buf), "%02d:%02d", hours, minutes);
        return std::string(buf);
    }
};