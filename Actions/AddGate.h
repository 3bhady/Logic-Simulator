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

class AddGate : public Action
{
private:

	//Parameters for rectangular area to be occupied by the gate
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	int Cx, Cy;				//Center point of the gate
	int x1, y1, x2, y2;		//Two corners of the rectangluar area
	ActionType ActType;		//Which gate to add
public:

	AddGate(ApplicationManager *pApp,ActionType);
	virtual ~AddGate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

