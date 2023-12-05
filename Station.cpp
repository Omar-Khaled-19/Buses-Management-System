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
			NP_ForwardWaiting.enqueue(P, 1);
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
			NP_BackwardWaiting.enqueue(P, 4);
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



	int WP_count = WP_ForwardWaiting.get_count() + WP_BackwardWaiting.get_count();
	
	cout << WP_count << " Waiting WP: FWD[";
	
	Node<Passenger*>* temp = WP_ForwardWaiting.getHead();
	for (int i = 0; i < WP_ForwardWaiting.get_count();i++)
	{
		Passenger* ptemp = temp->getItem();
		
		int WP_id = ptemp->get_id();
		cout << WP_id << ",";
	}
	cout << "] BCK[";

	Node<Passenger*>* temp2 = WP_BackwardWaiting.getHead();
	for (int i = 0; i < WP_BackwardWaiting.get_count();i++)
	{
		Passenger* ptemp = temp2->getItem();

		int WP_id = ptemp->get_id();
		cout << WP_id << ",";
	}
	cout << "]" << endl;




	int NP_count = NP_ForwardWaiting.getCount() + NP_BackwardWaiting.getCount();

	cout << NP_count << " Waiting NP: FWD[";

	PQNode<Passenger*>* tempQ3 = NP_ForwardWaiting.getHead();
	for (int i = 0; i < NP_ForwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ3->getItem();

		int NP_id = ptemp->get_id();
		cout << NP_id << ",";
	}
	cout << "] BCK[";
	
	PQNode<Passenger*>* tempQ4 = NP_BackwardWaiting.getHead();
	for (int i = 0; i < NP_BackwardWaiting.getCount();i++)
	{
		Passenger* ptemp = tempQ4->getItem();

		int NP_id = ptemp->get_id();
		cout << NP_id << ",";
	}
	cout << "]" << endl;

	cout << "----------------------------------------------------------------------------------------------------\n";
}