#include "AddSwitch.h"


AddSwitch::AddSwitch(ApplicationManager *pApp) :Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

bool AddSwitch::ReadActionParameters(string s)
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
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;

	//GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	return true;
}

void AddSwitch::Execute()
{

	//Get Center point of the Gate
	ReadActionParameters("Adding Switch : Click to add the Switch");

	Switch *pS = new Switch(GInfo, AND2_FANOUT);
	pManager->AddComponent(pS);
}

void AddSwitch::Undo()
{}

void AddSwitch::Redo()
{}

