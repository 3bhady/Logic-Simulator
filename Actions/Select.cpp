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
		selectedItem->Highlight( );				   //highlighting the component
		return;
	}
		GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component
		//selectedItem->ChangeState();
		

	//todo put parameters to indicate the type of the gate to send it to follow mouse and draw 
		if ( pManager->GetInput( )->DetectChange( ) )

		{
			selectedItem->DeleteComponent( pManager );			 //delete the component from the 2D array and draw an empty block over the gate
			pManager->GetOutput( )->FollowMouseAndDraw( GfxInfo , ITM_AND2 , pManager->GetArr( ) , true );
			//selectedItem->get_GraphicInfo( ) = GfxInfo;
			selectedItem->AddComponent( pManager );
				
				selectedItem->Highlight( );

			
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
