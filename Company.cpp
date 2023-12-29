#include "Company.h"

Company::Company()
{
	FinishedCount = 0;
	clock.setTime(04, 00);
}

Company::Company(string FileName) 
{
	load(FileName);
}

void Company::load(string FileName)
{
		ifstream inFile(FileName);
		int NoOfStations, StationTime, WBus_count, MBus_count, WBusCap, MBusCap, CheckupTrips, C_WBus, C_MBus, maxWaitMin, GetOnOffSec, EventsNum;
		char temp; //Not used, only used to take the ":" to be able to read time step
		inFile >> NoOfStations >> StationTime >> WBus_count >> MBus_count >> WBusCap >> MBusCap >> CheckupTrips >> C_WBus >> C_MBus >> maxWaitMin >> GetOnOffSec >> EventsNum;
		StationNumber = NoOfStations;
		for (int i = 0; i <= NoOfStations; i++)
		{
			StationPtrArray[i] = new Station(i);
		}
		bool flag = true;
		int tempMBus_count = MBus_count;
		int tempWBus_count = WBus_count;
		for (int i = 0; i < WBus_count + MBus_count; i++)
		{
			if (tempMBus_count != 0 && tempWBus_count != 0)
			{
				if (flag)
				{
					Bus* bus = new Bus(i + 1, MBusCap, 'M');
					BusList.enqueue(bus);
					flag = !flag;
					tempMBus_count--;
				}
				else if (!flag)
				{
					Bus* bus = new Bus(i + 1, WBusCap, 'W');
					BusList.enqueue(bus);
					flag = !flag;
					tempWBus_count--;
				}
			}
			else
			{
				if (tempMBus_count != 0)
				{
					Bus* bus = new Bus(i + 1, MBusCap, 'M');
					BusList.enqueue(bus);
					flag = !flag;
					tempMBus_count--;
					continue;
				}
				else 
				{
					Bus* bus = new Bus(i + 1, WBusCap, 'W');
					BusList.enqueue(bus);
					flag = !flag;
					tempWBus_count--;
				}
			}
		}
		
		for (int i = 0; i < EventsNum; i++)
		{
			string EventType;
			inFile >> EventType;
			if (EventType == "A")
			{
				string Type,SType;
				int TimeHour, TimeMin, id, StartStation, EndStation;
				inFile >>Type>> TimeHour >> temp >>TimeMin >>id >> StartStation >> EndStation;
				Time TimeStep(TimeHour, TimeMin);
				ArrivalEvent* arrive;
				if (Type == "SP")
				{
					inFile >> SType;
					arrive = new ArrivalEvent(id, Type, StationPtrArray[StartStation], StationPtrArray[EndStation], TimeStep, SType);
				}
				else
					arrive = new ArrivalEvent(id, Type, StationPtrArray[StartStation], StationPtrArray[EndStation], TimeStep);
				EventPtrList.enqueue(arrive);
			}
			if (EventType == "L")
			{
				int TimeHour2, TimeMin2, id, StartStation;
				inFile >> TimeHour2 >> temp >> TimeMin2 >> id >> StartStation;
				Time TimeStep2(TimeHour2, TimeMin2);
				LeaveEvent* leave = new LeaveEvent(id,StationPtrArray[StartStation],TimeStep2);
				EventPtrList.enqueue(leave);
			}

		}
	}

void Company::MovToFinishedList(Passenger* FinishedPassengerPtr)
{   
	FinishedPassengerList.enqueue(FinishedPassengerPtr);
	FinishedCount++;
}


int Company::generateRandom(int min, int max)
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<>dis(1, 100);
	return dis(gen);
}


//////////////////////////////////////////**************////////////////////////////////////////////
void Company::move_to_checkup(Bus* checkup_bus, Time startTime)
{
	checkup_bus->set_check_start_time(startTime);
	CheckupBusList.enqueue(checkup_bus);
}

void Company::remove_from_checkup(Time curr_time)  /////////////called each minute 
{
	Bus* tempBus;
	Time Leave_time;
	while (CheckupBusList.peek(tempBus))
	{
		Leave_time = tempBus->GetCheckStartTime() + tempBus->GetchekupDurationInMinutes();
		if (Leave_time == curr_time) {
			CheckupBusList.dequeue(tempBus);
			if (tempBus->GetNextStation() > tempBus->GetCurrStation()) {
				ForwardMovingBusList.enqueue(tempBus);
			}
			else if (tempBus->GetNextStation() < tempBus->GetCurrStation()) {
				BackwardMovingBusList.enqueue(tempBus);
			}
		}
		else return;
	}
}

void Company::release_buses()
{
	if (clock.GetMinute() % 15 == 0)
	{
		Bus* tempbus;
		BusList.dequeue(tempbus);
		ForwardMovingBusList.enqueue(tempbus);
	}
}

////////////////////////////////**********************************//////////////////////////////

void Company::simulate(string FileName)
{
	load(FileName);
	Event* E;
	Passenger* P;
	char x;
	while (EventPtrList.peek(E))
	{
		LinkedQueue<Event*> oneminuteEventQueue;
		while (E->get_event_time() == clock)
		{
			EventPtrList.dequeue(E);
			E->Excute();
			oneminuteEventQueue.enqueue(E);
			EventPtrList.peek(E);
		}




		//for (int i = 0; i++; i <= StationNumber) {
		//	int Num_of_ForwardBuses = StationPtrArray[i]->getnumoForwardfbuses();
		//	int Num_of_BackwardBuses = StationPtrArray[i]->getnumoBackwardfbuses();

		//	for (int i = 1; i++ i <= Num_of_ForwardBuses) {
		//		Bus* tempbus;
		//		tempbus = StationPtrArray[i]->PeekFirstForwardBus();
		//		////movepassengerstofinished  ******////////////// 
		//			//movetocheckup if any
		//		if (tempbus->GetNum_of_Curr_Journeys() == NumofJourneystoCheckup) {
		//			tempbus = StationPtrArray[i]->DequeueFirstForwardBus();
		//			move_to_checkup(tempbus, clock);
		//		}
		//		else {
		//			//boarding
		//			//move to miving bus list
		//		}
		//		for (int i = 1; i++ i <= Num_of_BackwardBuses) {
		//			Bus* tempbus2;
		//			tempbus2 = StationPtrArray[i]->PeekFirstBackwardBus();
		//			////movepassengerstofinished  ******////////////// 
		//				//movetocheckup if any
		//			if (tempbus->GetNum_of_Curr_Journeys() == NumofJourneystoCheckup) {
		//			    tempbus2 = StationPtrArray[i]->DequeueFirstBackwardBus();
		//				move_to_checkup(tempbus, clock);
		//			}
		//			else {
		//				//boarding
		//				//move to miving bus list
		//			}
		//	}
		//	}
		//}

		//////////////////////////////////////////////////////////////////////////////////////////
		clock.printTime();
		for (int i = 1; i <= StationNumber; i++)
		{
			int rand_number = generateRandom(1, 100);
			if (rand_number <= 25)
			{
				P = StationPtrArray[i]->MovSP();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}

			}
			else if (rand_number <= 60 && rand_number >= 50)
			{
				P = StationPtrArray[i]->MovNP();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}
			}
			else if (rand_number <= 45 && rand_number >= 35)
			{
				P = StationPtrArray[i]->MovWC();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}
			}
			StationPtrArray[i]->printStation(i);
			printFinished();
			cin >> x;
		}
		++clock;
	}
}

void Company:: printFinished()
{
	cout << FinishedCount << " Finished passengers: ";
	
	Node<Passenger*>* counter = FinishedPassengerList.getHead();
	for (int i = 0; i < FinishedCount; i++)
	{
		Passenger* temp = counter->getItem();
		if (temp)
		{
			int finish_id = temp->get_id();
			cout << finish_id << ",";
		}
		counter = counter->getNext();
	}
	cout << "\nPrint any key to display next station";
}

Company::~Company()
{
	EventPtrList.~LinkedQueue();
	BusList.~LinkedQueue();
	ForwardMovingBusList.~LinkedQueue();
	BackwardMovingBusList.~LinkedQueue();
	CheckupBusList.~LinkedQueue();
	FinishedPassengerList.~LinkedQueue();
	delete[] StationPtrArray;
	


}