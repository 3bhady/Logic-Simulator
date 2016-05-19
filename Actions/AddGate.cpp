#pragma once

#include "AddGate.h"

AddGate::AddGate(ApplicationManager *pApp,ActionType Action) :Action(pApp)
{
	ActType = Action;
}

AddGate::~AddGate(void)
{
}

bool AddGate::ReadActionParameters()
{
	return true;
}

void AddGate::Execute()
{
	if (REDO)			//if redo draw the gate in it's initial position
	{
		string GateImage = "Images\\PNG Gates\\", GateNumber;
		stringstream ss;
		ss << (int)ActType;
		ss >> GateNumber;
		GateImage += GateNumber + ".png";
		pManager->GetOutput()->DrawPNGImage(GateImage, GInfo);
	}

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	Gate *pG = NULL; //a generic gate pointer to hold any type of gate to be added

	switch (ActType)
	{
	case ADD_AND_GATE_2:
	{
		pG = new AND2( GInfo , AND2_FANOUT );
		break;
	}
	case ADD_OR_GATE_2:
	{
	pG = new OR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_Buff:
	{
	pG = new BUFFER(GInfo, AND2_FANOUT);
	break; }
	case ADD_INV:
	{
	pG = new NOT(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_2:
	{
	pG = new NAND2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_2:
	{
	pG = new NOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_2:
	{
	pG = new XOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_2:
	{
	pG = new XNOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_AND_GATE_3:
	{
	pG = new AND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_OR_GATE_3:
	{
	pG = new OR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_3:
	{
	pG = new NAND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_3:
	{
	pG = new NOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_3:
	{
	pG = new XOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_3:
	{
		pG = new XNOR3(GInfo, AND2_FANOUT);
		break;
	}
	}

	//if the gate wase successfully added this will return true and false otherwise with pressing escape key to cancel the addition
	if (pOut->FollowMouseAndDraw(pG->get_GraphicInfo(), (ComponentType)(int)ActType, pManager->GetArr()))
		pManager->AddComponent(pG);

	else delete pG;
}

void AddGate::undo()
{
	pManager->GetArr()[GInfo.y1][GInfo.x1]->DeleteComponent(pManager);
	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddGate::redo()
{
	REDO = true;
	Execute();
}
