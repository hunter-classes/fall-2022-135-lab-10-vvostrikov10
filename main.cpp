#include <iostream>
#include "funcs.h"
#include "time.h"

int main(){
    Time now;
    now.h = 17;
    now.m = 45;
    Time later;
    later.h = 19;
    later.m = 50;
    std::cout << minutesSinceMidnight(now) << std::endl;
    std::cout << minutesUntil(now, later) << std::endl;
    std::cout << minutesSinceMidnight(addMinutes(now, 2870)) << std::endl;
    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};
    TimeSlot morning = {movie1, {9, 15}};
    TimeSlot morning2 = {movie1, {9, 16}};
    TimeSlot next = scheduleAfter(morning, movie2);
    std::cout << getMovie(movie1) << std::endl;
    std::cout << getTimeSlot(morning) << std::endl;
    std::cout << getTimeSlot(next) << std::endl;
    std::cout << timeOverlap(morning, next) << std::endl;
    std::cout << timeOverlap(morning, morning2) << std::endl;
}