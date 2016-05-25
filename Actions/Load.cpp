#include "Load.h"
#include"AddConnection.h"
Load::Load(ApplicationManager*pApp):Action(pApp)
{
}


Load::~Load()
{
}

bool Load::ReadActionParameters()
{
	return true;
}

void Load::Execute()
{
	//to do :clear the interface
	ifstream fin("save-load.txt");
	if (!fin.is_open())
		return;
	if (fin.eof())
		return;
	Component*pG;
	int CompNum;
	fin >> CompNum;
	string type;
	GraphicsInfo L_GfxInfo;
	for (int i = 0; i < CompNum; i++)
	{
		fin >> type;
		if (type == "AND2")
		{
			pG = new AND2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "AND3")
		{
			pG = new AND3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "BUFFER")
		{
			pG = new BUFFER(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "LED")
		{
			pG = new LED(L_GfxInfo);// , AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "NAND2")
		{
			pG = new NAND2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "NAND3")
		{
			pG = new NAND3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "NOR2")
		{
			pG = new NOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "NOR3")
		{
			pG = new NOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "INVERTER")
		{
			pG = new NOT(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "OR2")
		{
			pG = new OR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "OR3")
		{
			pG = new OR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "SWITCH")
		{
			pG = new Switch(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "XNOR2")
		{
			pG = new XNOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "XNOR3")
		{
			pG = new XNOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "XOR2")
		{
			pG = new XOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
		if (type == "XOR3")
		{
			pG = new XOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			pManager->AddComponent(pG);
		}
	}
	string s = "";
	fin >> s;
	while (!fin.eof())
	{
		int SrcID;
		int DstID;
		int x;
		fin >> SrcID;
		fin >> DstID;
		fin >> x;
		AddConnection*Load = new AddConnection(pManager);
		Load->LoadConnection(SrcID, DstID);
	}
}

void Load::undo()
{
}

void Load::redo()
{
}
