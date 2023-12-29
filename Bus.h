
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
	int total_passengers_transported;
	int Num_of_Curr_Journeys;
	int Current_Station;
	int Next_Station;
	int Ch_Journeys;
	int ChekupDurationInMinutes;
	Time Ch_Start_Time;

	Time Ch_time;
	Time Ch_duration;
	Time Busy_time;
	Time Utilization_time;
	Time Tot_busy_time;
	Time Tot_delievery_time;
	PriorityQueue<Passenger*> Passengers;

public:
	Bus(int id, int capacity, char type);
	int GetPassengersCount();
	int GetBusCapacity();
	int GetCurrentStation();
	char GetBusType();
	void EnqueuePassenger(Passenger* P);
	void set_check_start_time(Time t);
	Time GetCheckStartTime();
	int GetchekupDurationInMinutes();
	int GetCurrStation();
	int GetNextStation();
	int GetNum_of_Curr_Journeys();
};
