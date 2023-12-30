#pragma once
#include "LinkedQueue.h"
#include "ModifiedQueue.h"
#include "Bus.h"

class Station
{
private:
	int StationNum;
	int numberOfPromoted;

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
	
public:
	Station();
	Station(int stationNum);

	int GetStationNum();
	
	/**************************** Buses Operations ********************************/
	void AddForwardBus(Bus* newBus);
	void AddBackwardBus(Bus* newBus);
	Bus* RemoveBusFromNeedsCheckupBusList();
	Bus* RemoveBusFromFullForwardBusList();
	Bus* RemoveBusFromFullBackwardBusList();
	Passenger* RemovePassengerFromGoToFinishedPassengerList();
	void LoadPassengersFWD(Bus* FBus, int& Time_count, int get_on_time);
	void LoadPassengersBWD(Bus* BBus, int& Time_count, int get_on_time, int TotalStationsNum);
	void UnloadPassengers(Bus* FBus, int& Time_count, int get_off_time);
	void AllFWDBusOperation(int get_on_off_time, int TotalNumOfStations, int NumOfJourneysToChecup);
	void AllBWDBusOperation(int get_on_off_time, int TotalNumOfStations);
    

	/**************************** Counters ****************************************/
	int GetGoToFinishedPassengerListCount();
	int GetNeedsCheckupBusListCount();
	int GetFullForwardBusListCount();
	int GetFullBackwardBusListCount();
	

	/******************* Actions and Events ****************************************/
	void add_passenger(Passenger* P);
	void remove_NP(int p_id);
	void PromoteNP(Time t, int max_waiting_time);


	/**************************** Displaying Data ***********************************/
	int Get_numberOfPromoted();
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
};


