#pragma once

#include "AddGate.h"

AddGate::AddGate(ApplicationManager *pApp,ActionType Action) :Action(pApp)
{
	ActType = Action;
}

AddGate::~AddGate(void)
{
}

bool AddGate::ReadActionParameters(string s)
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//if the gate wase successfully added this will return true and false otherwise with pressing escape key to cancel the addition
	return pOut->FollowMouseAndDraw( GInfo , ( ComponentType )( int )ActType , pManager->GetArr() , false );
	
	
}

void AddGate::Execute()
{
	
	Gate *pG = NULL; //a generic gate pointer to hold any type of gate to be added
	switch (ActType)
	{
	case ADD_AND_GATE_2:
	{

	if ( ReadActionParameters( "2-Input AND Gate: Click to add the gate" ) )
		pG = new AND2( GInfo , AND2_FANOUT );

			break;
	}
	case ADD_OR_GATE_2:
	{
		if(ReadActionParameters("2-Input OR Gate: Click to add the gate"))
	pG = new OR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_Buff:
	{
		if(ReadActionParameters("Buffer Gate: Click to add the gate"))
	pG = new BUFFER(GInfo, AND2_FANOUT);
	break; }
	case ADD_INV:
	{
		if(ReadActionParameters("Inverter Gate: Click to add the gate"))
	pG = new NOT(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_2:
	{
		if(ReadActionParameters("2-Input NAND Gate: Click to add the gate"))
	pG = new NAND2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_2:
	{	if(ReadActionParameters("2-Input NOR Gate: Click to add the gate"))
	pG = new NOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_2:
	{
		if(ReadActionParameters("2-Input XOR Gate: Click to add the gate"))
	pG = new XOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_2:
	{
		if(ReadActionParameters("2-Input XNOR Gate: Click to add the gate"))
	pG = new XNOR2(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_AND_GATE_3:
	{
		if(ReadActionParameters("3-Input AND Gate: Click to add the gate"))
	pG = new AND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_OR_GATE_3:
	{
		if(ReadActionParameters("3-Input OR Gate: Click to add the gate"))
	pG = new OR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NAND_GATE_3:
	{
		if(ReadActionParameters("3-Input NAND Gate: Click to add the gate"))
	pG = new NAND3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_NOR_GATE_3:
	{
		if(ReadActionParameters("3-Input NOR Gate: Click to add the gate"))
	pG = new NOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XOR_GATE_3:
	{
		if(ReadActionParameters("3-Input XOR Gate: Click to add the gate"))
	pG = new XOR3(GInfo, AND2_FANOUT);
	break;
	}
	case ADD_XNOR_GATE_3:
	{
		if(ReadActionParameters("3-Input XNOR Gate: Click to add the gate"))
		pG = new XNOR3(GInfo, AND2_FANOUT);
		break;
	}
	}
	if(pG )
	pManager->AddComponent(pG);
}

void AddGate::Undo()
{}

void AddGate::Redo()
{}
