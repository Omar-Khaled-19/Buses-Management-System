#pragma once
#include "Event.h"
#include "Station.h"
class ArrivalEvent : public Event
{
	Station end_station;
	string type;

public:
	
	ArrivalEvent(int ID, string Type, Station* sStation, Station* eStation, Time Arr_time);
	void Excute();
};

