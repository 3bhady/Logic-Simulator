#pragma once
#include "Action.h"
class ToggleSwitchState :	public Action
{
public:
	
	ToggleSwitchState(ApplicationManager* pApp);
	~ToggleSwitchState();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

