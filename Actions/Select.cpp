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
	Component * selectedItem = pManager->GetArr( )[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1];	//the selected item
	
	if ( selectedItem )					   //if the clicked area doesn't point to NULL
	{	
		GFXInfo = selectedItem->get_GraphicInfo();		//Save the graphics info
		if ( !selectedItem->isSelected( ) )			//highlight the item if the item is not already highlighted
		{
			selectedItem->Highlight( );
			pManager->GetHighlightedList().push_back(selectedItem);		//push it in the highlighted comp list
			return;
		}
			//GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component

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

				Move = true;

				//delete the components from the 2D array and draw an empty block over the gate
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
					InitialPositions.push_back(make_pair(pManager->GetHighlightedList()[i]->get_GraphicInfo(), pManager->GetHighlightedList()[i]->getType())),
					pManager->GetHighlightedList()[i]->EraseComponent(pManager);
					

				//move the highlighted components
				pManager->GetOutput()->MoveComponents(pManager, selectedItem);
			
				//add the components in the grid in their new positions & add them to the moved components list of the action 
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
				{
					pManager->GetHighlightedList()[i]->AddComponent(pManager);
					pManager->GetHighlightedList()[i]->Highlight();
					FinalPositions.push_back(make_pair(pManager->GetHighlightedList()[i]->get_GraphicInfo(), pManager->GetHighlightedList()[i]->getType()));
				}
			}
			else
			{
				//if not move then unselect the selected item
				selectedItem->Unhighlight();

				//find the selected item and remove it from the highlighted components vector
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
				{
					if (pManager->GetHighlightedList()[i] == selectedItem)
						pManager->GetHighlightedList().erase(pManager->GetHighlightedList().begin() + i);
				}
			}
	}
}

void Select::undo()
{
	if (!Move)
	{
		Component * pC = pManager->GetArr()[GFXInfo.y1][GFXInfo.x1];
		if (!pC->isSelected())
		{
			pC->Highlight();	
			pManager->GetHighlightedList().push_back(pC);
		}
		else {
			pC->Unhighlight();
			for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
			{
				if (pManager->GetHighlightedList()[i] == pC)
					pManager->GetHighlightedList().erase(pManager->GetHighlightedList().begin() + i);
			}
		}
	}
	else {
		for (unsigned int i = 0; i < FinalPositions.size(); i++)
		{
			Component* pG = pManager->GetArr()[FinalPositions[i].first.y1][FinalPositions[i].first.x1];
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = InitialPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void Select::redo()
{
	if (!Move)
	{
		Component * pC = pManager->GetArr()[GFXInfo.y1][GFXInfo.x1];
		if (!pC->isSelected())
		{
			pC->Highlight();
			pManager->GetHighlightedList().push_back(pC);
		}
		else
		{
			pC->Unhighlight();
			for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
			{
				if (pManager->GetHighlightedList()[i] == pC)
					pManager->GetHighlightedList().erase(pManager->GetHighlightedList().begin() + i);
			}
		}
	}
	else {
		for (unsigned int i = 0; i < InitialPositions.size(); i++)
		{
			Component* pG= pManager->GetArr()[InitialPositions[i].first.y1][InitialPositions[i].first.x1];
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = FinalPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
}

Select::~Select()
{
}
