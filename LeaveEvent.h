#pragma once
#include "Event.h"
class LeaveEvent : public Event
{
public:
	LeaveEvent(int ID, Station* sStation, Time etime);
	void Excute();
	Time get_event_time();
	Station* LeaveStation();
};

