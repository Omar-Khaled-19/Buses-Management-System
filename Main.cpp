#include "LinkedQueue.h"
#include "QueueADT.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include "ArrayBag.h"
#include "Company.h"
#include "Event.h"
#include "Passenger.h"
#include "Bus.h"
#include "Station.h"
#include "Time.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"
#include <fstream>
#include <iostream>


int main() 
{
	string FileName;
	Company OurCompany;
    OurCompany.load(FileName);

	while (OurCompany.EventPtrList().I)
	{

	}
}