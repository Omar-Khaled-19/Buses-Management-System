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
