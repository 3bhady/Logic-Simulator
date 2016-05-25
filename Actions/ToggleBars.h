#pragma once
#include"..\ApplicationManager.h"
#include "Action.h"
class ToggleBars :
	public Action
{
public:
	ToggleBars(ApplicationManager*pApp);
	~ToggleBars();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

