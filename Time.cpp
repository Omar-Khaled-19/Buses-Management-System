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

void Time:: setTime(int h, int m)
{
	hour = h;
	min = m;
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
Time Time::operator+(Time t2)
{
	Time new_time;
	if (min + t2.min < 60) {
		new_time.hour = hour + t2.hour;
		new_time.min = min + t2.min;
		return new_time;
	}
	new_time.hour = hour + t2.hour +1;
	new_time.min = min + t2.min - 60;
	return new_time;
}
Time Time::operator+(int minute)
{
	Time new_time;
	if (minute + min < 60) {
		new_time.min = min + minute;
		new_time.hour = hour;
		return new_time;
	}
	new_time.min = min + minute - 60;
	new_time.hour = hour + 1;
	return new_time;
}

int Time:: operator -(Time t2)
{
	if (hour == t2.hour)
		return min - t2.min;
	else
		return ((60 - min) + t2.min) * (hour - t2.hour);
}

void Time:: printTime()
{
	cout << "Current Time (Hour:Min)==> " << hour << ":" << min<<endl;

Time Time:: operator - (const Time &t2)
{
	Time t3;
	if (min >= t2.min)
	{
		t3.min = min - t2.min;
		t3.hour = hour - t2.hour;
	}
	else
	{
		hour--;
		min = min + 60;
		t3.min = min - t2.min;
		t3.hour = hour - t2.hour;
	}
	return t3;
}

int Time::GetHour()
{
	return hour;
}

int Time::GetMinute()
{
	return min;
}
