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
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

