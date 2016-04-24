#pragma once
#include "C:\Users\dell\Desktop\PROJECT\Logic-Simulator\Actions\Action.h"

class AddGate : public Action
{
private:

	//Parameters for rectangular area to be occupied by the gate

	int Cx, Cy;				//Center point of the gate
	int x1, y1, x2, y2;		//Two corners of the rectangluar area
	ActionType ActType;		//Which gate to add
public:

	AddGate(ApplicationManager *pApp,ActionType);
	virtual ~AddGate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

