#pragma once
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "Event.h"
#include "Passenger.h"
#include "Bus.h"
#include "Station.h"
#include "Time.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include <fstream>
class Company
{
private:
	LinkedQueue<Event*> EventPtrList;
	LinkedList<Station> SationList;
	Station** StationPtrArray;
	int TripCheckupsNum;
	Time TimeBetStaions;
	LinkedQueue<Bus> BusList;
	LinkedQueue<Bus> ForwardMovingBusList;
	LinkedQueue<Bus> BackwardMovingBusList;
	LinkedQueue<Bus> CheckupBusList;
	LinkedQueue<Passenger*> FinishedPassengerList;

public:
	Company();
	Company(string FileName);
	void load(string FileName);
	


};



