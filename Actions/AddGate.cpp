#pragma once

#include "AddGate.h"

AddGate::AddGate(ApplicationManager *pApp,ActionType Action) :Action(pApp)
{
	ActType = Action;
}

AddGate::~AddGate(void)
{
}

void AddGate::ReadActionParameters(string s)
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//pOut->FollowMouseAndDraw( GInfo , ( DsgnMenuItem )( int )ActType , Arr , false );
	//Print Action Message
	pOut->PrintMsg(s);

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	
	pOut->ClearStatusBar();

	//Calculate the rectangle Corners
	int Len = UI.Gate_Width;
	int Wdth = UI.Gate_Height;

	//Get Center point of the Gate
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	

}

void AddGate::Execute()
{
	
	Gate *pG = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
	{ReadActionParameters("2-Input AND Gate: Click to add the gate");
	pG = new AND2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_OR_GATE_2:
	{ReadActionParameters("2-Input OR Gate: Click to add the gate");
	pG = new OR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_Buff:
	{ReadActionParameters("Buffer Gate: Click to add the gate");
	pG = new BUFFER(GInfo, AND2_FANOUT);
	break; }
	case ADD_INV:
	{ReadActionParameters("Inverter Gate: Click to add the gate");
	pG = new NOT(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_2:
	{ReadActionParameters("2-Input NAND Gate: Click to add the gate");
	pG = new NAND2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_2:
	{	ReadActionParameters("2-Input NOR Gate: Click to add the gate");
	pG = new NOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_2:
	{ReadActionParameters("2-Input XOR Gate: Click to add the gate");
	pG = new XOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_2:
	{ReadActionParameters("2-Input XNOR Gate: Click to add the gate");
	pG = new XNOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_AND_GATE_3:
	{ReadActionParameters("3-Input AND Gate: Click to add the gate");
	pG = new AND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_OR_GATE_3:
	{ReadActionParameters("3-Input OR Gate: Click to add the gate");
	pG = new OR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_3:
	{ReadActionParameters("3-Input NAND Gate: Click to add the gate");
	pG = new NAND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_3:
	{ReadActionParameters("3-Input NOR Gate: Click to add the gate");
	pG = new NOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_3:
	{ReadActionParameters("3-Input XOR Gate: Click to add the gate");
	pG = new XOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_3:
	{
		ReadActionParameters("3-Input XNOR Gate: Click to add the gate");
		pG = new XNOR3(GInfo, AND2_FANOUT);
		break;
	}
	}
	//ReadActionParameters();

	//AND2 *pA = new AND2(GInfo, AND2_FANOUT);
	if(pG )
	pManager->AddComponent(pG);
}

void AddGate::Undo()
{}

void AddGate::Redo()
{}
