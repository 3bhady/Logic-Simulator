#include "AddSwitch.h"


AddSwitch::AddSwitch(ApplicationManager *pApp) :Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

bool AddSwitch::ReadActionParameters()
{
	/*
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
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;

	//GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	outP = make_pair(GInfo.x2, GInfo.y1 + 15);
	return true;
	*/
	return true;
}

void AddSwitch::Execute()
{

	if (REDO)
		pManager->GetOutput()->DrawSwitch(GInfo, LOW, false);


	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	Switch *pS = new Switch(GInfo, AND2_FANOUT);

	//if the gate wase successfully added this will return true and false otherwise with pressing escape key to cancel the addition
	if (pOut->FollowMouseAndDraw(GInfo, Switch_, pManager->GetArr()))
		pManager->AddComponent(pS);
	else delete pS;
}

void AddSwitch::undo()
{
	pManager->GetArr()[GInfo.y1][GInfo.x1]->DeleteComponent(pManager);
	pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddSwitch::redo()
{
	REDO = true;
	Execute();
}

