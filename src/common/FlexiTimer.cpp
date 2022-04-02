
#include <FlexiSense/common/FlexiTimer.h>

FlexiTimer::FlexiTimer()
{
    reset();
}

void FlexiTimer::reset()
{
#ifdef LINUX    
	ntp_gettime(&zeroClock1);
#elif WIN32
	zeroClock = clock();
#endif
}

float FlexiTimer::getSeconds()
{
#ifdef LINUX
	ntp_gettime(&zeroClock2);
    float sec = zeroClock2.time.tv_sec - zeroClock1.time.tv_sec,
          usec = zeroClock2.time.tv_usec - zeroClock1.time.tv_usec;
    return sec + (usec / 1000000.0f);
	//return (float)zeroClock.time.tv_sec + (float)(zeroClock.time.tv_usec / (float)1000000);
#elif WIN32
	clock_t newClock = clock();
	return (float)(newClock - zeroClock) / (float)CLOCKS_PER_SEC;
#endif
}

unsigned long FlexiTimer::getMilliseconds()
{
#ifdef LINUX
	ntp_gettime(&zeroClock2);
    unsigned long sec = zeroClock2.time.tv_sec - zeroClock1.time.tv_sec,
                  usec = zeroClock2.time.tv_usec - zeroClock1.time.tv_usec;
    
	return (sec * 1000) + (usec / 1000);
    //return (zeroClock.time.tv_sec * 1000) + (zeroClock.time.tv_usec / 1000);
#elif WIN32
	clock_t newClock = clock();
	return (unsigned long)(((float)(newClock - zeroClock) / (float)CLOCKS_PER_SEC) * 1000);
#endif
}

unsigned long FlexiTimer::getMicroseconds()
{
#ifdef LINUX
	ntp_gettime(&zeroClock2);
    unsigned long sec = zeroClock2.time.tv_sec - zeroClock1.time.tv_sec,
                  usec = zeroClock2.time.tv_usec - zeroClock1.time.tv_usec;

	return (sec * 1000000) + usec;
    //return (zeroClock.time.tv_sec * 1000000) + (zeroClock.time.tv_usec);
#elif WIN32
	clock_t newClock = clock();
	return (unsigned long)(((float)(newClock - zeroClock) / (float)CLOCKS_PER_SEC) * 1000000);
#endif
}
