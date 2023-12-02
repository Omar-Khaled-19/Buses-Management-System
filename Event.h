#pragma once
#include "Time.h"
#include "Station.h"
class Event
{
protected:
	Station st_station;
	Time event_time;
	int passenger_id;

public:
	virtual void Excute() = 0;
};

