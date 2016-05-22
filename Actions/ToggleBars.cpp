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
	if (UI.isInToolBarTitle(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1))
		if (UI.HiddenToolBar)
			pOut->ShowDesignToolBar();
		else pOut->HideDesignToolBar();
	if (UI.isInEditBarTitle(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1))
		if (UI.HiddenEditBar)
			pOut->ShowEditToolBar();
		else pOut->HideEditToolBar();
	if (UI.isInFileBarTitle(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1))
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
