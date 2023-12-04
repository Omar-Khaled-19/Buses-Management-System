#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent(int ID, string Type, Station* sStation, Station* eStation, Time etime,string Stype)
{
	passenger_id = ID;
	type = Type;
	st_station = sStation;
	end_station = eStation;
	event_time = etime;
}

void ArrivalEvent::Excute()
{
	Passenger* pPassenger = new Passenger(passenger_id, type, st_station,
		end_station, event_time, Stype);
	st_station->add_NP_SP(pPassenger);
}
Time ArrivalEvent::get_event_time()
{
    return event_time;
}
