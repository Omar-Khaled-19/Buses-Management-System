#pragma once
#include "Event.h"
#include "Station.h"
class ArrivalEvent : public Event
{
	Station* end_station;
	string type;
	string Stype;

public:
	
	ArrivalEvent(int ID, string Type, Station* sStation, Station* eStation, Time etime, string Stype = "");
	Time get_event_time();
	void Excute();
};

