#pragma once
#include "Action.h"
class New :	public Action
{
public:
	New(ApplicationManager*pApp);
	~New();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

