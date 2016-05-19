#pragma once
#include "Action.h"
class Save :
	public Action
{
public:
	Save(ApplicationManager*pApp);
	~Save();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

