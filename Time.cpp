#include "Time.h"

Time::Time()
{
	hour = 0;
	min = 0;
	sec = 0;
}

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

bool Time::operator==(Time t2)
{
	if (min == t2.min && hour == t2.hour)
		return true;

	return false;
}

void Time::operator++()
{
	min++;
	if (min == 60) {
		min = 0;
		hour++;
	}
	if (hour == 24) {
		hour = 0;
		min = 0;
		sec = 0;
	}
	
}
void Time:: printTime()
{
	cout << "Current Time (Hour:Min)==> " << hour << ":" << min<<endl;
}
