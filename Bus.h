
#pragma once
#include "time.h"
#include "passenger.h"
#include "priorityqueue.h"

class Bus
{

private:
	char Type;
	int Capacity;
	int ID;
	Time Ch_time;
	Time Ch_duration;
	Time Busy_time;
	Time Utilization_time;
	Time Tot_busy_time;
	Time Tot_delievery_time;
	PriorityQueue<Passenger> Passengers;

public:
	Bus(int id, int capacity, char type);

};
