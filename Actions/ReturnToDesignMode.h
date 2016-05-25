#pragma once
#include "Action.h"
class ReturnToDesignMode :	public Action
{
public:
	ReturnToDesignMode(ApplicationManager* pApp);
	~ReturnToDesignMode();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();
};

