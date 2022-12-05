#include <sys/time.h>
#include "myTimer.h"

struct timeval begin;
struct timeval end;

void startTimer() {

    gettimeofday(&begin, 0);
}

// Return time in ms
double stopTimer() {

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    return seconds * 1000 + (double) microseconds / 1000;
}