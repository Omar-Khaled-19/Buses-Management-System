
#pragma once
#include "Passenger.h"
#include "PriorityQueue.h"

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
	int Busy_time;
	int Utilization_time;
	PriorityQueue<Passenger*> Passengers;
	int DeliveryTrips;

public:
	Bus(int id, int capacity, char type);
	int GetPassengersCount();
	int GetBusCapacity();
	char GetBusType();
	bool GetPassengerOnFWD(Passenger* P,Time clockkk);
	bool GetPassengerOnBWD(Passenger* P,int num_of_stations,Time clockkk);
	bool GetPassengerOff(Passenger* &P, int station_num,Time clockkk);
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
	void increment_journeys();
	void reset_journeys();
	void set_busyTime();
	int get_busyTime();
	void set_utilization();
	int get_utilization();
};
