#pragma once
class Time
{

private:
	int sec;
	int min;
	int hour;

public:
	Time(int hr, int minute);
	void operator = (Time t2);
};

