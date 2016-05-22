#include "HideFileToolBar.h"



HideFileToolBar::HideFileToolBar(ApplicationManager*pApp) : Action(pApp)
{
}


HideFileToolBar::~HideFileToolBar()
{
}

bool HideFileToolBar::ReadActionParameters()
{
	return true;
}

void HideFileToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenFileBar = true;
	pOut->HideFileToolBar();
}

void HideFileToolBar::undo()
{
}

void HideFileToolBar::redo()
{
}
