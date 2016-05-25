#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
class Move :	public Action
{
public:
	Move(ApplicationManager* pApp);
	~Move( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters( );

	//Execute action
	virtual void Execute();

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();
	bool MoveSource( Connection* Comp );		//Changes the source of Connection
	virtual bool MoveDest( Connection* Comp );		//Changes the destination of the connection
	bool bfs( int x1 , int y1 , int x2 , int y2 , Component*** a , BFSOut &outx );//the function the determines the path of the connection
	bool isvalid( int x , int y , int** vis , int** ifc , int** oth , int x0 , int y0 , int x2 , int y2 , int x1 );//the function the determines whether a piont is valid or not

};

