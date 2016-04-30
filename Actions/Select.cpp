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
	Component * selected = pManager->GetArr( )[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1];
	
	if (selected)
	{
		GraphicsInfo &GfxInfo = selected->get_GraphicInfo();
		selected->ChangeState();
		

	//todo put parameters to indecate the type of the gate to send it to follow mouse and draw 
		if ( pManager->GetInput( )->DetectChange( ) )

		{
			selected->DeleteComponent( pManager );
			if ( pManager->GetOutput( )->FollowMouseAndDraw( GfxInfo , ITM_AND2 , pManager->GetArr( ) , true ) )
			{
				selected->get_GraphicInfo( ) = GfxInfo;
				selected->AddComponent( pManager );
			}

			
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
