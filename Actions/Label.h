#pragma once
#include"Action.h"
class Label :public Action
{
public:
	Label(ApplicationManager *pApp);
	~Label();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

