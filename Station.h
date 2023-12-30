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
	

	/******************Buses Lists*************************************************/
	LinkedQueue<Bus*> ForwardBusList;
	LinkedQueue<Bus*> FullForwardBusList;
	LinkedQueue<Bus*> BackwardBusList;
	LinkedQueue<Bus*> FullBackwardBusList;
	LinkedQueue<Bus*> NeedsCheckupBusList;
	LinkedQueue<Passenger*> GoToFinishedPassengerList;
	
	
	/*******************Waiting Passengers Lists***************************/
	LinkedQueue<Passenger*> WP_ForwardWaiting;
	LinkedQueue<Passenger*> WP_BackwardWaiting;
	ModifiedQueue<Passenger*> NP_ForwardWaiting;
	ModifiedQueue<Passenger*> NP_BackwardWaiting;
	PriorityQueue<Passenger*> SP_ForwardWaiting;
	PriorityQueue<Passenger*> SP_BackwardWaiting;
	int numberOfPromoted;
	

public:
	Station();
	Station(int stationNum);

	int GetStationNum();

	void LoadPassengersFWD(Bus* FBus, int& Time_count, int get_on_time);
	void LoadPassengersBWD(Bus* BBus, int& Time_count, int get_on_time,int TotalStationsNum);
	void UnloadPassengers(Bus* FBus, int& Time_count, int get_off_time);
	void AllFWDBusOperation(int get_on_off_time, int TotalNumOfStations, int NumOfJourneysToChecup);
	void AllBWDBusOperation(int get_on_off_time, int TotalNumOfStations);
	Passenger* RemovePassengerFromGoToFinishedPassengerList();
	int GetGoToFinishedPassengerListCount();
	Bus* RemoveBusFromNeedsCheckupBusList();
	int GetNeedsCheckupBusListCount();
	Bus* RemoveBusFromFullForwardBusList();
	int GetFullForwardBusListCount();
	Bus* RemoveBusFromFullBackwardBusList();
	int GetFullBackwardBusListCount();
    void remove_NP(int p_id);
	void add_passenger(Passenger* P);
	void AddForwardBus(Bus* newBus);
	void AddBackwardBus(Bus* newBus); 
	void PromoteNP(Time t, int max_waiting_time);
	PriorityQueue<Passenger*>* Get_FwdSP(); 
	PriorityQueue<Passenger*>* Get_BckSP();
	ModifiedQueue<Passenger*>* Get_FwdNP(); 
	ModifiedQueue<Passenger*>* Get_BckNP();
	LinkedQueue<Passenger*>* Get_FwdWP();
	LinkedQueue<Passenger*>* Get_BckWP(); 
	LinkedQueue<Bus*>* Get_FwdBus(); 
	LinkedQueue<Bus*>* Get_BckBus(); 
	LinkedQueue<Bus*>* Get_FwdBus2();
	LinkedQueue<Bus*>* Get_BckBus2();
	int Get_numberOfPromoted();
};


