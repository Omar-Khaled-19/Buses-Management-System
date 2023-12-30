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

bool Bus::GetPassengerOnFWD(Passenger* P)
{
	int count = GetPassengersCount();
	if (count < Capacity)
	{
		int End = P->get_end_station_num();
		
		Passengers.enqueue(P, End);
		return true;
	}
	else
		return false;
}

bool Bus::GetPassengerOnBWD(Passenger* P,int num_of_stations)
{
	int count = GetPassengersCount();
	if (count < Capacity)
	{
		
		int EndStationNum = P->get_end_station_num();
		int Priority = num_of_stations - EndStationNum;
		Passengers.enqueue(P, EndStationNum);
		return true;
	}
	else
		return false;
}

bool Bus::GetPassengerOff(Passenger* P,int station_num) //dequeues a passenger only if its priority(end station) is equal to the station num of the station calling it, takes passenger ptr to return the dequeued passenger in
{
	Passengers.peek(P);
	if (P != nullptr)
	{
		int EndStationNum = P->get_end_station_num();
		if (EndStationNum == station_num)
		{
			Passengers.dequeue(P);
			total_passengers_transported++;
			return true;
		}
		else
			return false;
	}
	else
		return false;

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

void Bus::setLastMovingTime(Time t)
{
	LastMovingTime = t;
}

int Bus::GetBusId()
{
	return ID;
}

PriorityQueue<Passenger*>* Bus::Get_Bus_Passengers()
{
	return &Passengers;
}

void Bus::increment_journeys()
{
	Num_of_Curr_Journeys++;
}

void Bus::reset_journeys()
{
	Num_of_Curr_Journeys = 0;
}
