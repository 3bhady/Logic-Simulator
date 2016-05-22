#include "ToggleBars.h"



ToggleBars::ToggleBars(ApplicationManager*pApp):Action(pApp)
{
}


ToggleBars::~ToggleBars()
{
}

bool ToggleBars::ReadActionParameters()
{
	return false;
}

void ToggleBars::Execute()
{
	Output*pOut = pManager->GetOutput();
	int x = UI.u_GfxInfo.x1;
	int y = UI.u_GfxInfo.y1;
	if (UI.isInToolBarTitle(x, y))
		if (UI.HiddenToolBar)
			pOut->ShowDesignToolBar();
		else pOut->HideDesignToolBar();
	if (UI.isInEditBarTitle(x, y))
		if (UI.HiddenEditBar)
			pOut->ShowEditToolBar();
		else pOut->HideEditToolBar();
	if (UI.isInFileBarTitle(x, y))
		if (UI.HiddenFileBar)
			pOut->ShowFileToolBar();
		else pOut->HideFileToolBar();


}

void ToggleBars::undo()
{
}

void ToggleBars::redo()
{
}
