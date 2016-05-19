#pragma once
#include "Action.h"
class Delete :
	public Action
{
public:
	Delete(ApplicationManager *pApp);
virtual	~Delete( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( string s );

	//Execute action (code depends on action type)
	virtual void Execute( );

	virtual void undo( );
	virtual void redo( );
};

