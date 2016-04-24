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
	
	

	
	AND2 *pG=NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
	{ReadActionParameters( "2-Input AND Gate: Click to add the gate" );
	pG = new AND2( GInfo , AND2_FANOUT );
	break; }
	case ADD_OR_GATE_2:
		ReadActionParameters("2-Input OR Gate: Click to add the gate");
		//OR2 *pG = new OR2(GInfo, AND2_FANOUT);
		break;
	case ADD_Buff:
		ReadActionParameters("Buffer Gate: Click to add the gate");
		//BUFFER *pG = new BUFFER(GInfo, AND2_FANOUT);
		break;
	case ADD_INV:
		ReadActionParameters("Inverter Gate: Click to add the gate");
		//INVERTER *pG = new INVERTER(GInfo, AND2_FANOUT);
		break;
	case ADD_NAND_GATE_2:
		ReadActionParameters("2-Input NAND Gate: Click to add the gate");
		//NAND2 *pG = new NAND2(GInfo, AND2_FANOUT);
		break;
	case ADD_NOR_GATE_2:
		ReadActionParameters("2-Input NOR Gate: Click to add the gate");
		//NOR2 *pG = new NOR2(GInfo, AND2_FANOUT);
		break;
	case ADD_XOR_GATE_2:
		ReadActionParameters("2-Input XOR Gate: Click to add the gate");
		//XOR2 *pG = new XOR2(GInfo, AND2_FANOUT);
		break;
	case ADD_XNOR_GATE_2:
		ReadActionParameters("2-Input XNOR Gate: Click to add the gate");
		//XNOR2 *pG = new XNOR2(GInfo, AND2_FANOUT);
		break;
	case ADD_AND_GATE_3:
		ReadActionParameters("3-Input AND Gate: Click to add the gate");
		//AND3 *pG = new AND3(GInfo, AND2_FANOUT);
		break;
	case ADD_OR_GATE_3:
		ReadActionParameters("3-Input OR Gate: Click to add the gate");
		//OR3 *pG = new OR3(GInfo, AND2_FANOUT);
		break;
	case ADD_NAND_GATE_3:
		ReadActionParameters("3-Input NAND Gate: Click to add the gate");
		//NAND3 *pG = new NAND3(GInfo, AND2_FANOUT);
		break;
	case ADD_NOR_GATE_3:
		ReadActionParameters("3-Input NOR Gate: Click to add the gate");
		//NOR3 *pG = new NOR3(GInfo, AND2_FANOUT);
		break;
	case ADD_XOR_GATE_3:
		ReadActionParameters("3-Input XOR Gate: Click to add the gate");
		//XOR3 *pG = new XOR3(GInfo, AND2_FANOUT);
		break;
	case ADD_XNOR_GATE_3:
		ReadActionParameters("3-Input XNOR Gate: Click to add the gate");
		//XNOR3 *pG = new XNOR3(GInfo, AND2_FANOUT);
		break;
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
