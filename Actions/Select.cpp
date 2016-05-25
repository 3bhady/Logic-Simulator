#include "Select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

bool Select::ReadActionParameters()
{
	return true;
}

void Select::Execute()
{
	if ( UI.AppMode == EDIT_MODE )
	{
		pManager->GetOutput( )->CloseEditMenu(pManager);
		
	}

	Component * selectedItem = pManager->GetComponent(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1);	//the selected item
	
	if ( selectedItem )					   //if the clicked area doesn't point to NULL
	{	
		GFXInfo = selectedItem->get_GraphicInfo();		//Save the graphics info
		if ( !selectedItem->isSelected( ) )			//highlight the item if the item is not already highlighted
		{
			
			pManager->HighlightComponent(selectedItem);
			return;
		}
			//GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component

			if (pManager->GetInput()->DetectChange())		//Move 
			{

				Move = true;

				//delete the components from the 2D array and draw an empty block over the gate
				for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
					InitialPositions.push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType())),
					pManager->GetHighlightedComponent(i)->EraseComponent(pManager);
					

				//move the highlighted components
				pManager->GetOutput()->MoveComponents(pManager, selectedItem);
			
				//add the components in the grid in their new positions & add them to the moved components list of the action 
				for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
				{
					pManager->GetHighlightedComponent(i)->AddComponent(pManager);
					pManager->GetHighlightedComponent(i)->Highlight();
					FinalPositions.push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
				}
			}
			else
			{
				//if not move then unselect the selected item and remove it from the highlighted components vector
				pManager->UnhighlightComponent(selectedItem);

			}

	}
}

void Select::undo()
{
	if (!Move)
	{
		Component * pC = pManager->GetComponent(GFXInfo.x1, GFXInfo.y1);
		if (!pC->isSelected())
		{
			
			pManager->HighlightComponent(pC);
		}
		else {
	
			pManager->UnhighlightComponent(pC);
		}
	}
	else {
		for (unsigned int i = 0; i < FinalPositions.size(); i++)
		{
			Component* pG = pManager->GetComponent(FinalPositions[i].first.x1, FinalPositions[i].first.y1);
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = InitialPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
}

void Select::redo()
{
	if (!Move)
	{
		Component * pC = pManager->GetComponent(GFXInfo.x1, GFXInfo.y1);
		if (!pC->isSelected())
		{
			pManager->HighlightComponent(pC);
	
		}
		else
		{
			pManager->UnhighlightComponent(pC);
		
		}
	}
	else {
		for (unsigned int i = 0; i < InitialPositions.size(); i++)
		{
			Component* pG = pManager->GetComponent(InitialPositions[i].first.x1, InitialPositions[i].first.y1);
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = FinalPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
}

Select::~Select()
{
}
