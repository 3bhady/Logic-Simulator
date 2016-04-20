
#include <iostream>
#include <sstream>
#include <cmath>

#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//test
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	window* Pwind = AppManager.GetOutput()->GetPwind();
	for (int j = 90; j < 650; j += 15)
	{
		for (int i = 15; i < 1360; i += 15)
		{
			Pwind->SetPen(SKYBLUE, 1);
			Pwind->DrawCircle(i, j, 1);
		}
	}
	do
	{
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the drawing window
		AppManager.UpdateInterface();


	}while(ActType != EXIT);

	return 0;
}

