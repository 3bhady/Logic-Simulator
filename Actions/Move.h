#pragma once
#include "Action.h"
class Move :
	public Action
{
public:
	Move(ApplicationManager* pApp);
	~Move( );
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

