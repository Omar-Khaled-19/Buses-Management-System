#include "Station.h"
#include "Company.h"
Station::Station()
{

}

Station::Station(int stationNum)
{
	StationNum = stationNum;
	FWD_NP=0;
	BCK_NP=0;
	FWD_SP_age=0;
	FWD_SP_pod=0;
	FWD_SP_preg=0;
	BCK_SP_age=0;
	BCK_SP_pod=0;
	BCK_SP_preg=0;
	FWD_WP=0;
	BCK_WP=0;
}

void Station::remove_NP(int p_id)
{
	if (NP_ForwardWaiting.remove_Specific(p_id))
	{
		FWD_NP--;
		return;
	}
	else if (NP_BackwardWaiting.remove_Specific(p_id))
		BCK_NP--;
}

int Station::GetStationNum()
{
	return StationNum;
}

Passenger* Station::MovWC()
{
	Passenger* WC_Passenger_ptr = nullptr;
	if (!WP_ForwardWaiting.isEmpty())
	{
		WP_ForwardWaiting.dequeue(WC_Passenger_ptr);
		FWD_WP--;
	}
	else
	{
		WP_BackwardWaiting.dequeue(WC_Passenger_ptr);
		BCK_WP--;
	}
	return WC_Passenger_ptr;
}

Passenger* Station::MovSP()
{
	Passenger* SP_Passenger_ptr = nullptr;
	
	if (!SP_ForwardWaiting.isEmpty())
	{
		SP_ForwardWaiting.dequeue(SP_Passenger_ptr);
		
	}
	else
	{
		SP_BackwardWaiting.dequeue(SP_Passenger_ptr);
		
	}
	return SP_Passenger_ptr;
}

Passenger* Station::MovNP()
{
	Passenger* NP_Passenger_ptr = nullptr;

	if (!NP_ForwardWaiting.isEmpty())
	{
		NP_ForwardWaiting.dequeue(NP_Passenger_ptr);
		FWD_NP--;
	}
	else
	{
		NP_BackwardWaiting.dequeue(NP_Passenger_ptr);
		BCK_NP--;
	}
	return NP_Passenger_ptr;
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
	return;
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

	}
}









void Station::LoadPassengersBWD(Bus* BBus, int& Time_count, int get_on_time, int TotalStationsNum)
{
		Passenger* BP = nullptr;
		char BBusType = BBus->GetBusType();
		if (BBusType == 'M')
		{
			while (SP_BackwardWaiting.dequeue(BP) && Time_count < 60)
			{
				if (BBus->GetPassengerOnBWD(BP,TotalStationsNum))
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
					if (BBus->GetPassengerOnBWD(BP,TotalStationsNum))
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
			}


		}
		else if (BBusType == 'W')
		{
			while (WP_BackwardWaiting.dequeue(BP) && Time_count < 60)
			{
				if (BBus->GetPassengerOnBWD(BP,TotalStationsNum))
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

		}
}


void Station::AllFWDBusOperation(int get_on_off_time, int TotalNumOfStations, int NumOfJourneysToChecup)
{
	int count = 0;
	Bus* B = nullptr;
	while (!ForwardBusList.isEmpty() && count < 60)
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
	return;
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
	return;
}

void Station::add_passenger(Passenger* P)
{
	if (P->get_start_station() < P->get_end_station())
	{
		if (P->get_type() == "WP")
		{
			WP_ForwardWaiting.enqueue(P);
			FWD_WP++;
		}
		else if (P->get_type() == "NP")
		{
			NP_ForwardWaiting.enqueue(P);
			FWD_NP++;
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				SP_ForwardWaiting.enqueue(P, 1);
				FWD_SP_age++;
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					SP_ForwardWaiting.enqueue(P, 2);
					FWD_SP_pod++;
				}
				else
				{
					SP_ForwardWaiting.enqueue(P, 3);
					FWD_SP_preg++;
				}
			}
		}
	}
	else
	{
		if (P->get_type() == "WP")
		{
			WP_BackwardWaiting.enqueue(P);
			BCK_WP++;
		}
		else if (P->get_type() == "NP")
		{
			NP_BackwardWaiting.enqueue(P);
			BCK_NP++;
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				SP_BackwardWaiting.enqueue(P, 1);
				BCK_SP_age++;
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					SP_BackwardWaiting.enqueue(P, 2);
					BCK_SP_pod++;
				}
				else
				{
					SP_BackwardWaiting.enqueue(P, 3);
					BCK_SP_preg++;
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


void Station:: printStation(int stationn)
{
	cout << "\n==============     STATION #"<<stationn<<"     ==============\n";

	int SP_count = SP_ForwardWaiting.getCount() + SP_BackwardWaiting.getCount();

	cout << SP_count << " Waiting SP: FWD[";

	PQNode<Passenger*>* tempQ = SP_ForwardWaiting.getHead();
	for (int i = 0; i < SP_ForwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ->getItem();

		int SP_id = ptemp->get_id();
		cout << SP_id << "(" << ptemp->get_special_type() << ")" << ",";
	}
	cout << "] BCK[";
	
	PQNode<Passenger*>* tempQ2 = SP_BackwardWaiting.getHead();
	for (int i = 0; i < SP_BackwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ2->getItem();

		int SP_id = ptemp->get_id();
		cout << SP_id << "(" << ptemp->get_special_type() << ")" << ",";
	}
	cout << "]" << endl;



	int WP_count = WP_ForwardWaiting.getCount() + WP_BackwardWaiting.getCount();
	
	cout << WP_count << " Waiting WP: FWD[";
	
	Node<Passenger*>* temp = WP_ForwardWaiting.getHead();
	for (int i = 0; i < WP_ForwardWaiting.getCount();i++)
	{
		Passenger* ptemp = temp->getItem();
		
		int WP_id = ptemp->get_id();
		cout << WP_id << ",";
	}
	cout << "] BCK[";

	Node<Passenger*>* temp2 = WP_BackwardWaiting.getHead();
	for (int i = 0; i < WP_BackwardWaiting.getCount();i++)
	{
		Passenger* ptemp = temp2->getItem();

		int WP_id = ptemp->get_id();
		cout << WP_id << ",";
	}
	cout << "]" << endl;




	int NP_count = NP_ForwardWaiting.getCount() + NP_BackwardWaiting.getCount();

	cout << NP_count << " Waiting NP: FWD[";

	Node<Passenger*>* tempQ3 = NP_ForwardWaiting.getHead();
	for (int i = 0; i < NP_ForwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ3->getItem();

		int NP_id = ptemp->get_id();
		cout << NP_id << ",";
	}
	cout << "] BCK[";
	
	Node<Passenger*>* tempQ4 = NP_BackwardWaiting.getHead();
	for (int i = 0; i < NP_BackwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ4->getItem();

		int NP_id = ptemp->get_id();
		cout << NP_id << ",";
	}
	cout << "]" << endl;

	cout << "----------------------------------------------------------------------------------------------------\n";
}

Bus* Station::PeekFirstForwardBus()
{
	Bus* tempBus;
	ForwardBusList.peek(tempBus);
	return tempBus;
}

Bus* Station::PeekFirstBackwardBus()
{
	Bus* tempBus;
	BackwardBusList.peek(tempBus);
	return tempBus;
}

Bus* Station::DequeueFirstForwardBus()
{
	Bus* tempBus;
	ForwardBusList.dequeue(tempBus);
	return tempBus;
}

Bus* Station::DequeueFirstBackwardBus()
{
	Bus* tempBus;
	BackwardBusList.dequeue(tempBus);
	return tempBus;
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
