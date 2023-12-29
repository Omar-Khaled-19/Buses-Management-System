#include "Bus.h"


Bus::Bus(int id, int cap, char type)
{
	ID = id;
	Capacity = cap;
	Type = type;
}

int Bus:: GetBusCapacity()
{
  return Capacity;
}

int Bus::GetPassengersCount()
{
	return Passengers.getCount();
}

char Bus::GetBusType()
{
	return Type;
}

void Bus::EnqueuePassenger(Passenger* P)
{
	Station* End = P->get_end_station();
	int EndSationNum = End->GetStationNum();
	Passengers.enqueue(P, EndSationNum);
}

void Bus::set_check_start_time(Time t)
{
	Ch_Start_Time = t;
}

Time Bus::GetCheckStartTime()
{
	return Ch_Start_Time;
}

int Bus::GetchekupDurationInMinutes()
{
	return ChekupDurationInMinutes;
}

void Bus::SetCurrStation(int n)
{
	Current_Station = n;
}

void Bus::SetNextStation(int n)
{
	Next_Station = n;
}

int Bus::GetCurrStation()
{
	return Current_Station;
}

int Bus::GetNextStation()
{
	return Next_Station;
}

int Bus::GetNum_of_Curr_Journeys()
{
	return Num_of_Curr_Journeys;
}

Time Bus::GetLastMovingTime()
{
	return LastMovingTime;
}

int Bus::GetBusId()
{
	return ID;
}

PriorityQueue<Passenger*>* Bus::Get_Bus_Passengers()
{
	return &Passengers;
}
