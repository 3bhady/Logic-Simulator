#include "EditMenu.h"



EditMenu::EditMenu(ApplicationManager*pApp) : Action(pApp)
{
}


EditMenu::~EditMenu()
{
}

bool EditMenu::ReadActionParameters(string s)
{
	if(!UI.isForbidden( UI.EditMenuStartX, UI.EditMenuStartY ))
	item = pManager->GetArr()[UI.EditMenuStartY][UI.EditMenuStartX];
	if(item)
	return true;
	return false;
}

void EditMenu::Execute()
{
	pManager->GetOutput()->CloseEditMenu(pManager);
	pManager->UpdateInterface( );
	pManager->GetOutput( )->UpdateBuffer( );
	pManager->GetOutput( )->SetBuffering( false );
	string s="";
	if (ReadActionParameters(s))
	{
		
		if (!item->isSelected())
		{
			item->Highlight();
			pManager->GetHighlightedList().push_back(item);
			item->Draw(pManager->GetOutput());
		}
	}
	else
	{
		for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
			pManager->GetHighlightedList()[i]->Unhighlight();

		pManager->GetHighlightedList().clear();

	}
	pManager->UpdateInterface();
	UI.AppMode = EDIT_MODE;

}

void EditMenu::undo()
{
}

void EditMenu::redo()
{
}
