#pragma once
#include "time.h"
#include <iostream>
using namespace std;

class Station;
class Passenger
{

private:
	int id;
	string type;
	string special_type;
	Station* start_station;
	Station* end_station;
	int Max_waiting_time;
	Time AT;
	Time FT;
	Time MT;

public:
	Passenger();
	Passenger(int ID, string Type, Station* sStation, Station* eStation, Time Arr_time, string Stype = NULL);
	int get_id();
	string get_type();
	string get_special_type();
	Station* get_start_station();
	Station* get_end_station();
	Time get_FT();
	Time get_AT();
	Time get_MT();
	Time get_finish_WT();
	Time get_upgrade_WT(Time clock);
	Time get_TT();
};

