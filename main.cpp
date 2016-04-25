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
	window* pWind = AppManager.GetOutput()->GetPwind();

	do
	{
		//Read user action
		ActType = AppManager.GetUserAction();

		//Execute the action


		AppManager.ExecuteAction(ActType);

		//Update the drawing window
		AppManager.UpdateInterface();

		//commentat kteer el fatra el gaya
		//
		// ana //mesh
		//3arfny

	}while(ActType != EXIT);

	return 0;
}

