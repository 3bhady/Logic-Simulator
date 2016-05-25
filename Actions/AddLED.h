#pragma once
#include "Action.h"
#include"..\Components\LED.h"

class AddLED :	public Action
{
private:

	GraphicsInfo GInfo;		//Gfx info to be used to construct the  gate
	pair<int, int> inP;		//the coordinates of the inputpin
	bool REDO = false;		//redo or adding new LED

public:

	AddLED(ApplicationManager *pApp);
	virtual ~AddLED(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

