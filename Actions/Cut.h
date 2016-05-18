#pragma once
#include "Action.h"
#include"AddGate.h"
class Cut :	public Action
{
	vector< pair<GraphicsInfo, ComponentType> > ActionClipboard;
public:
	Cut(ApplicationManager* pApp);
	~Cut( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( string s );

	//Execute action (code depends on action type)
	virtual void Execute( );

	//To undo this action (code depends on action type)
	virtual void undo( );

	//To redo this action (code depends on action type)
	virtual void redo( );
};

