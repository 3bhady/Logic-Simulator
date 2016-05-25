#include "ReturnToDesignMode.h"



ReturnToDesignMode::ReturnToDesignMode(ApplicationManager* pApp):Action(pApp)
{
}


ReturnToDesignMode::~ReturnToDesignMode()
{
}

bool ReturnToDesignMode::ReadActionParameters()
{
	return true;
}

void ReturnToDesignMode::Execute()
{
	UI.AppMode = DESIGN;
	pManager->TurnOffLEDs();
	pManager->GetOutput()->ShowDesignToolBar();
	pManager->GetOutput()->CreateGrid();
	pManager->GetOutput()->CreateToolBars();
	pManager->UpdateInterface();
	pManager->GetOutput()->UpdateBuffer();
}

void ReturnToDesignMode::undo()
{
}

void ReturnToDesignMode::redo()
{
}
