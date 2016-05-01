#pragma once
#include "Action.h"
class AreaSelect :
	public Action
{

public:
	AreaSelect(ApplicationManager* pApp);
	~AreaSelect( );
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( string s );

	//Execute action (code depends on action type)
	virtual void Execute( );

	//To undo this action (code depends on action type)
	virtual void Undo( ) ;

	//To redo this action (code depends on action type)
	void Redo( );


};

