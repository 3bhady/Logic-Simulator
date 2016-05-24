#pragma once
#include "Action.h"
class Simulate :	public Action
{
public:
	Simulate(ApplicationManager *pApp);
	~Simulate();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();

	//returns true if simulation succeded
	static bool Run(ApplicationManager*pManager);

	//Gets the input pin status of the LED
	static STATUS dfs(vector<bool>& visited, const vector<Component*>& Complist, int index, int &result);
};

