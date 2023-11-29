#pragma once
#include "station.h"
#include "time.h"

class Passenger
{

private:
	int id;
	char type;
	Station S_station;
	Station E_station;
	int Max_w_time;
	Time AT;
	Time FT;
	Time MT;

public:
	Passenger();
	Passenger(int ID, char Type, Station sStation, Station eStation, Time Arr_time);


};

