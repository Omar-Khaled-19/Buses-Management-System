#pragma once
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "Event.h"
#include "Passenger.h"
#include "Bus.h"
#include "Station.h"
#include "Time.h"
class Company
{
private:
	LinkedQueue<Event*> EventPtrList;
	LinkedList<Station> SationList;
	int TripCheckupsNum;
	Time TimeBetStaions;
	LinkedQueue<Bus> BusList;
	LinkedQueue<Bus> ForwardMovingBusList;
	LinkedQueue<Bus> BackwardMovingBusList;
	LinkedQueue<Bus> MovingWCBusList;
	LinkedQueue<Bus> CheckupBusList;
	LinkedQueue<Passenger> FinishedPassengerList;

public:




};



