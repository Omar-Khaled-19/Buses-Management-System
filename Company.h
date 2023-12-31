#pragma once
#include "Event.h"
#include "Station.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include "UI.h"
#include <fstream>
class Company
{
private:
	Time clock;
	int StationNumber;
	int TripCheckupsNum;
	int MBus_checkup_duration;
	int WBus_checkup_duration;
	int NumofJourneystoCheckup;
	int GetOnTime;
	int TimeBetStaions;
	int WBusCount;
	int MBusCount;
	int MaxWaitingTime;
	int AllBusesBusyTime;
	int TotalUtilization;

	Station** StationPtrArray = new Station * [StationNumber];
	LinkedQueue<Event*> EventPtrList;
	LinkedQueue<Bus*> BusList;
	LinkedQueue<Bus*> ForwardMovingBusList;
	LinkedQueue<Bus*> BackwardMovingBusList;
	LinkedQueue<Bus*> CheckupBusList;
	LinkedQueue<Bus*> AllBusList;
	LinkedQueue<Passenger*> FinishedPassengerList;
	
public:
	Company();  
	
	void Load(string FileName);
	void SilentSimulate(string FileName);
	void InteractiveSimulate(string FileName);
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
	void BusBusyTime();
	void BusUtiTime();
	void TotalBusyTime();
	void TotalUtiTime();
	void UpdateFinishedList(Station* S);
	void CreateOutputFile();

	~Company();
	
};



