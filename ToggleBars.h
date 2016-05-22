#pragma once
#include"ApplicationManager.h"
#include "Actions\Action.h"
class ToggleBars :
	public Action
{
public:
	ToggleBars(ApplicationManager*pApp);
	~ToggleBars();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

