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
	Input(window*);		//constructor
	~Input();			//destructor

	clicktype GetPointClicked(int &, int &);	//Get coordinate where user clicks

	string GetString(Output*);		//Returns a string entered by the user

	bool DetectChange( ); //detects change in mouse movement to be used to determine the user action
	keytype GetKeyPressed( );
	buttonstate GetButtonState( const button btMouse , int &iX , int &iY );		//Gets the button state clicked or not

	ActionType GetUserAction( ApplicationManager * pApp )const;		//Reads the user click and maps it to an action
	bool close();//the function that closes any other function if the user pressed ESC
};
