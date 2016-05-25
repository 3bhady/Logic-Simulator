#include "AddLED.h"


AddLED::AddLED(ApplicationManager *pApp) :Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

bool AddLED::ReadActionParameters()
{
	return true;
}

void AddLED::Execute()
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	LED *pL = new LED(GInfo);

	//if redo draw LED
	if (REDO)
	{
		pManager->GetOutput()->DrawLED(GInfo, LOW, false);
		pManager->AddComponent(pL);
		return;
	}

	 //if the LED was successfully added this will return true and false if escape key was pressed to cancel the addition
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

