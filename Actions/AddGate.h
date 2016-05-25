#pragma once
#include "Action.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\NAND2.h"
#include "..\Components\NAND3.h"
#include "..\Components\OR2.h"
#include "..\Components\NOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\OR3.h"
#include "..\Components\NOR3.h"
#include"..\Components\BUFFER.h"
#include"..\Components\NOT.h"
#include"..\Components\XOR3.h"
#include"..\Components\XNOR3.h"
#include<sstream>

class AddGate : public Action
{
private:

	GraphicsInfo GInfo;		//Gfx info to be used to construct the gate
	ActionType ActType;		//Which gate to add
	bool REDO = false;		//redo or adding new gate

public:

	AddGate( ApplicationManager *pApp , ActionType );
	virtual ~AddGate( void );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute( );

	//Undo this action
	virtual void undo();

	//Redo this action
	virtual void redo();

};

