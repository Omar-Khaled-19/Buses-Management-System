#pragma once
#include "Event.h"
#include "Station.h"
class ArrivalEvent : public Event
{
	Station* end_station;
	string type;
	string Stype;

public:
	
	ArrivalEvent(int ID, string Type,string Stype, Station* sStation, Station* eStation, Time etime);
	Time get_event_time();
	void Excute();
};

