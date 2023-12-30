#pragma once
#include <iostream>
#include "Time.h"
#include "Station.h"

using namespace std;

class UI
{

public:
	int ChooseMode();
	void SilentStart();
	void SilentEnd();
	void InteractiveInterface(int stationn,Station* stationptr, LinkedQueue<Bus*>* Checkup, LinkedQueue<Passenger*>* finished, LinkedQueue<Bus*>* FWDBusList, LinkedQueue<Bus*>* BCKBusList);
	void printTime(Time time);
};

