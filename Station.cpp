#include "Station.h"
Station::Station()
{}

Station::Station(int stationNum)
{
	StationNum = stationNum;
}

void Station::remove_NP(int p_id)
{
	if (NP_ForwardWaiting.remove_Specific(p_id))
		return;
	else
		NP_BackwardWaiting.remove_Specific(p_id);
}

int Station::GetStationNum()
{
	return StationNum;
}

void Station:: UnloadPassengers(Bus* Buss, int& Time_count, int get_off_time)
{
	Passenger* PP = nullptr;
	while (Time_count<60)
	{
		if (Buss->GetPassengerOff(PP, StationNum))
		{
			Time_count += get_off_time;
			GoToFinishedPassengerList.enqueue(PP);
		}
		else  // no passengers to drop off in this station 
			return;
	}
}


void Station::LoadPassengersFWD(Bus* FBus, int& Time_count, int get_on_time)
{
	Passenger* FP = nullptr;
	char FBusType = FBus->GetBusType();
	if (FBusType == 'M')
	{
		while (SP_ForwardWaiting.dequeue(FP) && Time_count < 60)
		{
			if (FBus->GetPassengerOnFWD(FP))
			{
				Time_count += get_on_time;
			}
			else  // full bus
			{
				ForwardBusList.dequeue(FBus);
				FullForwardBusList.enqueue(FBus);
				return;
			}
		}
		if (Time_count >= 60)
			return;
		else
		{
			while (NP_ForwardWaiting.dequeue(FP) && Time_count < 60)
			{
				if (FBus->GetPassengerOnFWD(FP))
				{
					Time_count += get_on_time;
				}
				else // full bus
				{
					ForwardBusList.dequeue(FBus);
					FullForwardBusList.enqueue(FBus);
					return;
				}
			}
			if (Time_count >= 60)
				return;

			else // no more passengers in the station
			{
				ForwardBusList.dequeue(FBus);
				FullForwardBusList.enqueue(FBus);
				return;
			}

		}


	}
	else if (FBusType == 'W')
	{
		while (WP_ForwardWaiting.dequeue(FP) && Time_count < 60)
		{
			if (FBus->GetPassengerOnFWD(FP))
			{
				Time_count += get_on_time;
			}
			else // full bus
			{
				ForwardBusList.dequeue(FBus);
				FullForwardBusList.enqueue(FBus);
				return;
			}
		}
		if (Time_count >= 60)
			return;

		else // no more passengers in the station
		{
			ForwardBusList.dequeue(FBus);
			FullForwardBusList.enqueue(FBus);
			return;
		}
	}
}


void Station::LoadPassengersBWD(Bus* BBus, int& Time_count, int get_on_time, int TotalStationsNum)
{
	Passenger* BP = nullptr;
	char BBusType = BBus->GetBusType();
	if (BBusType == 'M')
		Bus* BBus;
	BackwardBusList.peek(BBus);
	int BMovCount = BBus->GetPassengersCount();
	int BmaxCap = BBus->GetBusCapacity();
	int Backward_Waiting_MPassengers_Count = SP_BackwardWaiting.getCount() + NP_BackwardWaiting.getCount();
	int Backward_Waiting_WPassengers_Count = WP_BackwardWaiting.getCount();

	while (BMovCount < BmaxCap)
	{
		if (BBus->GetBusType() == 'M')
		{
			while (SP_BackwardWaiting.dequeue(BP) && Time_count < 60)
			{
				if (BBus->GetPassengerOnBWD(BP, TotalStationsNum))
				{
					Time_count += get_on_time;
				}
				else  // full bus
				{
					BackwardBusList.dequeue(BBus);
					FullBackwardBusList.enqueue(BBus);
					return;
				}
			}
			if (Time_count >= 60)
				return;
			else
			{
				while (NP_BackwardWaiting.dequeue(BP) && Time_count < 60)
				{
					if (BBus->GetPassengerOnBWD(BP, TotalStationsNum))
					{
						Time_count += get_on_time;
					}
					else // full bus
					{
						BackwardBusList.dequeue(BBus);
						FullBackwardBusList.enqueue(BBus);
						return;
					}
				}
				if (Time_count >= 60)
					return;

				else // no more passengers
				{
					BackwardBusList.dequeue(BBus);
					FullBackwardBusList.enqueue(BBus);
					return;
				}
			}


		}
		else if (BBusType == 'W')
		{
			while (WP_BackwardWaiting.dequeue(BP) && Time_count < 60)
			{
				if (BBus->GetPassengerOnBWD(BP, TotalStationsNum))
				{
					Time_count += get_on_time;
				}
				else // full bus
				{
					BackwardBusList.dequeue(BBus);
					FullBackwardBusList.enqueue(BBus);
					return;
				}
			}
			if (Time_count >= 60)
				return;

			else // no more passengers
			{
				BackwardBusList.dequeue(BBus);
				FullBackwardBusList.enqueue(BBus);
				return;
			}
		}
	}
}

void Station::AllFWDBusOperation(int get_on_off_time, int TotalNumOfStations, int NumOfJourneysToChecup)
{
	int count = 0;
	Bus* B = nullptr;
	while (!ForwardBusList.isEmpty() && count < 60 )
	{
		ForwardBusList.peek(B);
		if (StationNum == 1)
		{
			UnloadPassengers(B, count, get_on_off_time);
			int current_journeys = B->GetNum_of_Curr_Journeys();
			if (current_journeys >= NumOfJourneysToChecup)
			{
				ForwardBusList.dequeue(B);
				NeedsCheckupBusList.enqueue(B);
			}
			else
			LoadPassengersFWD(B, count, get_on_off_time);
		}
		else
		{
			UnloadPassengers(B, count, get_on_off_time);
			LoadPassengersFWD(B, count, get_on_off_time);
		}
	}
}


void Station::AllBWDBusOperation(int get_on_off_time, int TotalNumOfStations)
{
	int count = 0;
	Bus* B = nullptr;
	while (!BackwardBusList.isEmpty() && count < 60)
	{
		BackwardBusList.peek(B);
		UnloadPassengers(B, count, get_on_off_time);
		LoadPassengersBWD(B, count, get_on_off_time,TotalNumOfStations);
	}
}

void Station::add_passenger(Passenger* P)
{
	if (P->get_start_station() < P->get_end_station())
	{
		if (P->get_type() == "WP")
		{
			WP_ForwardWaiting.enqueue(P);
		}
		else if (P->get_type() == "NP")
		{
			NP_ForwardWaiting.enqueue(P);
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				SP_ForwardWaiting.enqueue(P, 1);
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					SP_ForwardWaiting.enqueue(P, 2);
				}
				else
				{
					SP_ForwardWaiting.enqueue(P, 3);
				}
			}
		}
	}
	else
	{
		if (P->get_type() == "WP")
		{
			WP_BackwardWaiting.enqueue(P);
		}
		else if (P->get_type() == "NP")
		{
			NP_BackwardWaiting.enqueue(P);
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				SP_BackwardWaiting.enqueue(P, 1);
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					SP_BackwardWaiting.enqueue(P, 2);
	
				}
				else
				{
					SP_BackwardWaiting.enqueue(P, 3);
				}
			}
		}
	}

}

void Station::AddForwardBus(Bus* newBus)
{
	ForwardBusList.enqueue(newBus);
}

void Station::AddBackwardBus(Bus* newBus)
{
	BackwardBusList.enqueue(newBus);
}

void Station::PromoteNP(Time t, int max_waiting_time)
{
	Passenger* tempPass;
	LinkedQueue<Passenger*> tempQueue;
	while (NP_ForwardWaiting.dequeue(tempPass))
	{
		if (t - tempPass->get_arrival_time() > max_waiting_time)
		{
			SP_ForwardWaiting.enqueue(tempPass, 1);
			numberOfPromoted++;
		}
		else
			tempQueue.enqueue(tempPass);
	}
	while (tempQueue.dequeue(tempPass))
		NP_ForwardWaiting.enqueue(tempPass);

	while (NP_BackwardWaiting.dequeue(tempPass))
	{
		if (t - tempPass->get_arrival_time() > max_waiting_time)
		{
			SP_BackwardWaiting.enqueue(tempPass, 1);
			numberOfPromoted++;
		}
		else
			tempQueue.enqueue(tempPass);
	}
	while (tempQueue.dequeue(tempPass))
		NP_BackwardWaiting.enqueue(tempPass);
}

Passenger* Station::RemovePassengerFromGoToFinishedPassengerList()
{
	Passenger* ptr = nullptr;
	GoToFinishedPassengerList.dequeue(ptr);
	return ptr;

}

int Station::GetGoToFinishedPassengerListCount()
{
	return GoToFinishedPassengerList.getCount();
}

Bus* Station::RemoveBusFromFullForwardBusList()
{
	Bus* ptr = nullptr;
	FullForwardBusList.dequeue(ptr);
	return ptr;
}

int Station::GetFullForwardBusListCount()
{
	return FullForwardBusList.getCount();
}

Bus* Station::RemoveBusFromFullBackwardBusList()
{
	Bus* ptr = nullptr;
	FullBackwardBusList.dequeue(ptr);
	return ptr;

}

int Station::GetFullBackwardBusListCount()
{
	return FullBackwardBusList.getCount();
}

Bus* Station::RemoveBusFromNeedsCheckupBusList()
{
	Bus* ptr = nullptr;
	NeedsCheckupBusList.dequeue(ptr);
	return ptr;

}

int Station::GetNeedsCheckupBusListCount()
{
	return NeedsCheckupBusList.getCount();
}

PriorityQueue<Passenger*>* Station::Get_FwdSP()
{
	return &SP_ForwardWaiting;
}
PriorityQueue<Passenger*>* Station::Get_BckSP()
{
	return &SP_BackwardWaiting;
}
ModifiedQueue<Passenger*>* Station:: Get_FwdNP()
{
	return &NP_ForwardWaiting;
}
ModifiedQueue<Passenger*>* Station:: Get_BckNP()
{
	return &NP_BackwardWaiting;
}
LinkedQueue<Passenger*>* Station:: Get_FwdWP()
{
	return &WP_ForwardWaiting;
}
LinkedQueue<Passenger*>* Station:: Get_BckWP()
{
	return &WP_BackwardWaiting;
}
LinkedQueue<Bus*>* Station::Get_FwdBus()
{
	return &FullForwardBusList;
}
LinkedQueue<Bus*>* Station::Get_BckBus()
{
	return &FullBackwardBusList;
}
