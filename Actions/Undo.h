#pragma once
#include "Action.h"
class Undo :	public Action
{
public:
	Undo(ApplicationManager *pApp);
	virtual ~Undo(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void undo() {};
	virtual void redo() {};
};

