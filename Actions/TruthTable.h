#pragma once
#include "Action.h"
#include"AddSwitch.h"
#include"AddLED.h"
class TruthTable :
	public Action
{
	int RowWidth = 35,
		ColumnWidth = 35,
		Height,
		Width,
		StartX = 100,
		StartY = 50;
	int **Arr;

public:
	TruthTable(ApplicationManager*pApp);
	~TruthTable();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

