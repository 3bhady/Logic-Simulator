#pragma once
#include "Action.h"
#include"AddGate.h"
#include"AddConnection.h"
class Select :	public Action
{
	GraphicsInfo GFXInfo;			//gfxinfo of the selected item
	bool Move = false;				//1 = Move , 0 = Select
	vector< pair<GraphicsInfo, ComponentType> > InitialPositions;			//Initial positions before move
	vector< pair<GraphicsInfo, ComponentType> > FinalPositions;				//Final positions after move

public:
	Select(ApplicationManager *pApp);
	~Select();

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

	//virtual int CheckPin(pair<int,int> Coordinates);
	virtual bool MoveSource(Connection* Comp);		//Changes the source of Connection
	virtual bool MoveDest(Connection* Comp);		//Changes the destination of the connection

	bool bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx);//the function the determines the path of the connection
	bool isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1, int y1);//the function the determines whether a piont is valid or not

	virtual bool MoveOutPin(Connection* Comp);		//Change the coordinates of outpin
	virtual bool MoveInput(Connection* Comp	);		//Change the coordinates of inputpin

	virtual bool ReturnConnection(GraphicsInfo&OldGraphic,Connection*Comp);//the function that changes the source of Connection	
	bool MoveConnection(Connection*Comp);
};

