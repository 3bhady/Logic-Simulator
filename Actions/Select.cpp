#include "Select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

bool Select::ReadActionParameters(string s)
{
	return true;
}

void Select::Execute()
{
	Component * selectedItem = pManager->GetArr( )[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1];	//the selected item
	
	
	if (selectedItem)					   //if the clicked area doesn't point to NULL
	{
		if (!selectedItem->isSelected())			//if the item is not highlighted , highlight it
		{
			selectedItem->Highlight();
			return;
		}
		GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();
		selectedItem->ChangeState();

		//todo put parameters to indicate the type of the gate to send it to follow mouse and draw 

		if (pManager->GetInput()->DetectChange())
		{
			selectedItem->DeleteComponent(pManager);
			pManager->GetOutput()->FollowMouseAndDraw(GfxInfo, ITM_AND2, pManager->GetArr(), true,50,50);
			selectedItem->get_GraphicInfo() = GfxInfo;
			selectedItem->AddComponent(pManager);
			selectedItem->Highlight();
		}
	}
}

void Select::Undo()
{
}

void Select::Redo()
{
}

Select::~Select()
{
}
