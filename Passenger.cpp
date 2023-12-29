#include "Passenger.h"
#include"Station.h"


Passenger::Passenger()
{
}

Passenger::Passenger(int ID, string Type, Station* sStation, Station* eStation, Time Arr_time, string Stype)
{
	id = ID;
	type = Type;
	start_station = sStation;
	end_station = eStation;
	AT = Arr_time;
	special_type = Stype;
}

int Passenger::get_id()
{
	return id;
}

Time Passenger::get_arrival_time()
{
	return AT;
}

string Passenger::get_type()
{
	return type;
}



string Passenger::get_special_type()
{
	return special_type;
}


Station* Passenger::get_start_station()
{
	return start_station;
}

Station* Passenger::get_end_station()
{
	return end_station;
}

int Passenger::get_end_station_num()
{
	int EndStationNum = end_station->GetStationNum();
	return EndStationNum;
}



Time Passenger:: get_FT()
{
	return FT;
}
Time Passenger:: get_AT()
{
	return AT;
}
Time Passenger:: get_MT() 
{
	return MT;
}

int Passenger:: get_finish_WT()
{ 
	return MT - AT;
}
int Passenger:: get_upgrade_WT(Time clock)
{
	return clock - AT;
}
int Passenger:: get_TT()
{
	return FT - MT;
}