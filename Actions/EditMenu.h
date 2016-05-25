#pragma once
#include "Action.h"
class EditMenu :
	public Action
{
	Component*item;
public:
	EditMenu(ApplicationManager*pApp);
	~EditMenu();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

