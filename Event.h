#pragma once
#include "Time.h"
#include "Station.h"
class Event
{
protected:
	Station* st_station;
	Time event_time;
	int passenger_id;

public:
	virtual Time get_event_time() = 0;
	virtual void Excute() = 0;
};

