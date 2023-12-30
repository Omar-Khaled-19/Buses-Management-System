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
	int StationNumber;
	int TripCheckupsNum;
	int NumofJourneystoCheckup;
	int GetOnTime;
	int TimeBetStaions;
	int WBusCount;
	int MBusCount;

	Station** StationPtrArray = new Station * [StationNumber];
	LinkedQueue<Event*> EventPtrList;
	LinkedQueue<Bus*> BusList;
	LinkedQueue<Bus*> ForwardMovingBusList;
	LinkedQueue<Bus*> BackwardMovingBusList;
	LinkedQueue<Bus*> CheckupBusList;
	LinkedQueue<Passenger*> FinishedPassengerList;
	

public:
	Company();  
	
	void Load(string FileName);
	void Simulate(string FileName);
	
	/*************************Bus Movement*******************************/
	void ReleaseBuses();
	void BusEnterStation();
	void UpdateForwardMovingBusList(Station*S);
	void UpdateBackwardMovingBusList(Station* S);
	
	/*************************Checkup Bus********************************/
	void UpdateCheckupBusList(Station* S);
	void RemoveFromCheckup();
	
	/*************************Printing Data*******************************/
	void UpdateFinishedList(Station* S);
	void CreateOutputFile();

	~Company();
	
};



