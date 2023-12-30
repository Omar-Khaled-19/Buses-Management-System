#include "Company.h"

Company::Company()
{
	
}

void Company::Load(string FileName)
{
	ifstream inFile(FileName);
	int NoOfStations, StationTime, WBus_count, MBus_count, WBusCap, MBusCap, CheckupTrips, C_WBus, C_MBus, maxWaitMin, GetOnOffSec, EventsNum;
	char temp; //Not used, only used to take the ":" to be able to read time step
	inFile >> NoOfStations >> StationTime >> WBus_count >> MBus_count >> WBusCap >> MBusCap >> CheckupTrips >> C_WBus >> C_MBus >> maxWaitMin >> GetOnOffSec >> EventsNum;
	WBusCount = WBus_count;
	MBusCount = MBus_count;
	StationNumber = NoOfStations;
	TimeBetStaions = StationTime;
	GetOnTime = GetOnOffSec;
	NumofJourneystoCheckup = CheckupTrips;
	WBus_checkup_duration = C_WBus;
	MBus_checkup_duration = C_MBus;
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
		Bus* tempbus = S->RemoveBusFromFullForwardBusList();
		tempbus->setLastMovingTime(clock);
		ForwardMovingBusList.enqueue(tempbus);
	}
}

void Company::UpdateBackwardMovingBusList(Station* S)
{
	int x = S->GetFullBackwardBusListCount();
	for (int i = 0;i < x;i++)
	{
		Bus* tempbus = S->RemoveBusFromFullBackwardBusList();
		tempbus->setLastMovingTime(clock);
		BackwardMovingBusList.enqueue(tempbus);
	}
}

void Company::UpdateCheckupBusList(Station* S)
{
	int x = S->GetNeedsCheckupBusListCount();
	for (int i = 0;i < x;i++)
	{
		Bus* B = S->RemoveBusFromNeedsCheckupBusList();
		B->set_check_start_time(clock);
		B->reset_journeys();
		CheckupBusList.enqueue(B);
	}
}


//////////////////////////////////////////**************////////////////////////////////////////////

void Company::RemoveFromCheckup()  /////////////called each minute 
{
	Bus* tempBus;
	Time Leave_time;
	char type;
	int duration;
	while (CheckupBusList.peek(tempBus))
	{
		type = tempBus->GetBusType();
		if (type == 'M')
			duration = MBus_checkup_duration;
		else
			duration = WBus_checkup_duration;
		Leave_time = tempBus->GetCheckStartTime() +duration;
		if (Leave_time == clock) {
			CheckupBusList.dequeue(tempBus);
			if (tempBus->GetNextStation() > tempBus->GetCurrStation()) {
				tempBus->setLastMovingTime(clock);
				ForwardMovingBusList.enqueue(tempBus);
			}
			else if (tempBus->GetNextStation() < tempBus->GetCurrStation()) {
				tempBus->setLastMovingTime(clock);
				BackwardMovingBusList.enqueue(tempBus);
			}
		}
		else return;
	}
}

void Company::ReleaseBuses()
{
	if (clock.GetMin() % 15 == 0)
	{
		Bus* tempbus;
		BusList.dequeue(tempbus);
		tempbus->setLastMovingTime(clock);
		ForwardMovingBusList.enqueue(tempbus);
	}
}

void Company::BusEnterStation()
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
				StationPtrArray[tempBus->GetCurrStation()]->AddBackwardBus(tempBus);
			}
			else {
				tempBus->SetNextStation(tempBus->GetNextStation() + 1);
				StationPtrArray[tempBus->GetCurrStation()]->AddForwardBus(tempBus);
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
				tempBus->increment_journeys();
				tempBus->SetNextStation(2);
				StationPtrArray[tempBus->GetCurrStation()]->AddForwardBus(tempBus);
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

void Company::Simulate(string FileName)
{
	clock.setTime(4, 00);
	UI User;
	Load(FileName);
	Event* E;
	while (clock.GetHour() < 5)
	{
		LinkedQueue<Event*> EventQueue;
		while (EventPtrList.peek(E) && E->get_event_time() == clock)
		{
			EventPtrList.dequeue(E);
			E->Excute();
			EventQueue.enqueue(E);
			EventPtrList.peek(E);
		}

		if (!BusList.isEmpty()) {
			ReleaseBuses();
		}

		BusEnterStation();
		
		for (int i = 1; i <= StationNumber ; i++) {
			StationPtrArray[i]->AllFWDBusOperation(GetOnTime, StationNumber, NumofJourneystoCheckup);
			StationPtrArray[i]->AllBWDBusOperation(GetOnTime, StationNumber);
			UpdateFinishedList(StationPtrArray[i]);
			UpdateCheckupBusList(StationPtrArray[i]);
			RemoveFromCheckup();

			User.printTime(clock);
			User.InteractiveInterface(i, StationPtrArray[i], &CheckupBusList, &FinishedPassengerList, &ForwardMovingBusList, &BackwardMovingBusList);
			
			UpdateForwardMovingBusList(StationPtrArray[i]);
			UpdateBackwardMovingBusList(StationPtrArray[i]);
			
		}
		++clock;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////



void Company::CreateOutputFile()
{
	ofstream Outfile;
	Outfile.open("Output file.txt");
	Outfile << "FT \tID\tAT \tWT \tTT\n";
	int finishNP = 0;
	int finishSP = 0; 
	int finishWP = 0;
	int PromotedNum = 10;
	Time totalWT;
	Time totalTT;
	int promotedPresentage = 0;
	if (FinishedPassengerList.getCount() != 0)
		promotedPresentage = (PromotedNum / FinishedPassengerList.getCount())*100;
	
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
	int avgTT_min = totalTT_min; // / FinishedPassengerList.getCount();
	int avgWT_min = totalWT_min; // / FinishedPassengerList.getCount();
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
	Outfile << "Passengers: "<< FinishedPassengerList.getCount() <<"    [NP: "<<finishNP<<", SP: "<<finishSP<<", WP: "<<finishWP;
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