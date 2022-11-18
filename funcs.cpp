#include "time.h"
#include "movie.h"
#include "timeslot.h"
#include <string>

int minutesSinceMidnight(Time time){
    return 60 * time.h + time.m;
}

int minutesUntil(Time earlier, Time later){
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier); 
}

Time addMinutes(Time time0, int min){
    Time time1;
    time1.m = time0.m + min;
    time1.h = time0.h;
    time1.h += time1.m / 60;
    time1.m %= 60;
    time1.h %= 24;
    if (time1.m < 0){
        time1.h += (time1.m + 1)/60 - 1;
        time1.m += 60 * (-1) * ((time1.m + 1)/60 - 1);
    }
    if (time1.h < 0){
        time1.h += 24 * (-1) * ((time1.h + 1)/24 - 1);
    }
    return time1;
}



std::string getTime(Time time) {
    return std::to_string(time.h) + (time.m < 10? ":0" : ":") + std::to_string(time.m);
}


std::string getMovie(Movie mv){
    std::string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    return mv.title + " " + g + " (" + std::to_string(mv.duration) + " min)";
}

std::string getTimeSlot(TimeSlot ts){
    return getMovie(ts.movie) + " [starts at " + getTime(ts.startTime) + ", ends by " + getTime(addMinutes(ts.startTime, ts.movie.duration)) + "]";
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    TimeSlot nextTimeslot = {nextMovie, addMinutes(ts.startTime, ts.movie.duration)};
    return nextTimeslot;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    int start1 = minutesSinceMidnight(ts1.startTime);
    int end1 = minutesSinceMidnight(addMinutes(ts1.startTime, ts1.movie.duration));
    int start2 = minutesSinceMidnight(ts2.startTime);
    int end2 = minutesSinceMidnight(addMinutes(ts2.startTime, ts2.movie.duration));
    return start1 < end2 && start2 < end1;
}

