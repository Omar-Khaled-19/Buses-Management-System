#include "Company.h"

Company::Company()
{
	FinishedCount = 0;
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
			//StationPtrArray[i] = new Station(i);
			StationPtrArray[i] = new Station(i);
		}
		for (int i = 0; i < WBus_count; i++)
		{
			Bus bus(i+1, WBusCap,'W');
			Bus* busptr=&bus;
			BusList.enqueue(busptr);
		}
		for (int i = 0; i < MBus_count; i++)
		{
			Bus bus(i+WBus_count, MBusCap, 'M');
			Bus* busptr = &bus;
			BusList.enqueue(busptr);
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
			else if (EventType == "L")
			{
				int TimeHour, TimeMin, id, StartStation;
				inFile >> TimeHour >> temp >> TimeMin >> id >> StartStation;
				Time TimeStep(TimeHour, TimeMin);
				LeaveEvent* leave = new LeaveEvent(id,StationPtrArray[StartStation],TimeStep);
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

void Company::simulate(string FileName)
{
	Time clock(04, 00);
	load(FileName);
	cout << StationNumber;
	Event* E;
	Passenger* P;
	char x;
	while (EventPtrList.peek(E))
	{
		while (E->get_event_time() == clock)
		{
			EventPtrList.dequeue(E);
			E->Excute();
		}
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