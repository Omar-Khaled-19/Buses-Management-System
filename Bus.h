
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
	int Current_Station = 0;
	int Next_Station = 1;
	int Ch_Journeys;
	int ChekupDurationInMinutes;
	Time LastMovingTime;
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
	char GetBusType();
	bool GetPassengerOnFWD(Passenger* P);
	bool GetPassengerOnBWD(Passenger* P,int num_of_stations);
	bool GetPassengerOff(Passenger* P, int station_num);
	void set_check_start_time(Time t);
	Time GetCheckStartTime();
	int GetchekupDurationInMinutes();
	void SetCurrStation(int n);
	void SetNextStation(int n);
	int GetCurrStation();
	int GetNextStation();
	int GetNum_of_Curr_Journeys();
	Time GetLastMovingTime();
	int GetBusId();
	PriorityQueue<Passenger*>* Get_Bus_Passengers();
	void setLastMovingTime(Time t);
};
