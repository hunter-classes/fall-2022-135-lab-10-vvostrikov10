#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "funcs.h"
#include "time.h"
#include "movie.h"
#include "timeslot.h"

TEST_CASE("<minutesSinceMidnight tests>"){
    Time testTime = {12,15};
    CHECK(minutesSinceMidnight(testTime) == 735);
    testTime = {0, 59};
    CHECK(minutesSinceMidnight(testTime) == 59);
    testTime = {3, 45};
    CHECK(minutesSinceMidnight(testTime) == 225);
    testTime = {6, 47};
    CHECK(minutesSinceMidnight(testTime) == 407);
    testTime = {16, 13};
    CHECK(minutesSinceMidnight(testTime) == 973);
}

TEST_CASE("<minutesUntil tests>"){
    Time testTime1 = {12, 15};
    Time testTime2 = {13, 59};
    CHECK(minutesUntil(testTime1, testTime2) == 104);
    CHECK(minutesUntil(testTime2, testTime1) == -104);
    testTime2 = {12, 15};
    CHECK(minutesUntil(testTime1, testTime2) == 0);
    testTime1 = {23, 00};
    CHECK(minutesUntil(testTime1, testTime2) == -645);
}

TEST_CASE("<getTime tests>"){
    Time testTime = {12, 40};
    CHECK(getTime(testTime) == "12:40");
    testTime = {13, 59};
    CHECK(getTime(testTime) == "13:59");
    testTime = {16, 50};
    CHECK(getTime(testTime) == "16:50");
    testTime = {1, 9};
    CHECK(getTime(testTime) == "1:09");
    testTime = {123, 403};
    CHECK(getTime(testTime) == "123:403");
}

TEST_CASE("<addMinutes tests>"){
    Time testTime = {10,40};
    CHECK(getTime(addMinutes(testTime, 60)) == "11:40");
    CHECK(getTime(addMinutes(testTime, 169)) == "13:29");
    CHECK(getTime(addMinutes(testTime, -169)) == "7:51");
    CHECK(getTime(addMinutes(testTime, 1440)) == "10:40");
    CHECK(getTime(addMinutes(testTime, -2881)) == "10:39");
}


TEST_CASE("<getMovie tests>"){
    Movie testMovie = {"The Empire Strikes Back", ACTION, 124};
    CHECK(getMovie(testMovie) == "The Empire Strikes Back ACTION (124 min)");
    testMovie.duration = 144;
    CHECK(getMovie(testMovie) == "The Empire Strikes Back ACTION (144 min)");
    testMovie.genre = THRILLER;
    CHECK(getMovie(testMovie) == "The Empire Strikes Back THRILLER (144 min)");
    testMovie.title = "Knives Out";
    CHECK(getMovie(testMovie) == "Knives Out THRILLER (144 min)");
}

TEST_CASE("<getTimeSlot tests>"){
    Movie testMovie = {"The Empire Strikes Back", ACTION, 124};
    TimeSlot testTimeslot = {testMovie, {12, 30}};
    CHECK(getTimeSlot(testTimeslot) == "The Empire Strikes Back ACTION (124 min) [starts at 12:30, ends by 14:34]");
    testTimeslot.movie.duration = 144;
    CHECK(getTimeSlot(testTimeslot) == "The Empire Strikes Back ACTION (144 min) [starts at 12:30, ends by 14:54]");
    testTimeslot.movie.genre = THRILLER;
    CHECK(getTimeSlot(testTimeslot) == "The Empire Strikes Back THRILLER (144 min) [starts at 12:30, ends by 14:54]");
    testTimeslot.movie.title = "Knives Out";
    CHECK(getTimeSlot(testTimeslot) == "Knives Out THRILLER (144 min) [starts at 12:30, ends by 14:54]");
    testTimeslot.startTime = {14, 24};
    CHECK(getTimeSlot(testTimeslot) == "Knives Out THRILLER (144 min) [starts at 14:24, ends by 16:48]");
}

TEST_CASE("<scheduleAfter tests>"){
    Movie testMovie = {"The Empire Strikes Back", ACTION, 124};
    TimeSlot testTimeslot = {testMovie, {12, 30}};
    CHECK(getTimeSlot(scheduleAfter(testTimeslot, testMovie)) == "The Empire Strikes Back ACTION (124 min) [starts at 14:34, ends by 16:38]");
    testTimeslot.startTime = {23, 0};
    CHECK(getTimeSlot(scheduleAfter(testTimeslot, testMovie)) == "The Empire Strikes Back ACTION (124 min) [starts at 1:04, ends by 3:08]");
    testTimeslot.startTime = {21, 0};
    CHECK(getTimeSlot(scheduleAfter(testTimeslot, testMovie)) == "The Empire Strikes Back ACTION (124 min) [starts at 23:04, ends by 1:08]");
}

TEST_CASE("<timeOverlap tests>"){
    Movie testMovie1 = {"The Empire Strikes Back", ACTION, 124};
    TimeSlot testTimeslot1 = {testMovie1, {12, 30}};
    Movie testMovie2 = {"Knives Out", THRILLER, 144};
    TimeSlot testTimeslot2 = {testMovie2, {13, 30}};
    CHECK(timeOverlap(testTimeslot1, testTimeslot2) == true);
    CHECK(timeOverlap(testTimeslot2, testTimeslot1) == true);
    testTimeslot2.startTime = {14, 34};
    CHECK(timeOverlap(testTimeslot1, testTimeslot2) == false);
    CHECK(timeOverlap(testTimeslot2, testTimeslot1) == false);
}



