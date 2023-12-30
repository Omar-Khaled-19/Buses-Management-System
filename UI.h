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
	void InteractiveInterface(int stationn,Station* stationptr, LinkedQueue<Bus*>* Checkup, LinkedQueue<Passenger*>* finished);
	void printTime(Time& time);
};

