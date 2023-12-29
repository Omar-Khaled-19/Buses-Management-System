#pragma once
#include<iostream>
using namespace std;
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
	bool operator == (Time t2);
	void operator ++ ();
	Time operator + (Time t2);
	Time operator + (int minute);
	int operator - (Time t2);
	void printTime();
	Time operator - (const Time &t2);
	int GetHour()
	{
		return hour;
	}
	int GetMin()
	{
		return min;
	}
};

