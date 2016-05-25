#pragma once
#include "Action.h"
class Delete :
	public Action
{
public:
	Delete(ApplicationManager *pApp);
virtual	~Delete( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

