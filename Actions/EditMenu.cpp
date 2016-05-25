#include "EditMenu.h"



EditMenu::EditMenu(ApplicationManager*pApp) : Action(pApp)
{
}


EditMenu::~EditMenu()
{
}

bool EditMenu::ReadActionParameters()
{
	//Check if user clicked on a component or an empty area
	if (!UI.isForbidden(UI.EditMenuStartX, UI.EditMenuStartY))
		item = pManager->GetComponent(UI.EditMenuStartX, UI.EditMenuStartY);

	if (item)
		return true;
	return false;
}

void EditMenu::Execute()
{
	pManager->GetOutput()->CloseEditMenu(pManager);
	pManager->UpdateInterface( );
	pManager->GetOutput( )->UpdateBuffer( );
	pManager->GetOutput( )->SetBuffering( false );

	//Highlight the selected component
	if (ReadActionParameters())
	{
		if (!item->isSelected())
		{
			pManager->HighlightComponent(item);
			item->Draw(pManager->GetOutput());
		}
	}

	else pManager->ClearHighlightedCompList();

	pManager->UpdateInterface();

	UI.AppMode = EDIT_MODE;

}

void EditMenu::undo()
{
}

void EditMenu::redo()
{
}
