#include "Passenger.h"

Passenger::Passenger()
{
}

Passenger::Passenger(int ID, char Type, Station* sStation, Station* eStation, Time Arr_time)
{
	id = ID;
	type = Type;
	S_station = sStation;
	E_station = eStation;
	AT = Arr_time;
}

int Passenger::get_id()
{
	return id;
}

char Passenger::get_type()
{
	return type;
}