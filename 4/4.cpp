#include "4.hpp"
#include <string>
#include <iomanip>
#include <vector>

using std::cout, std::endl, std::vector, std::string_view, std::string;

Time::Time(int hours, int minutes, int seconds) {
    mHours = hours;
    mMinutes = minutes;
    mSeconds = seconds;
}

Time::Time(string_view s) {
    string buf;
    buf = s.substr(0, 2);
    mHours = stoi(buf);
    buf = s.substr(3, 2);
    mMinutes = stoi(buf);
    buf = s.substr(6, 2);
    mSeconds = stoi(buf);
}

Time::Time():Time(0, 0, 0) {
};

Time Time::operator+(Time b) const {
    return Time((mHours + b.mHours + (mMinutes + b.mMinutes) / 60) % 24, (mMinutes + b.mMinutes + (mSeconds + b.mSeconds) / 60) % 60, (mSeconds + b.mSeconds) % 60);
}

int Time::hours() const {
    return mHours;
}

int Time::minutes() const {
    return mMinutes;
}

int Time::seconds() const {
    return mSeconds;
}

vector<Time> getTimesFromString(string_view s) {
    vector<Time> res;
    for (int i = 0, size = s.size(); i < size; i += 9) {
	res.push_back(Time(s.substr(i, 9)));
    }
    return res;
}

Time sumTimes(const vector < Time > &v) {
    Time res;
    for (int i = 0, size = v.size(); i < size; i++) {
	res = res + v[i];
    }
    return res;
}

std::ostream & operator<<(std::ostream & out, Time t) {
    out << std::setw(2) << std::setfill('0') << t.mHours << ":"	<< std::setw(2) << std::setfill('0') << t.mMinutes << ":" << std::setw(2) << std::setfill('0') << t.mSeconds;
    return out;
}
