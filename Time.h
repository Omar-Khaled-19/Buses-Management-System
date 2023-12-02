#pragma once
class Time
{

private:
	int sec;
	int min;
	int hour;

public:
	Time(); // default constructor
	Time(int hr, int minute); // copy constructor
	void operator = (Time t2);
};

