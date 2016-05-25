#pragma once
#include "Action.h"
class Simulate :	public Action
{
public:
	Simulate(ApplicationManager *pApp);
	~Simulate();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

	//returns true if simulation succeded
	static bool Run(ApplicationManager*pManager);

	//Gets the input pin status of the LED
	static STATUS dfs(vector<bool>& visited,Component* &Comp, int index, int &result,ApplicationManager* pApp);
};

