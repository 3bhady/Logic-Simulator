#pragma once
#include "Action.h"
class Copy :	public Action
{
public:
	Copy(ApplicationManager * pApp);
	~Copy( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

