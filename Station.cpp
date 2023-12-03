#include "Station.h"
#include "Company.h"
Station::Station()
{

}

Station::Station(int stationNum)
{
	StationNum = stationNum;
}

void Station::remove_NP(int p_id)
{
	if (!NP_SP_ForwardWaiting.remove_Specific(p_id)) {
		NP_SP_BackwardWaiting.remove_Specific(p_id);
	}
}
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
}

void Station::add_NP_SP(Passenger* P)
{
	if (P->get_start_station() < P->get_end_station())
	{
		if (P->get_type() == "N")
			NP_SP_ForwardWaiting.enqueue(P, 1);
		else
		{
			if (P->get_special_type() == "aged")
				NP_SP_ForwardWaiting.enqueue(P, 4);
			else
			{
				if (P->get_special_type() == "POD")
					NP_SP_ForwardWaiting.enqueue(P, 3);
				else
					NP_SP_ForwardWaiting.enqueue(P, 2);
			}
		}
	}
}
