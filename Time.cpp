#include "Time.h"

Time::Time(int hr, int minute)
{
	hour = hr;
	min = minute;
	sec = 0;
}
void Time::operator=(Time t2)
{
	sec = t2.sec;
	min = t2.min;
	hour = t2.hour;
}
