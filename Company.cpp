#include "Company.h"

Company::Company()
{
	FinishedCount = 0;
	clock.setTime(04, 00);
}

Company::Company(string FileName) 
{
	load(FileName);
}

void Company::load(string FileName)
{
		ifstream inFile(FileName);
		int NoOfStations, StationTime, WBus_count, MBus_count, WBusCap, MBusCap, CheckupTrips, C_WBus, C_MBus, maxWaitMin, GetOnOffSec, EventsNum;
		char temp; //Not used, only used to take the ":" to be able to read time step
		inFile >> NoOfStations >> StationTime >> WBus_count >> MBus_count >> WBusCap >> MBusCap >> CheckupTrips >> C_WBus >> C_MBus >> maxWaitMin >> GetOnOffSec >> EventsNum;
		WBusCount = WBus_count;
		MBusCount = MBus_count;
		StationNumber = NoOfStations;
		TimeBetStaions = StationTime;
		for (int i = 0; i <= NoOfStations; i++)
		{
			StationPtrArray[i] = new Station(i);
		}
		bool flag = true;
		int tempMBus_count = MBus_count;
		int tempWBus_count = WBus_count;
		for (int i = 0; i < WBus_count + MBus_count; i++)
		{
			if (tempMBus_count != 0 && tempWBus_count != 0)
			{
				if (flag)
				{
					Bus* bus = new Bus(i + 1, MBusCap, 'M');
					BusList.enqueue(bus);
					flag = !flag;
					tempMBus_count--;
				}
				else if (!flag)
				{
					Bus* bus = new Bus(i + 1, WBusCap, 'W');
					BusList.enqueue(bus);
					flag = !flag;
					tempWBus_count--;
				}
			}
			else
			{
				if (tempMBus_count != 0)
				{
					Bus* bus = new Bus(i + 1, MBusCap, 'M');
					BusList.enqueue(bus);
					flag = !flag;
					tempMBus_count--;
					continue;
				}
				else 
				{
					Bus* bus = new Bus(i + 1, WBusCap, 'W');
					BusList.enqueue(bus);
					flag = !flag;
					tempWBus_count--;
				}
			}
		}
		
		for (int i = 0; i < EventsNum; i++)
		{
			string EventType;
			inFile >> EventType;
			if (EventType == "A")
			{
				string Type,SType;
				int TimeHour, TimeMin, id, StartStation, EndStation;
				inFile >>Type>> TimeHour >> temp >>TimeMin >>id >> StartStation >> EndStation;
				Time TimeStep(TimeHour, TimeMin);
				ArrivalEvent* arrive;
				if (Type == "SP")
				{
					inFile >> SType;
					arrive = new ArrivalEvent(id, Type, StationPtrArray[StartStation], StationPtrArray[EndStation], TimeStep, SType);
				}
				else
					arrive = new ArrivalEvent(id, Type, StationPtrArray[StartStation], StationPtrArray[EndStation], TimeStep);
				EventPtrList.enqueue(arrive);
			}
			if (EventType == "L")
			{
				int TimeHour2, TimeMin2, id, StartStation;
				inFile >> TimeHour2 >> temp >> TimeMin2 >> id >> StartStation;
				Time TimeStep2(TimeHour2, TimeMin2);
				LeaveEvent* leave = new LeaveEvent(id,StationPtrArray[StartStation],TimeStep2);
				EventPtrList.enqueue(leave);
			}

		}
	}

void Company::MovToFinishedList(Passenger* FinishedPassengerPtr)
{   
	FinishedPassengerList.enqueue(FinishedPassengerPtr);
	FinishedCount++;
}


int Company::generateRandom(int min, int max)
{
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<>dis(1, 100);
	return dis(gen);
}
/////////////////////////////////////////////UPDATES/////////////////////////////////////////////////////////

void Company::UpdateFinishedList(Station* S)
{
	int x = S->GetGoToFinishedPassengerListCount();
	for (int i = 0;i < x;i++)
	{
		FinishedPassengerList.enqueue(S->RemovePassengerFromGoToFinishedPassengerList());
	}
}

void Company::UpdateForwardMovingBusList(Station* S)
{
	int x = S->GetFullForwardBusListCount();
	for (int i = 0;i < x;i++)
	{
		ForwardMovingBusList.enqueue(S->RemoveBusFromFullForwardBusList());
	}
}

void Company::UpdateBackwardMovingBusList(Station* S)
{
	int x = S->GetFullForwardBusListCount();
	for (int i = 0;i < x;i++)
	{
		BackwardMovingBusList.enqueue(S->RemoveBusFromFullForwardBusList());
	}
}

void Company::UpdateCheckupBusList(Station* S)
{
	int x = S->GetNeedsCheckupBusListCount();
	for (int i = 0;i < x;i++)
	{
		CheckupBusList.enqueue(S->RemoveBusFromNeedsCheckupBusList());
	}
}


//////////////////////////////////////////**************////////////////////////////////////////////
void Company::move_to_checkup(Bus* checkup_bus, Time startTime)
{
	checkup_bus->set_check_start_time(startTime);
	CheckupBusList.enqueue(checkup_bus);
}

void Company::remove_from_checkup(Time curr_time)  /////////////called each minute 
{
	Bus* tempBus;
	Time Leave_time;
	while (CheckupBusList.peek(tempBus))
	{
		Leave_time = tempBus->GetCheckStartTime() + tempBus->GetchekupDurationInMinutes();
		if (Leave_time == curr_time) {
			CheckupBusList.dequeue(tempBus);
			if (tempBus->GetNextStation() > tempBus->GetCurrStation()) {
				ForwardMovingBusList.enqueue(tempBus);
			}
			else if (tempBus->GetNextStation() < tempBus->GetCurrStation()) {
				BackwardMovingBusList.enqueue(tempBus);
			}
		}
		else return;
	}
}

void Company::release_buses()
{
	if (clock.GetMin() % 15 == 0)
	{
		Bus* tempbus;
		BusList.dequeue(tempbus);
		ForwardMovingBusList.enqueue(tempbus);
	}
}

void Company::bus_enter_station()
{
	Bus* tempBus;
	while (ForwardMovingBusList.peek(tempBus))
	{
		if (clock - tempBus->GetLastMovingTime() == TimeBetStaions)
		{
			ForwardMovingBusList.dequeue(tempBus);
			tempBus->SetCurrStation(tempBus->GetNextStation());
			if (tempBus->GetCurrStation() == StationNumber) {
				tempBus->SetNextStation(StationNumber - 1);
				StationPtrArray[tempBus->GetNextStation()]->AddBackwardBus(tempBus);
			}
			else {
				tempBus->SetNextStation(tempBus->GetNextStation() + 1);
				StationPtrArray[tempBus->GetNextStation()]->AddForwardBus(tempBus);
			}
		}
		else
			break;
	}

	while (BackwardMovingBusList.peek(tempBus))
	{
		if (clock - tempBus->GetLastMovingTime() == TimeBetStaions)
		{
			BackwardMovingBusList.dequeue(tempBus);
			tempBus->SetCurrStation(tempBus->GetNextStation());
			if (tempBus->GetCurrStation() == 1) {
				tempBus->SetNextStation(2);
				StationPtrArray[tempBus->GetNextStation()]->AddForwardBus(tempBus);
			}
			else {
				tempBus->SetNextStation(tempBus->GetCurrStation() - 1);
				StationPtrArray[tempBus->GetNextStation()]->AddBackwardBus(tempBus);
			}
		}
		else
			break;
	}
}

////////////////////////////////**********************************//////////////////////////////

void Company::simulate(string FileName)
{
	UI User;
	Time clock(04, 00);
	load(FileName);
	Event* E;
	Passenger* P;
	char x;
	while (EventPtrList.peek(E) || clock.GetHour() < 10)
	{
		LinkedQueue<Event*> oneminuteEventQueue;
		while (E->get_event_time() == clock)
		{
			EventPtrList.dequeue(E);
			E->Excute();
			oneminuteEventQueue.enqueue(E);
			EventPtrList.peek(E);
		}

		if (!BusList.isEmpty()) {
			release_buses();
		}
		bus_enter_station();


		for (int i = 0; i++; i <= StationNumber) {
		//	int Num_of_ForwardBuses = StationPtrArray[i]->getnumoForwardfbuses();
		//	int Num_of_BackwardBuses = StationPtrArray[i]->getnumoBackwardfbuses();

		//	for (int i = 1; i++ i <= Num_of_ForwardBuses) {
		//		Bus* tempbus;
		//      int remaining_time = 60
		//		 
		//      tempbus  stationptrarray[i]->unload(getOfTime,remaining_time (by reference) )
		//		////movepassengerstofinished  ******//////////////       
		// 
		//			//movetocheckup if any
		// 
		//		if (tempbus->GetNum_of_Curr_Journeys() == NumofJourneystoCheckup) {
		//			temp StationPtrArray[i]->DequeueFirstForwardBus();
		//			move_to_checkup(tempbus, clock);
		//		}
		//		else {
		//			//boarding
		//          //sum of get on time
		//
		//			//move to moving bus list ?
		//		}
		//		for (int i = 1; i++ i <= Num_of_BackwardBuses) {
		//			Bus* tempbus2;
		//			tempbus2 = StationPtrArray[i]->PeekFirstBackwardBus();
		//			////movepassengerstofinished  ******////////////// 
		//				//movetocheckup if any
		//			if (tempbus->GetNum_of_Curr_Journeys() == NumofJourneystoCheckup) {
		//			    tempbus2 = StationPtrArray[i]->DequeueFirstBackwardBus();
		//				move_to_checkup(tempbus, clock);
		//			}
		//			else {
		//				//boarding
		//				//move to miving bus list
		//			}
		//	}
		//	}
		//}

		//////////////////////////////////////////////////////////////////////////////////////////
		clock.printTime();
		for (int i = 1; i <= StationNumber; i++)
		{
			int rand_number = generateRandom(1, 100);
			if (rand_number <= 25)
			{
				P = StationPtrArray[i]->MovSP();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}

			}
			else if (rand_number <= 60 && rand_number >= 50)
			{
				P = StationPtrArray[i]->MovNP();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}
			}
			else if (rand_number <= 45 && rand_number >= 35)
			{
				P = StationPtrArray[i]->MovWC();
				if (P != nullptr)
				{
					FinishedPassengerList.enqueue(P);
					FinishedCount++;
				}
			}
			StationPtrArray[i]->printStation(i);
			printFinished();
			cin >> x;
		}
		++clock;
	}
}

void Company:: printFinished()
{
	cout << FinishedCount << " Finished passengers: ";
	
	Node<Passenger*>* counter = FinishedPassengerList.getHead();
	for (int i = 0; i < FinishedCount; i++)
	{
		Passenger* temp = counter->getItem();
		if (temp)
		{
			int finish_id = temp->get_id();
			cout << finish_id << ",";
		}
		counter = counter->getNext();
	}
	cout << "\nPrint any key to display next station";
}

void Company::CreateOutputFile()
{
	ofstream Outfile;
	Outfile.open("Output file.txt");
	Outfile << "FT \tID\tAT \tWT \tTT\n";
	int finishNP = 0;
	int finishSP = 0; 
	int finishWP = 0;
	int PromotedNum = Station::numberOfPromoted;
	Time totalWT;
	Time totalTT;
	int promotedPresentage = (PromotedNum / FinishedCount)*100;
	while(!FinishedPassengerList.isEmpty())
	{
		Time ft, at;
		int wt_min, tt_min;
		int wt_hr = 0;
		int tt_hr = 0;
		Passenger* finished;
		FinishedPassengerList.dequeue(finished);
		ft = finished->get_FT();
		at = finished->get_AT();
		wt_min = finished->get_finish_WT();
		totalWT = totalWT + wt_min;
		tt_min = finished->get_TT();
		totalTT = totalTT + tt_min;
		string type = finished->get_type();
		if (type == "SP")
			finishSP++;
		if (type == "WP")
			finishWP++;
		if (type == "NP")
			finishNP++;
		while (wt_min > 59)
		{
			wt_min = wt_min-60;
			wt_hr++;
		}
		while (tt_min > 59)
		{
			tt_min = tt_min - 60;
			tt_hr++;
		}
		Outfile << "\n" << ft.GetHour() << ":" << ft.GetMin()<<"\t"<<finished->get_id()<<"\t";
	 	Outfile << at.GetHour() << ":" << at.GetMin() << "\t" << wt_hr << ":" << wt_min << "\t" << tt_hr << ":" << tt_min;
	}
	int totalTT_min = totalTT.GetMin() + ((totalTT.GetHour()) * 60);
	int totalWT_min = totalWT.GetMin() + ((totalWT.GetHour()) * 60);
	int avgTT_min = totalTT_min / FinishedCount;
	int avgWT_min = totalWT_min / FinishedCount;
	int avgTT_hr = 0;
	int avgWT_hr = 0;
	while (avgTT_min > 59)
	{
		avgTT_min = avgTT_min - 60;
		avgTT_hr++;
	}
	while (avgWT_min > 59)
	{
		avgWT_min = avgWT_min - 60;
		avgWT_hr++;
	}
	Outfile << "......................................\n......................................\n";
	Outfile << "Passengers: "<<FinishedCount<<"    [NP: "<<finishNP<<", SP: "<<finishSP<<", WP: "<<finishWP;
	Outfile << "\nPassengers Avg wait time = "<<avgWT_hr<<":"<<avgWT_min; 
	Outfile << "\nPassenger Avg trip time = "<<avgTT_hr<<":"<<avgTT_min;
	Outfile << "\nnAuto-promoted passengers: "<<promotedPresentage<<"%"; 
	Outfile << "\nBuses: " << WBusCount + MBusCount << "  [WBus: " << WBusCount << ", MBus: " << MBusCount << "]";
	Outfile << "\nAvg Busy time = "; //needs calculating
	Outfile << "\nAvg utilization = ";  //needs calculating
	Outfile.close();
}

Company::~Company()
{
	EventPtrList.~LinkedQueue();
	BusList.~LinkedQueue();
	ForwardMovingBusList.~LinkedQueue();
	BackwardMovingBusList.~LinkedQueue();
	CheckupBusList.~LinkedQueue();
	FinishedPassengerList.~LinkedQueue();
	delete[] StationPtrArray;
	


}