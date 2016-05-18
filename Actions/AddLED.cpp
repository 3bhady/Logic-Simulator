#include "AddLED.h"


AddLED::AddLED(ApplicationManager *pApp) :Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

bool AddLED::ReadActionParameters(string s)
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
	int Len = UI.LED_Width;
	int Wdth = UI.LED_Height;

	//GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	return true;
}

void AddLED::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters("Adding LED : Click to add the LED");

	LED *pL = new LED(GInfo, AND2_FANOUT);
	pManager->AddComponent(pL);
}

void AddLED::undo()
{
	pManager->GetArr()[GInfo.y1][GInfo.x1]->DeleteComponent(pManager);
	pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddLED::redo()
{
	REDO = true;
	Execute();
}

