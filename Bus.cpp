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

int Bus::GetCurrentStation()
{
	return Current_Station;
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
