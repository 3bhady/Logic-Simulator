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
	if (REDO)
	{
		string GateImage = "Images\\PNG Gates\\",GateNumber;
		stringstream ss;
		ss << (int)ActType;
		ss >> GateNumber;
		GateImage += GateNumber + ".png";
		pManager->GetOutput()->DrawPNGImage(GateImage, GInfo);
		return true;
	}
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

void AddGate::undo()
{
	pManager->GetArr()[GInfo.y1][GInfo.x1]->DeleteComponent(pManager);
	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddGate::redo()
{
	REDO = true;
	Execute();
	/*
	Gate *pG = NULL; //a generic gate pointer to hold any type of gate to be added
	switch (ActType)
	{
	case ADD_AND_GATE_2:
	{
		pG = new AND2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\0", GInfo);
		break;
	}
	case ADD_OR_GATE_2:
	{
		pG = new OR2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\1", GInfo);
		break;
	}
	case ADD_Buff:
	{
		pG = new BUFFER(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\2", GInfo);
		break;
	}
	case ADD_INV:
	{
		pG = new NOT(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\3", GInfo);
		break;
	}
	case ADD_NAND_GATE_2:
	{
		pG = new NAND2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\4", GInfo);
		break;
	}
	case ADD_NOR_GATE_2:
	{
		pG = new NOR2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\5", GInfo);
		break;
	}
	case ADD_XOR_GATE_2:
	{
		pG = new XOR2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\6", GInfo);
		break;
	}
	case ADD_XNOR_GATE_2:
	{
		pG = new XNOR2(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\7", GInfo);
		break;
	}
	case ADD_AND_GATE_3:
	{
		pG = new AND3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\8", GInfo);
		break;
	}
	case ADD_OR_GATE_3:
	{
		pG = new OR3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\9", GInfo);
		break;
	}
	case ADD_NAND_GATE_3:
	{
		pG = new NAND3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\10", GInfo);
		break;
	}
	case ADD_NOR_GATE_3:
	{
		pG = new NOR3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\11", GInfo);
		break;
	}
	case ADD_XOR_GATE_3:
	{
		pG = new XOR3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\12", GInfo);
		break;
	}
	case ADD_XNOR_GATE_3:
	{
		pG = new XNOR3(GInfo, AND2_FANOUT);
		pManager->GetOutput()->DrawPNGImage("Images\\PNG Gates\\13", GInfo);
		break;
	}
	}
	if (pG)
		pManager->AddComponent(pG);
	*/
}
