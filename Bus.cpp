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
	int EndSationNum = End->GetStationNum;
	Passengers.enqueue(P, EndSationNum);
}