#include "EditMenu.h"



EditMenu::EditMenu(ApplicationManager*pApp) : Action(pApp)
{
}


EditMenu::~EditMenu()
{
}

bool EditMenu::ReadActionParameters(string s)
{
	if(!UI.isForbidden(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1))
	item = pManager->GetArr()[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1];
	if(item)
	return true;
	return false;
}

void EditMenu::Execute()
{
	pManager->GetOutput()->CloseEditMenu();
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
