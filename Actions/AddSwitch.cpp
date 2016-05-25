#include "AddSwitch.h"


AddSwitch::AddSwitch(ApplicationManager *pApp) :Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

bool AddSwitch::ReadActionParameters()
{
	return true;
}

void AddSwitch::Execute()
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Create new Switch
	Switch *pS = new Switch(GInfo, AND2_FANOUT);

	//if redo draw switch
	if (REDO)
	{
		pManager->GetOutput()->DrawSwitch(GInfo, LOW, false);
		pManager->AddComponent(pS);
		return;
	}

	//if the switch was successfully added this will return true and false if escape key was pressed to cancel the addition
	if (pOut->FollowMouseAndDraw(pS->get_GraphicInfo(), Switch_, pManager->GetArr()))
	{
		pManager->AddComponent(pS); GInfo = pS->get_GraphicInfo();
	}
	else delete pS;
}

void AddSwitch::undo()
{
	pManager->GetComponent(GInfo.x1, GInfo.y1)->DeleteComponent(pManager);
	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void AddSwitch::redo()
{
	REDO = true;
	Execute();
}

