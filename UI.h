#pragma once
#include <iostream>
#include "Time.h"
using namespace std;

class UI
{

public:
	int ChooseMode();
	void SilentStart();
	void SilentEnd();
	void InteractiveInterface();
	void printTime(Time& time);
};

