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
	void setTime(int h, int m);
	void operator = (const Time &t2);
	bool operator == (const Time &t2);
	void operator ++ ();
	Time operator + (const Time &t2);
	Time operator + (int minute);
	int operator - (const Time &t2);
	void printTime();
	int GetHour();
	int GetMin();
};

