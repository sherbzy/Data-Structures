//
// Created by Lauren Sherburne on 4/13/2020.
//

#include "clock_time.h"

//construct a clock_time object representing midnight
clock_time::clock_time() {
    _seconds = 0;
}

//construct a clock_time object representing the same time as an object after calling set_time(h, m, s)
clock_time::clock_time(int h, int m, int s) {
    set_time(h, m, s);
}

//get the hour part of the time
int clock_time::get_hour() {
    return _seconds / 3600;
}

//get the minute part of the time
int clock_time::get_minute() {
    return (_seconds % 3600) / 60;
}

//get the second part of the time
int clock_time::get_second() {
    return _seconds % 60;
}

//set the time to the time that would exist h hours, m minutes, and s seconds after midnight
void clock_time::set_time(int h, int m, int s) {
    int hours, mins;

    //check for negative hours
    if (h < 0) {
        h = 24 + h;
    }
    hours = h * 3600;

    //check for negative minutes
    if (m < 0) {
        hours += (m * 60);
        mins = 0;
    } else {
        mins = m * 60;
    }

    //check for negative seconds
    if (s < 0) {
        hours += s;
        s = 0;
    }

    _seconds = hours + mins + s;

    //check for overflow and change the time accordingly
    while (_seconds > (24 * 60 * 60) - 1) {
        _seconds -= 24 * 60 * 60;
    }
}

//EXTRA CREDIT OPTION 1
//return the human-readable time as a string
string to_string(clock_time c) {
    //determine if the user would like the clock printed in 24-hour or 12-hour format
    bool format = true;
    cout << "Would you like the time in 24-hour format or 12-hour format?" << endl;
    string userInput;
    cin >> userInput;
    if (userInput == "12" || userInput == "12-hour" || userInput == "12-hour format") {
        format = false;
    }

    //create a string listing the time based on the user's response
    string time;
    string distinction;
    if (format) {
        time += std::to_string(c.get_hour()) + ':';
        distinction = "";
    } else {
        int hour = c.get_hour();
        distinction = "AM";
        if (hour >= 12) {
            distinction = "PM";
            hour -= 12;
        }
        time += std::to_string(hour) + ':';
    }

    if (c.get_minute() < 10) {
        time += '0' + std::to_string(c.get_minute()) + ':';
    } else {
        time += std::to_string(c.get_minute()) + ':';
    }

    if (c.get_second() < 10) {
        time += '0' + std::to_string(c.get_second());
    } else {
        time += std::to_string(c.get_second());
    }
    time += distinction;

    //cout << time << endl;
    return time;
}

//output the human-readable time to the output stream out
ostream & operator<<(ostream & out, clock_time c) {
    out << to_string(c);
}

//friend function that checks for equality
bool operator==(clock_time a, clock_time b) {
    if (a.get_hour() == b.get_hour()) {
        if (a.get_minute() == b.get_minute()) {
            if (a.get_second() == b.get_second()) {
                return true;
            }
        }
    }
    return false;
}

//friend function that checks for inequality
bool operator!=(clock_time a, clock_time b){
    if (a.get_hour() != b.get_hour()) {
        return true;
    }
    if (a.get_minute() != b.get_minute()) {
        return true;
    }
    if (a.get_second() != b.get_second()) {
        return true;
    }
    return false;
}

//friend function that adds two times
clock_time operator+(clock_time a, clock_time b) {
    int hours, mins, seconds;
    hours = a.get_hour() + b.get_hour();
    mins = a.get_minute() + b.get_minute();
    seconds = a.get_second() + b.get_second();
    clock_time c;
    c.set_time(hours, mins, seconds);
    return c;
}

//EXTRA CREDIT OPTION 2
//use the computer's clock to set the clock object to the current time
void clock_time::set_now() {
    //first, get the current time
    time_t currentTime = time(nullptr);
    struct tm *tmp = localtime(&currentTime);

    //then, determine values for the hours, minutes and seconds
    int hours, mins, seconds;
    hours = tmp->tm_hour;
    cout << "hour: " << hours << endl;
    mins = tmp->tm_min;
    cout << "minute: " << mins << endl;
    seconds = tmp->tm_sec;
    cout << "second: " << seconds << endl;

    //finally, set the time using the values found
    set_time(hours, mins, seconds);
}