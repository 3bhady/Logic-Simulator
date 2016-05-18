#pragma once
//#include "Action.h"
#include "AddGate.h"
class Paste :	public Action
{
	vector < pair<GraphicsInfo, ComponentType> > ActionClipBoard;
public:
	Paste(ApplicationManager * pApp);
	~Paste( );
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( string s );

	//Execute action (code depends on action type)
	virtual void Execute( );

	//To undo this action (code depends on action type)
	virtual void undo( );

	//To redo this action (code depends on action type)
	virtual void redo( );
};

