#pragma once
#include "Action.h"
#include"AddGate.h"
#include"AddConnection.h"
class Select :	public Action
{
	GraphicsInfo GFXInfo;				//gfxinfo of the selected item
	bool Move;							//1 = Move , 0 = Select

	vector< pair<GraphicsInfo, ComponentType> > InitialPositions;			//Initial positions before move
	vector< pair<GraphicsInfo, ComponentType> > FinalPositions;				//Final positions after move

public:
	Select(ApplicationManager *pApp);
	~Select();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();

	//the function the determines the path of the conncetion
	void bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx);

	//the function the determines whether a piont is valied or not
	bool isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1);

};

