#pragma once
#include "LinkedQueue.h"
#include "Passenger.h"
#include "PriorityQueue.h"
#include "Company.h"
#include "Bus.h"

class Station
{
private:
	int StationNum;
	LinkedQueue<Bus*> ForwardBusList;
	LinkedQueue<Bus*> BackwardBusList;
	LinkedQueue<Passenger*> WP_ForwardWaiting;
	LinkedQueue<Passenger*> WP_BackwardWaiting;
	PriorityQueue<Passenger*> NP_SP_ForwardWaiting;
	PriorityQueue<Passenger*> NP_SP_BackwardWaiting;
public:
	Station();
	Station(int stationNum);
	Passenger* MovSP();
	Passenger* MovNP();
	Passenger* MovWC();
};

