#pragma once
#include "Action.h"
class Redo :	public Action
{
public:
	Redo(ApplicationManager *pApp);
	virtual ~Redo(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void undo() {};
	virtual void redo() {};
};
