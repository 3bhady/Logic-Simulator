#include "AddLED.h"


AddLED::AddLED(ApplicationManager *pApp) :Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

bool AddLED::ReadActionParameters()
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
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;

	//GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	inP = make_pair(GInfo.x1, GInfo.y1 + 15);

	return true;
	*/
	return true;
}

void AddLED::Execute()
{
	if (REDO)
		pManager->GetOutput()->DrawLED(GInfo, LOW, false);

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	LED *pL = new LED(GInfo);

	 //if the gate wase successfully added this will return true and false otherwise with pressing escape key to cancel the addition
	if (pOut->FollowMouseAndDraw(pL->get_GraphicInfo(), LED_ , pManager->GetArr()))
	{
		pManager->AddComponent(pL);
		GInfo = pL->get_GraphicInfo();
	}
	else delete pL;
}

void AddLED::undo()
{
	pManager->GetComponent(GInfo.x1, GInfo.y1)->DeleteComponent(pManager);
	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddLED::redo()
{
	REDO = true;
	Execute();
}

