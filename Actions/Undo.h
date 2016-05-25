#pragma once
#include "Action.h"
class Undo :	public Action
{
public:
	Undo(ApplicationManager *pApp);
	virtual ~Undo(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

