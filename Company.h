#pragma once
#include "LinkedQueue.h"
#include "Event.h"
#include "Passenger.h"
#include "Bus.h"
#include "Station.h"
#include "Time.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include "UI.h"
#include <fstream>
#include<random>
class Company
{
private:
	Time clock;
	LinkedQueue<Event*> EventPtrList;
	int StationNumber;
	Station* * StationPtrArray = new Station*[StationNumber];
	int TripCheckupsNum;
	int NumofJourneystoCheckup;
	int GetOnTime;
	int TimeBetStaions;
	LinkedQueue<Bus*> BusList;
	LinkedQueue<Bus*> ForwardMovingBusList;
	LinkedQueue<Bus*> BackwardMovingBusList;
	LinkedQueue<Bus*> CheckupBusList;
	LinkedQueue<Passenger*> FinishedPassengerList;
	int WBusCount;
	int MBusCount;

public:
	Company(); // default constructor
	~Company(); // destructor
	Company(string FileName); // non-default constructor
	void load(string FileName);
	void printFinished();
	void simulate(string FileName);
	int generateRandom(int min, int max);
	void CreateOutputFile();
	void remove_from_checkup();
	void UpdateFinishedList(Station* S);
	void UpdateForwardMovingBusList(Station*S);
	void UpdateBackwardMovingBusList(Station* S);
	void UpdateCheckupBusList(Station* S);

	void release_buses();
	void bus_enter_station();
	
};



