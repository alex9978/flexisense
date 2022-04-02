
#ifndef FLEXITIMER_H
#define FLEXITIMER_H

#include <stdio.h>

#ifdef LINUX
	#include <sys/timex.h>
#elif WIN32
	#include <time.h>
#endif


class FlexiTimer
{
public:
    FlexiTimer() ;
    ~FlexiTimer() { }

    // Resets timer
    void reset();

    // Returns seconds since last reset
    float getSeconds();

    // Returns milliseconds since last reset
    unsigned long getMilliseconds();

    // Returns microseconds since last reset
    unsigned long getMicroseconds();

protected:
#ifdef LINUX
    ntptimeval zeroClock1,
               zeroClock2;
#elif WIN32
    clock_t zeroClock ;
#endif
};

#endif
