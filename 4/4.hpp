#pragma once
#include <string_view>
#include <iostream>
#include <vector>

using std::string_view, std::vector;

class Time {
private:
    int mHours = 0, mMinutes = 0, mSeconds = 0;
public:
    Time(int hours, int minutes, int seconds);
    Time();
    Time(string_view s);
    Time operator+(Time b) const;
    int hours() const; int minutes() const; int seconds() const;
    friend std::ostream& operator<<(std::ostream& out, Time t);
};

Time sumTimes(const vector<Time>& v);
vector<Time> getTimesFromString(string_view s);
