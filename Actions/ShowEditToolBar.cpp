#include "ShowEditToolBar.h"



ShowEditToolBar::ShowEditToolBar(ApplicationManager*pApp) : Action(pApp)
{
}


ShowEditToolBar::~ShowEditToolBar()
{
}

bool ShowEditToolBar::ReadActionParameters()
{
	return true;
}

void ShowEditToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenEditBar = false;
	pOut->ShowEditToolBar();
}


void ShowEditToolBar::undo()
{
}

void ShowEditToolBar::redo()
{
}
