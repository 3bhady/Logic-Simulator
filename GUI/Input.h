#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Component;
class ApplicationManager;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetString(Output*);		//Returns a string entered by the user


	ActionType GetUserAction( ApplicationManager * pApp,GraphicsInfo & r_GfxInfo  , Component ** Arr[780] , bool selected = false )const; //Reads the user click and maps it to an action

	~Input();
};
