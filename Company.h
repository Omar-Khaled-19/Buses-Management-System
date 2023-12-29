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
#include "UI.h"
#include <fstream>
#include<random>
class Company
{
private:
	LinkedQueue<Event*> EventPtrList;
	int StationNumber;
	Station** StationPtrArray = new Station*[StationNumber];
	int TripCheckupsNum;
	int NumofJourneystoCheckup;
	int GetOnTime;
	Time TimeBetStaions;
	LinkedQueue<Bus*> BusList;
	LinkedQueue<Bus*> ForwardMovingBusList;
	LinkedQueue<Bus*> BackwardMovingBusList;
	LinkedQueue<Bus*> CheckupBusList;
	LinkedQueue<Passenger*> FinishedPassengerList;
	int FinishedCount;
	int WBusCount;
	int MBusCount;

public:
	Company(); // default constructor
	~Company(); // destructor
	Company(string FileName); // non-default constructor
	void load(string FileName);
	void MovToFinishedList(Passenger* FinishedPassengerPtr);
	void printFinished();
	void simulate(string FileName);
	int generateRandom(int min, int max);
	void CreateOutputFile();
	void move_to_checkup(Bus* checkup_bus, Time startTime);
	void remove_from_checkup(Time curr_time);
	void UpdateFinishedList(Station* S);
	void UpdateForwardMovingBusList(Station*S);
	void UpdateBackwardMovingBusList(Station* S);
	void UpdateCheckupBusList(Station* S);

	

};



