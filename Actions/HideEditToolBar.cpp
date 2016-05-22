#include "HideEditToolBar.h"



HideEditToolBar::HideEditToolBar(ApplicationManager*pApp) : Action(pApp)
{
}


HideEditToolBar::~HideEditToolBar()
{
}

bool HideEditToolBar::ReadActionParameters()
{
	return true;
}

void HideEditToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenEditBar = true;
	pOut->HideEditToolBar();
}

void HideEditToolBar::undo()
{
}

void HideEditToolBar::redo()
{
}
