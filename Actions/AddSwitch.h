#pragma once
#include "Action.h"
#include"..\Components\Switch.h"

class AddSwitch :
	public Action
{
private:

	GraphicsInfo GInfo;		//Gfx info to be used to construct the  gate
	pair<int, int> outP;	//outpin coordinates
	bool REDO = false;		//redo or adding new switch

public:

	AddSwitch(ApplicationManager *pApp);
	virtual ~AddSwitch(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

