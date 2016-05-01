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
		//selectedItem->ChangeState();

		//todo put parameters to indicate the type of the gate to send it to follow mouse and draw 

		if (pManager->GetInput()->DetectChange())
		{
			vector<Component*> HighlightedVec;
			for (int i = 0; i<pManager->GetCompList().size(); i++)
			{
				if (pManager->GetCompList()[i]->isSelected())
					HighlightedVec.push_back(pManager->GetCompList()[i]);
			}
			for (int i = 0; i < HighlightedVec.size(); i++)
			{
				HighlightedVec[i]->DeleteComponent(pManager);
				// selectedItem->DeleteComponent(pManager);			 //delete the component from the 2D array and draw an empty block over the gate
			}
			//pManager->GetOutput( )->FollowMouseAndDraw( GfxInfo , AND2_ , pManager->GetArr( ) , true );
			pManager->GetOutput()->MoveComponents(HighlightedVec, pManager->GetArr());
			//selectedItem->get_GraphicInfo( ) = GfxInfo;
			for (int i = 0; i < HighlightedVec.size(); i++)
			{
				//selectedItem->AddComponent(pManager);
				HighlightedVec[i]->AddComponent(pManager);
				HighlightedVec[i]->Highlight();
				//selectedItem->Highlight();
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
