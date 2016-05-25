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
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

