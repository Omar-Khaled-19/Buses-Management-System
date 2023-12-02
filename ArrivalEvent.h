#pragma once
#include "Event.h"
#include "Station.h"
class ArrivalEvent : public Event
{
	Station end_station;
	char type;

public:
	
	ArrivalEvent(int ID, char Type, Station sStation, Station eStation, Time Arr_time);
	void Excute();
};

