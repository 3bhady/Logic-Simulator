#include "ShowDesignToolBar.h"



ShowDesignToolBar::ShowDesignToolBar(ApplicationManager*pApp) : Action(pApp)
{

}


ShowDesignToolBar::~ShowDesignToolBar()
{
}

bool ShowDesignToolBar::ReadActionParameters()
{
	return true;
}

void ShowDesignToolBar::Execute()
{
	Output*pOut = pManager->GetOutput();
	UI.HiddenToolBar = false;
	pOut->ShowDesignToolBar();
}

void ShowDesignToolBar::undo()
{
}

void ShowDesignToolBar::redo()
{
}
