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
			pManager->GetHighlightedList().push_back(selectedItem);		//push it in the highlighted comp list
			return;
		}
			GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component

			if (pManager->GetInput()->DetectChange())		//Move 
			{
				/*
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
				*/

				//delete the components from the 2D array and draw an empty block over the gate
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
					pManager->GetHighlightedList()[i]->DeleteComponent(pManager);

				//move the highlighted components
				pManager->GetOutput()->MoveComponents(pManager->GetHighlightedList(), pManager->GetArr(), selectedItem);
			
				//add the components in the grid in their new positions
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
				{
					pManager->GetHighlightedList()[i]->AddComponent(pManager);
					pManager->GetHighlightedList()[i]->Highlight();
				}
			}
			else
			{
				//if not move then unselect the selected item
				selectedItem->Unhighlight();

				//find the selected item and remove it from the highlighted components vector
				vector<Component*>::iterator it;
				it = find(pManager->GetHighlightedList().begin(), pManager->GetHighlightedList().end(), selectedItem);
				pManager->GetHighlightedList().erase(it);
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
