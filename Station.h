#pragma once
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "Bus.h"
#include "Passenger.h"
#include "modified_priority_queue.h"


class Station
{
private:
	int StationNum;
	LinkedQueue<Bus*> ForwardBusList;
	LinkedQueue<Bus*> BackwardBusList;
	LinkedQueue<Passenger*> WP_ForwardWaiting;
	LinkedQueue<Passenger*> WP_BackwardWaiting;
	Modified_Priority_Queue<Passenger*> NP_SP_ForwardWaiting;
	Modified_Priority_Queue<Passenger*> NP_SP_BackwardWaiting;
public:
	Station();
	Station(int stationNum);

	Passenger* MovSP();
	Passenger* MovNP();
	Passenger* MovWC();
	void remove_NP(int p_id);
	void add_NP_SP(Passenger* P);

};

