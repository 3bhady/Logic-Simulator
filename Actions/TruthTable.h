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
	int **Arr; //2D array of values 
	int* SwitchArr; //the original values of Switches

public:
	TruthTable(ApplicationManager*pApp);
	~TruthTable();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

