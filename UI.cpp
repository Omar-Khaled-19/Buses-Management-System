#include "UI.h"

int UI::ChooseMode() //First thing to call in simulation
{
	int x;
	cout << "PLease enter: \n(1) for 'Interactive Mode'  \n(2) for 'Silent Mode'";
	cin >> x;
	while (x != 1 && x != 2)
	{
		cout << "Error! Please enter 1 or 2";
		cin >> x;
	}
	return x; 
}

void UI::InteractiveInterface()
{

}

void UI::SilentStart()
{
	cout << "\nSilent Mode\nSimulation Starts...";
}

void UI::SilentEnd()
{
	cout << "Simulation ends, Output file created.";
}

//void UI::printTime(Time& time)
//{
//	cout << "Current Time (Hour:Min)==> " << time.GetHour() << ":" << time.GetMin() << endl;
//}
