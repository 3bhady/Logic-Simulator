#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
class Move :	public Action
{
public:
	Move(ApplicationManager* pApp);
	~Move( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

