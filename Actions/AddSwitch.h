#pragma once
#include "Action.h"
#include"..\Components\Switch.h"

class AddSwitch :
	public Action
{
private:

	//Parameters for rectangular area to be occupied by the gate
	GraphicsInfo GInfo; //Gfx info to be used to construct the  gate
	int Cx, Cy;				//Center point of the gate
	//int x1, y1, x2, y2;		//Two corners of the rectangluar area
	bool REDO=false;				//redo or adding new gate
	pair<int, int> outP;//outpin coordinates
public:

	AddSwitch(ApplicationManager *pApp);
	virtual ~AddSwitch(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void undo();
	virtual void redo();

};

