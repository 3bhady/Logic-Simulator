#pragma once
#include<fstream>
#include<string>
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
#include"..\Components\LED.h"
#include"..\Components\Switch.h"
class Load :
	public Action
{
public:
	Load(ApplicationManager*pApp);
	~Load();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};

