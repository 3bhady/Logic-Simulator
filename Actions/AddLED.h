#pragma once
#include "Action.h"
#include"..\Components\LED.h"

class AddLED :
	public Action
{
private:

	//Parameters for rectangular area to be occupied by the gate
	GraphicsInfo GInfo; //Gfx info to be used to construct the  gate
	int Cx, Cy;				//Center point of the gate
	pair<int, int> inP;//the cooedeinates of the inputpin
	//int x1, y1, x2, y2;		//Two corners of the rectangluar area
	bool REDO=false;				//redo or adding new gate
public:

	AddLED(ApplicationManager *pApp);
	virtual ~AddLED(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void undo();
	virtual void redo();

};

