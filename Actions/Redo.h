#pragma once
#include "Action.h"
class Redo :	public Action
{
public:
	Redo(ApplicationManager *pApp);
	virtual ~Redo(void);

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};
