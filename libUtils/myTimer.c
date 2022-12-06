#include <sys/time.h>
#include "myTimer.h"

clock_t start_t;
clock_t end_t;

void startTimer() {

    start_t = clock();
}

double stopTimer() {

    end_t = clock();
    return (double) (end_t - start_t) / CLOCKS_PER_SEC;
}

//struct timeval begin;
//struct timeval end;
//
//void startTimer() {
//
//    gettimeofday(&begin, 0);
//}
//
//// Return time in ms
//double stopTimer() {
//
//    gettimeofday(&end, 0);
//    long seconds = end.tv_sec - begin.tv_sec;
//    long microseconds = end.tv_usec - begin.tv_usec;
//    return seconds * 1000 + (double) microseconds / 1000;
//}