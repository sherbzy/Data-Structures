//
// Created by Lauren Sherburne on 4/13/2020.
//

#ifndef LAB_5_CLOCK_TIME_H
#define LAB_5_CLOCK_TIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;


class clock_time {
public:
    int get_hour();                         //get the hour part of the time
    int get_minute();	                    //get the minute part of the time
    int get_second();	                    //get the second part of the time
    void set_time(int h, int m, int s);	    //set the time to the time that would exist at h hours, m minutes, and
                                            //s seconds after midnight

    clock_time();	                        //construct a clock_time object representing midnight
    clock_time(int h, int m, int s);	    //construct a clock_time object representing the same time as an object
                                            // after calling set_time(h, m, s)
    void set_now();                         //use the computer's clock to set the clock object to the current time
private:
    int _seconds;

public:
    friend bool operator==(clock_time a, clock_time b);         //checks for equality
    friend bool operator!=(clock_time a, clock_time b);         //checks for inequality
    friend clock_time operator+(clock_time a, clock_time b);    //adds two times
};

//output the human-readable time to the output stream out
ostream & operator<<(ostream & out, clock_time c);

//return the human-readable time as a string
string to_string(clock_time c);


#endif //LAB_5_CLOCK_TIME_H
