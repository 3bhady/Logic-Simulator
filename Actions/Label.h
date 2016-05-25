#pragma once
#include"Action.h"
class Label :public Action
{
public:
	Label(ApplicationManager *pApp);
	~Label();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

