#pragma once
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "Bus.h"
#include "Passenger.h"
#include "modified_priority_queue.h"
#include <iostream>


class Station
{
private:
	int StationNum;
	int FWD_NP;
	int BCK_NP;
	int FWD_SP_age;
	int FWD_SP_pod;
	int FWD_SP_preg;
	int BCK_SP_age;
	int BCK_SP_pod;
	int BCK_SP_preg;
	int FWD_WP;
	int BCK_WP;
	LinkedQueue<Bus*> ForwardBusList;
	LinkedQueue<Bus*> BackwardBusList;
	LinkedQueue<Passenger*> WP_ForwardWaiting;
	LinkedQueue<Passenger*> WP_BackwardWaiting;
	Modified_Priority_Queue<Passenger*> NP_ForwardWaiting;
	Modified_Priority_Queue<Passenger*> NP_BackwardWaiting;
	Modified_Priority_Queue<Passenger*> SP_ForwardWaiting;
	Modified_Priority_Queue<Passenger*> SP_BackwardWaiting;
public:
	Station();
	Station(int stationNum);

	Passenger* MovSP();
	Passenger* MovNP();
	Passenger* MovWC();
	void remove_NP(int p_id);
	void add_passenger(Passenger* P);
	void printStation(int stationn);
};

