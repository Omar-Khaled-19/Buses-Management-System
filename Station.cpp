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
	if (NP_SP_ForwardWaiting.remove_Specific(p_id))
	{
		FWD_NP--;
		return;
	}
	else if (NP_SP_BackwardWaiting.remove_Specific(p_id))
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
	
	if (!NP_SP_ForwardWaiting.isEmpty())
	{
		NP_SP_ForwardWaiting.Dequeue_First("SP", SP_Passenger_ptr);
		if (SP_Passenger_ptr->get_special_type() == "aged")
			FWD_SP_age--;
		else
		{
			if (SP_Passenger_ptr->get_special_type() == "POD")
				FWD_SP_pod--;
			else
				FWD_SP_preg--;
		}
	}
	else
	{
		NP_SP_BackwardWaiting.Dequeue_First("SP", SP_Passenger_ptr);
		if (SP_Passenger_ptr->get_special_type() == "aged")
			BCK_SP_age--;
		else
		{
			if (SP_Passenger_ptr->get_special_type() == "POD")
				BCK_SP_pod--;
			else
				BCK_SP_preg--;
		}
	}
	return SP_Passenger_ptr;
}

Passenger* Station::MovNP()
{
	Passenger* NP_Passenger_ptr = nullptr;

	if (!NP_SP_ForwardWaiting.isEmpty())
	{
		NP_SP_ForwardWaiting.Dequeue_First("NP", NP_Passenger_ptr);
		FWD_NP--;
	}
	else
	{
		NP_SP_BackwardWaiting.Dequeue_First("NP", NP_Passenger_ptr);
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
			NP_SP_ForwardWaiting.enqueue(P, 4);
			FWD_NP++;
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				NP_SP_ForwardWaiting.enqueue(P, 1);
				FWD_SP_age++;
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					NP_SP_ForwardWaiting.enqueue(P, 2);
					FWD_SP_pod++;
				}
				else
				{
					NP_SP_ForwardWaiting.enqueue(P, 3);
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
			NP_SP_BackwardWaiting.enqueue(P, 4);
			BCK_NP++;
		}
		else
		{
			if (P->get_special_type() == "aged")
			{
				NP_SP_BackwardWaiting.enqueue(P, 1);
				BCK_SP_age++;
			}
			else
			{
				if (P->get_special_type() == "POD")
				{
					NP_SP_BackwardWaiting.enqueue(P, 2);
					BCK_SP_pod++;
				}
				else
				{
					NP_SP_BackwardWaiting.enqueue(P, 3);
					BCK_SP_preg++;
				}
			}
		}
	}

}


void Station:: printStation(int stationn)
{
	cout << "\n==============     STATION #"<<stationn<<"     ==============\n";
	int* BCK_WP_ID=nullptr;
	int* FWD_WP_ID=nullptr;
	int* FWD_SP_age_ID=nullptr;
	int* FWD_SP_pod_ID=nullptr;
	int* FWD_SP_preg_ID=nullptr;
	int* FWD_NP_ID=nullptr;
	int* BCK_SP_age_ID=nullptr;
	int* BCK_SP_pod_ID=nullptr;
	int* BCK_SP_preg_ID=nullptr;
	int* BCK_NP_ID=nullptr;

	if (1)
	{
		BCK_WP_ID = new int[BCK_WP - 1];
		Node<Passenger*>* counter = WP_BackwardWaiting.getHead();
		for (int i = 0; i < BCK_WP; i++)
		{
			Passenger* temp = counter->getItem();
			int WP_id = temp->get_id();
			BCK_WP_ID[i] = WP_id;
			counter = counter->getNext();
		}
	}

	if (FWD_WP != 0)
	{
		FWD_WP_ID = new int[FWD_WP - 1];
		Node<Passenger*>* counter2 = WP_ForwardWaiting.getHead();
		for (int i = 0; i < FWD_WP; i++)
		{
			Passenger* temp = counter2->getItem();
			int WP_id = temp->get_id();
			FWD_WP_ID[i] = WP_id;
			counter2 = counter2->getNext();
		}
	}

	if (!NP_SP_ForwardWaiting.isEmpty())
	{
		PQNode<Passenger*>* counter3 = NP_SP_ForwardWaiting.getHead();
		if (FWD_SP_age != 0)
		{
			FWD_SP_age_ID = new int[FWD_SP_age - 1];
			for (int i = 0; i < FWD_SP_age; i++)
			{
				Passenger* temp = counter3->getItem();
				int SP_id = temp->get_id();
				FWD_SP_age_ID[i] = SP_id;
				counter3 = counter3->getNext();
			}
			//counter3 at first pod
		}

		if (FWD_SP_pod != 0)
		{
			FWD_SP_pod_ID = new int[FWD_SP_pod - 1];
			for (int i = 0; i < FWD_SP_pod; i++)
			{
				Passenger* temp = counter3->getItem();
				int SP_id = temp->get_id();
				FWD_SP_pod_ID[i] = SP_id;
				counter3 = counter3->getNext();
			}
		}
		//counter3 at first pregnant
	
		if (FWD_SP_preg != 0)
		{
			FWD_SP_preg_ID = new int[FWD_SP_preg - 1];
			for (int i = 0; i < FWD_SP_preg; i++)
			{
				Passenger* temp = counter3->getItem();
				int SP_id = temp->get_id();
				FWD_SP_preg_ID[i] = SP_id;
				counter3 = counter3->getNext();
			}
		}
		//counter3 at first NP

		if (FWD_NP != 0)
		{
			FWD_NP_ID = new int[FWD_NP - 1];
			for (int i = 0; i < FWD_NP; i++)
			{
				Passenger* temp = counter3->getItem();
				int NP_id = temp->get_id();
				FWD_NP_ID[i] = NP_id;
				counter3 = counter3->getNext();
			}
		}
	}

	//SAME FOR BACKWARDS
	if (!NP_SP_BackwardWaiting.isEmpty())
	{
		PQNode<Passenger*>* counter4 = NP_SP_BackwardWaiting.getHead();

		if (BCK_SP_age != 0)
		{
			BCK_SP_age_ID = new int[BCK_SP_age - 1];
			PQNode<Passenger*>* counter4 = NP_SP_BackwardWaiting.getHead();
			for (int i = 0; i < FWD_SP_age; i++)
			{
				Passenger* temp = counter4->getItem();
				int SP_id = temp->get_id();
				BCK_SP_age_ID[i] = SP_id;
				counter4 = counter4->getNext();
			}
		}
		//counter4 at first pod

		if (BCK_SP_pod != 0)
		{
			BCK_SP_pod_ID = new int[BCK_SP_pod - 1];
			for (int i = 0; i < BCK_SP_pod; i++)
			{
				Passenger* temp = counter4->getItem();
				int SP_id = temp->get_id();
				BCK_SP_pod_ID[i] = SP_id;
				counter4 = counter4->getNext();
			}
		}
		//counter4 at first pregnant

		if (BCK_SP_preg != 0)
		{
			BCK_SP_preg_ID = new int[BCK_SP_preg - 1];
			for (int i = 0; i < BCK_SP_preg; i++)
			{
				Passenger* temp = counter4->getItem();
				int SP_id = temp->get_id();
				BCK_SP_preg_ID[i] = SP_id;
				counter4 = counter4->getNext();
			}
		}
		//counter4 at first NP

		if (BCK_NP != 0)
		{
			BCK_NP_ID = new int[BCK_NP - 1];
			for (int i = 0; i < BCK_NP; i++)
			{
				Passenger* temp = counter4->getItem();
				int NP_id = temp->get_id();
				BCK_NP_ID[i] = NP_id;
				counter4 = counter4->getNext();
			}
		}
	}

	int SP_wait = FWD_SP_age + FWD_SP_pod + FWD_SP_preg + BCK_SP_age + BCK_SP_pod + BCK_SP_preg;
	int NP_wait = FWD_NP + BCK_NP;
	int WP_wait = FWD_WP + BCK_WP;

	cout << SP_wait <<" Waiting SP: FWD[";
	for (int i = 0; i < FWD_SP_age; i++)
	{ 
		if(i==0)
		cout << FWD_SP_age_ID[i] << "(Ag)";
		else
			cout << ","<<FWD_SP_age_ID[i] << "(Ag)";
	}
	for (int i = 0; i < FWD_SP_pod; i++)
	{
		if (i == 0)
			cout << FWD_SP_pod_ID[i] << "(PD)";
		else
			cout << "," << FWD_SP_pod_ID[i] << "(PD)";
	}
	for (int i = 0; i < FWD_SP_preg; i++)
	{
		if (i == 0)
			cout << FWD_SP_preg_ID[i] << "(Preg)";
		else
			cout << "," << FWD_SP_preg_ID[i] << "(Preg)";
	}
	cout << "]  BCK[";
	for (int i = 0; i < BCK_SP_age; i++)
	{
		if (i == 0)
			cout << BCK_SP_age_ID[i] << "(Ag)";
		else
			cout << "," << BCK_SP_age_ID[i] << "(Ag)";
	}
	for (int i = 0; i < BCK_SP_pod; i++)
	{
		if (i == 0)
			cout << BCK_SP_pod_ID[i] << "(PD)";
		else
			cout << "," << BCK_SP_pod_ID[i] << "(PD)";
	}
	for (int i = 0; i < BCK_SP_preg; i++)
	{
		if (i == 0)
			cout << BCK_SP_preg_ID[i] << "(Preg)";
		else
			cout << "," << BCK_SP_preg_ID[i] << "(Preg)";
	}
	cout << "]\n";

	cout << WP_wait << " Waiting WP: FWD[";
	for (int i = 0; i < FWD_WP; i++)
	{
		if (i == 0)
			cout << FWD_WP_ID[i];
		else
			cout << "," << FWD_WP_ID[i];
	}
	cout << "] BCK[";
	for (int i = 0; i < BCK_WP; i++)
	{
		if (i == 0)
			cout << BCK_WP_ID[i];
		else
			cout << "," << BCK_WP_ID[i];
	}
	cout << "]\n";


	cout << NP_wait << " Waiting NP: FWD[";
	for (int i = 0; i < FWD_NP; i++)
	{
		if (i == 0)
			cout << FWD_NP_ID[i];
		else
			cout << "," << FWD_NP_ID[i];
	}
	cout << "] BCK[";
	for (int i = 0; i < BCK_NP; i++)
	{
		if (i == 0)
			cout << BCK_NP_ID[i];
		else
			cout << "," << BCK_NP_ID[i];
	}
	cout << "]\n";

	cout << "----------------------------------------------------------------------------------------------------\n";
}