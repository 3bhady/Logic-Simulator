#pragma once
#include "Action.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"
#include "..\Components\Switch.h"
#include "..\Components\Led.h"
class AddConnection :
	public Action
{

	GraphicsInfo GInfo; //Gfx info to be used to construct the  gate
	int Cx , Cy;				//Center point of the gate
								//int x1, y1, x2, y2;		//Two corners of the rectangluar area
	ActionType ActType;		//Which gate to add

	BFSOut outx;

public:

	AddConnection( ApplicationManager *pApp );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( );

	//Execute action (code depends on action type)
	virtual void Execute();
	void bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx);//the function the determines the path of the conncetion
	bool isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2,int x1);//the function the determines whether a piont is valied or not
	void LoadConnection(int ID1, int ID2);

	virtual void undo( );
	virtual void redo( );
	~AddConnection( );
};

