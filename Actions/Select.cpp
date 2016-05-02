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
	
	if ( selectedItem )					   //if the clicked area doesn't point to NULL
	{	
		
	if ( !selectedItem->isSelected( ) )			//highlight the item if the item is not already highlighted
	{
		selectedItem->Highlight( );
		return;
	}
		GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component


		if (pManager->GetInput()->DetectChange())
		{
			vector<Component*> HighlightedVec;
			for (int i = 0; i< (int)pManager->GetCompList().size(); i++)
			{
				if (pManager->GetCompList()[i]->isSelected())
					HighlightedVec.push_back(pManager->GetCompList()[i]);
			}
			for (int i = 0; i <(int) HighlightedVec.size(); i++)
			{
				HighlightedVec[i]->DeleteComponent(pManager); //delete the component from the 2D array and draw an empty block over the gate
							 
			}
			pManager->GetOutput()->MoveComponents(HighlightedVec, pManager->GetArr(), selectedItem);
			
			for (int i = 0; i < (int)HighlightedVec.size(); i++)
			{
				HighlightedVec[i]->AddComponent(pManager);
				HighlightedVec[i]->Highlight();
			}
		}
		else selectedItem->Unhighlight();
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
