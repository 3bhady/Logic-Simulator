#pragma once
#include "Action.h"
#include"AddGate.h"
class Select :	public Action
{
	GraphicsInfo GFXInfo;				//gfxinfo of the selected item
	bool Move = false;							//1 = Move , 0 = Select

	vector< pair<GraphicsInfo, ComponentType> > InitialPositions;			//Initial positions before move
	vector< pair<GraphicsInfo, ComponentType> > FinalPositions;				//Final positions after move

public:
	Select(ApplicationManager *pApp);
	~Select();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

