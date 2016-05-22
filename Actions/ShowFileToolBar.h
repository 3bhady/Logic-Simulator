#pragma once
#include "Action.h"
class ShowFileToolBar :
	public Action
{
public:
	ShowFileToolBar(ApplicationManager*pApp);
	~ShowFileToolBar();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

