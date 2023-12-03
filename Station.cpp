#include "Station.h"

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
