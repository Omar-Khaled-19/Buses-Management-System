#pragma once
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "Bus.h"
#include "Passenger.h"
#include "PriorityQueue.h"
#include "ModifiedQueue.h"
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
	ModifiedQueue<Passenger*> NP_ForwardWaiting;
	ModifiedQueue<Passenger*> NP_BackwardWaiting;
	PriorityQueue<Passenger*> SP_ForwardWaiting;
	PriorityQueue<Passenger*> SP_BackwardWaiting;

	static int numberOfPromoted;

public:
	Station();
	Station(int stationNum);

	int GetStaionNum();

	Passenger* MovSP();
	Passenger* MovNP();
	Passenger* MovWC();
	void GetPassengerOn();
	LinkedQueue<Passenger*> GetPassengerOff();
    void remove_NP(int p_id);
	void add_passenger(Passenger* P);
	void AddForwardBus(Bus* newBus);
	void AddBackwardBus(Bus* newBus);
	void printStation(int stationn);
	Bus* PeekFirstForwardBus();
	Bus* PeekFirstBackwardBus();
	Bus* DequeueFirstForwardBus();
	Bus* DequeueFirstBackwardBus();
	void PromoteNP(Time t, int max_waiting_time);
	
};

int Station::numberOfPromoted = 0;
