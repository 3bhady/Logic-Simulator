#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"
#include <ctime>

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
	bool DetectChange( ); //detects change in mouse movement to be used to determine the user action
	buttonstate GetButtonState( const button btMouse , int &iX , int &iY );


	ActionType GetUserAction( ApplicationManager * pApp, bool selected = false )const; //Reads the user click and maps it to an action

	~Input();
};
