#pragma once
#include "Action.h"
class Move :
	public Action
{
public:
	Move(ApplicationManager* pApp);
	~Move( );
	virtual bool ReadActionParameters( );

	//Execute action (code depends on action type)
	virtual void Execute( );

	//To undo this action (code depends on action type)
	virtual void undo( );

	//To redo this action (code depends on action type)
	virtual void redo( );
};

