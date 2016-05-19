#include "HideDesignToolBar.h"



HideDesignToolBar::HideDesignToolBar(ApplicationManager*pApp) : Action(pApp) 
{
}


HideDesignToolBar::~HideDesignToolBar()
{
}

bool HideDesignToolBar::ReadActionParameters(string s)
{
	return true;
}

void HideDesignToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenToolBar = true;
	pOut->HideDesignToolBar();
}

void HideDesignToolBar::undo()
{
}

void HideDesignToolBar::redo()
{
}
