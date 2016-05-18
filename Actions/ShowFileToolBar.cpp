#include "ShowFileToolBar.h"



ShowFileToolBar::ShowFileToolBar(ApplicationManager*pApp) : Action(pApp)
{
}


ShowFileToolBar::~ShowFileToolBar()
{
}

bool ShowFileToolBar::ReadActionParameters(string s)
{
	return true;
}

void ShowFileToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenFileBar = false;
	pOut->ShowFileToolBar();
}

void ShowFileToolBar::undo()
{
}

void ShowFileToolBar::redo()
{
}
