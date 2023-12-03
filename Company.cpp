#include "Company.h"

Company::Company()
{

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
				string Type;
				int TimeHour, TimeMin, id, StartStation, EndStation;
				inFile >>Type>> TimeHour >> temp >>TimeMin >>id >> StartStation >> EndStation;
				Time TimeStep(TimeHour, TimeMin);
				ArrivalEvent *arrive= new ArrivalEvent(id,Type, StationPtrArray[StartStation], StationPtrArray[EndStation], TimeStep);
				EventPtrList.enqueue(arrive);
			}
			else if (EventType == "L")
			{
				int TimeHour, TimeMin, id, StartStation;
				Time TimeStep(TimeHour, TimeMin);
				inFile >> TimeHour >> temp >> TimeMin >> id >> StartStation;
				LeaveEvent* leave = new LeaveEvent(id,StationPtrArray[StartStation],TimeStep);
				EventPtrList.enqueue(leave);
			}

		}
	}

void Company::MovToFinishedList(Passenger* FinishedPassengerPtr)
{   
	FinishedPassengerList.enqueue(FinishedPassengerPtr);
}

void Company::Simulator(string FileName)
{
 
}


int Company::generateRandom(int min, int max)
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<>dis(1, 100);
	return dis(gen);
}

void Company::simulate()
{
	load("Ay_haga.txt");
	Time clock(04,00);
	
	Event* E;
	Passenger* P;
	while (EventPtrList.isEmpty())
	{
		++clock;
		EventPtrList.peek(E);
		if (E->get_event_time() == clock)
		{
			EventPtrList.dequeue(E);
			E->Excute();
		}
	}
	for (int i = 1; i <= StationNumber; i++)
	{
		int rand_number = generateRandom(1, 100);
		if (rand_number < 25)
		{
		//	StationPtrArray[i]->get_SP_queue().dequeue(P);
			FinishedPassengerList.enqueue(P);
		}
		
	}
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