#include "Station.h"
#include "Company.h"
Station::Station()
{

}

Station::Station(int stationNum)
{
	StationNum = stationNum;
}


Passenger* Station::MovWC()
{
	Passenger* WC_Passenger_ptr = nullptr;
	WP_ForwardWaiting.dequeue(WC_Passenger_ptr);
	return WC_Passenger_ptr;
}
Passenger* Station::MovSP()
{
	Passenger* SP_Passenger_ptr = nullptr;
	NP_SP_ForwardWaiting.dequeue(SP_Passenger_ptr);
	return SP_Passenger_ptr;
}
Passenger* Station::MovNP()
{
	Passenger* NP_Passenger_ptr = nullptr;
	NP_SP_ForwardWaiting.dequeue(NP_Passenger_ptr);
	return NP_Passenger_ptr;
}