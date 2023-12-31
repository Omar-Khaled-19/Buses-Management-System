#include "UI.h"

int UI::ChooseMode() //First thing to call in simulation
{
	int x;
	cout << "PLease enter: \n(1) for 'Interactive Mode'  \n(2) for 'Silent Mode'\n";
	cin >> x;
	while (x != 1 && x != 2)
	{
		cout << "Error! Please enter 1 or 2";
		cin >> x;
	}
	return x; 
}

void UI:: InteractiveInterface(Time clockk,int stationn, Station* stationptr, LinkedQueue<Bus*>* Checkup, LinkedQueue<Passenger*>* finished, LinkedQueue<Bus*>* FWDBusList, LinkedQueue<Bus*>* BCKBusList)
 {
	cout << "Current Time (Hour:Min)==> " << clockk.GetHour() << ":" << clockk.GetMin() << endl;
	
		cout << "\n==============     STATION #" << stationn << "     ==============\n";
		PriorityQueue<Passenger*>* FwdSP = stationptr->Get_FwdSP();
		PriorityQueue<Passenger*>* BckSP = stationptr->Get_BckSP();
		ModifiedQueue<Passenger*>* FwdNP = stationptr->Get_FwdNP();
		ModifiedQueue<Passenger*>* BckNP = stationptr->Get_BckNP();
		LinkedQueue<Passenger*>* FwdWP = stationptr->Get_FwdWP();
		LinkedQueue<Passenger*>* BckWP = stationptr->Get_BckWP();
		LinkedQueue<Bus*>* FwdBus = stationptr->Get_FwdBus();
		LinkedQueue<Bus*>* BckBus = stationptr->Get_BckBus();
		LinkedQueue<Bus*>* FwdBus2 = stationptr->Get_FwdBus2();
		LinkedQueue<Bus*>* BckBus2 = stationptr->Get_BckBus2();

		int SP_count = FwdSP->getCount() + BckSP->getCount();

		cout << SP_count << " Waiting SP: FWD[";

		PQNode<Passenger*>* tempQ = FwdSP->getHead();
		for (int i = 0; i < FwdSP->getCount(); i++)
		{
			Passenger* ptemp = tempQ->getItem();

			int SP_id = ptemp->get_id();
			cout << SP_id << "(" << ptemp->get_special_type() << ")" << ",";
			tempQ = tempQ->getNext();
		}
		cout << "] BCK[";

		PQNode<Passenger*>* tempQ2 = BckSP->getHead();
		for (int i = 0; i < BckSP->getCount(); i++)
		{
			Passenger* ptemp = tempQ2->getItem();

			int SP_id = ptemp->get_id();
			cout << SP_id << "(" << ptemp->get_special_type() << ")" << ",";
			tempQ2 = tempQ2->getNext();
		}
		cout << "]" << endl;



		int WP_count = FwdWP->getCount() + BckWP->getCount();

		cout << WP_count << " Waiting WP: FWD[";

		Node<Passenger*>* temp = FwdWP->getHead();
		for (int i = 0; i < FwdWP->getCount(); i++)
		{
			Passenger* ptemp = temp->getItem();

			int WP_id = ptemp->get_id();
			cout << WP_id << ",";
			temp = temp->getNext();
		}
		cout << "] BCK[";

		Node<Passenger*>* temp2 = BckWP->getHead();
		for (int i = 0; i < BckWP->getCount(); i++)
		{
			Passenger* ptemp = temp2->getItem();

			int WP_id = ptemp->get_id();
			cout << WP_id << ",";
			temp2 = temp2->getNext();
		}
		cout << "]" << endl;




		int NP_count = FwdNP->getCount() + BckNP->getCount();

		cout << NP_count << " Waiting NP: FWD[";

		Node<Passenger*>* tempQ3 = FwdNP->getHead();
		for (int i = 0; i < FwdNP->getCount(); i++)
		{
			Passenger* ptemp = tempQ3->getItem();

			int NP_id = ptemp->get_id();
			cout << NP_id << ",";
			tempQ3 = tempQ3->getNext();
		}
		cout << "] BCK[";

		Node<Passenger*>* tempQ4 = BckNP->getHead();
		for (int i = 0; i < BckNP->getCount(); i++)
		{
			Passenger* ptemp = tempQ4->getItem();

			int NP_id = ptemp->get_id();
			cout << NP_id << ",";
			tempQ4 = tempQ4->getNext();
		}
		cout << "]" << endl;

		int Bus_count = FwdBus->getCount() + BckBus->getCount()+ FwdBus2->getCount() + BckBus2->getCount();
		cout << Bus_count << " Buses at this station:";
		Node<Bus*>* tempQ5 = FwdBus->getHead();
		for (int i = 0; i < FwdBus->getCount(); i++)
		{
			Bus* bustemp = tempQ5->getItem();
			cout<<"\nB"<<bustemp->GetBusId()<<"[FWD, "<<bustemp->GetBusType()<<"Bus, "<<bustemp->GetBusCapacity()<<"] {";
			PriorityQueue<Passenger*>* Bus_passenger = bustemp->Get_Bus_Passengers();
			PQNode<Passenger*>* temp10 = Bus_passenger->getHead();
			for (int j = 0; j < Bus_passenger->getCount(); j++)
			{
				Passenger* tempPassenger = temp10->getItem();
				if (j == Bus_passenger->getCount() - 1)
					cout << tempPassenger->get_id()<< "}";
				else
			      cout << tempPassenger->get_id() << ", ";
				temp10 = temp10->getNext();
			}
			tempQ5 = tempQ5->getNext();
		}
		Node<Bus*>* tempQ52 = FwdBus2->getHead();
		for (int i = 0; i < FwdBus2->getCount(); i++)
		{
			Bus* bustemp = tempQ52->getItem();
			cout << "\nB" << bustemp->GetBusId() << "[FWD, " << bustemp->GetBusType() << "Bus, " << bustemp->GetBusCapacity() << "] {";
			PriorityQueue<Passenger*>* Bus_passenger = bustemp->Get_Bus_Passengers();
			PQNode<Passenger*>* temp10 = Bus_passenger->getHead();
			for (int j = 0; j < Bus_passenger->getCount(); j++)
			{
				Passenger* tempPassenger = temp10->getItem();
				if (j == Bus_passenger->getCount() - 1)
					cout << tempPassenger->get_id() << "}";
				else
					cout << tempPassenger->get_id() << ", ";
				temp10 = temp10->getNext();
			}
			tempQ52 = tempQ52->getNext();
		}

		Node<Bus*>* tempQ6 = BckBus->getHead();
		for (int i = 0; i < BckBus->getCount(); i++)
		{
			Bus* bustemp = tempQ6->getItem();
			cout << "\nB" << bustemp->GetBusId() << "[BCK, " << bustemp->GetBusType() << "Bus, " << bustemp->GetBusCapacity() << "] {";
			PriorityQueue<Passenger*>* Bus_passenger = bustemp->Get_Bus_Passengers();
			PQNode<Passenger*>* temp11 = Bus_passenger->getHead();
			for (int j = 0; j < Bus_passenger->getCount(); j++)
			{
				Passenger* tempPassenger = temp11->getItem();
				if (j == Bus_passenger->getCount() - 1)
					cout << tempPassenger->get_id() << "}";
				else
					cout << tempPassenger->get_id() << ", ";
				temp11 = temp11->getNext();
			}
			tempQ6 = tempQ6->getNext();
		}

		Node<Bus*>* tempQ62 = BckBus2->getHead();
		for (int i = 0; i < BckBus2->getCount(); i++)
		{
			Bus* bustemp = tempQ62->getItem();
			cout << "\nB" << bustemp->GetBusId() << "[BCK, " << bustemp->GetBusType() << "Bus, " << bustemp->GetBusCapacity() << "] {";
			PriorityQueue<Passenger*>* Bus_passenger = bustemp->Get_Bus_Passengers();
			PQNode<Passenger*>* temp11 = Bus_passenger->getHead();
			for (int j = 0; j < Bus_passenger->getCount(); j++)
			{
				Passenger* tempPassenger = temp11->getItem();
				if (j == Bus_passenger->getCount() - 1)
					cout << tempPassenger->get_id() << "}";
				else
					cout << tempPassenger->get_id() << ", ";
				temp11 = temp11->getNext();
			}
			tempQ62 = tempQ62->getNext();
		}

		cout << "\n----------------------------------------------------------------------------------------------------\n";

		Node<Bus*>* tempQ7 = Checkup->getHead();
		int Check_count = Checkup->getCount();
		cout << Check_count <<" In_Checkup buses: ";
		for (int i = 0; i < Check_count; i++)
		{
			Bus* bustemp = tempQ7->getItem();
			if(i== Check_count-1)
		    	cout << bustemp->GetBusId();
			else
				cout << bustemp->GetBusId() << ", ";
			tempQ7 = tempQ7->getNext();
		}

		cout << "\n----------------------------------------------------------------------------------------------------\n";

		Node<Passenger*>* tempQ8 = finished->getHead();
		int finish_count = finished->getCount();
		cout << finish_count << " Finished passengers: ";

		for (int i = 0; i < finish_count; i++)
		{
			Passenger* tempP = tempQ8->getItem();
			int finish_id = tempP->get_id();
			cout << finish_id << ",";
			tempQ8 = tempQ8->getNext();
		}
		
		cout << "\n----------------------------------------------------------------------------------------------------\n";

		//Node<Bus*>* tempQ15 = FWDBusList->getHead();
		//int FWDmoving_count = FWDBusList->getCount();
		//cout << FWDmoving_count << " Forward moving buses: ";
		//for (int i = 0; i < FWDmoving_count; i++)
		//{
		//	Bus* bustemp = tempQ15->getItem();
		//	if (i == FWDmoving_count - 1)
		//		cout << bustemp->GetBusId();
		//	else
		//		cout << bustemp->GetBusId() << ", ";
		//	tempQ15 = tempQ15->getNext();
		//}
		//cout << endl;
		//Node<Bus*>* tempQ17 = BCKBusList->getHead();
		//int BCKmoving_count = BCKBusList->getCount();
		//cout << BCKmoving_count << " Backwawrd moving buses: ";
		//for (int i = 0; i < BCKmoving_count; i++)
		//{
		//	Bus* bustemp = tempQ17->getItem();
		//	if (i == BCKmoving_count - 1)
		//		cout << bustemp->GetBusId();
		//	else
		//		cout << bustemp->GetBusId() << ", ";
		//	tempQ17 = tempQ17->getNext();
		//}
		char x;
		cout << "\nPrint any key to display next station\n";
		//cin >> x;
}


void UI::SilentStart()
{
	cout << "\nSilent Mode\nSimulation Starts...";
}

void UI::SilentEnd()
{
	cout << "\nSimulation ends, Output file created.";
}

