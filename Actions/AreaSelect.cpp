#include "AreaSelect.h"



AreaSelect::AreaSelect(ApplicationManager* pApp):Action(pApp )
{

}


AreaSelect::~AreaSelect( )
{

}

bool AreaSelect::ReadActionParameters( string s )
{

	if ( pManager->GetInput( )->DetectChange( ) )		  //if the mouse moved far away from the starting point then the user intends to do an Area select
		return true;
	else
		return false;
}


void AreaSelect::Execute()
{
	for (int i = 0; i<pManager->GetCompList().size(); i++)
	{
		pManager->GetCompList()[i]->Unhighlight();
	}

	if (!ReadActionParameters(""))
	{
		return;
	}
	int a, b;
	while (pManager->GetOutput()->GetPwind()->GetButtonState(LEFT_BUTTON, a, b) == NO_CLICK)
	{
		pManager->GetOutput()->GetPwind()->SetBuffering(true);
		int x, y;
		for (int i = 0; i < pManager->GetCompList().size(); i++)
		{
			pManager->GetCompList()[i]->Unhighlight();
		}
		pManager->GetOutput()->CreateGrid();
		pManager->GetOutput()->CreateToolBars();
		pManager->GetOutput()->DrawRect(x, y);
		int j = x < UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		int sj = x >= UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		int i = y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		int si = y >= UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;

		for (j; j <= sj; j += 15)
		{
			for (i = y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1; i <= si; i += 15)
			{
				if (pManager->GetArr()[i][j])
					pManager->GetArr()[i][j]->Highlight();
			}
		}
		pManager->UpdateInterface();
		pManager->GetOutput()->CreateToolBars();
		pManager->GetOutput()->GetPwind()->UpdateBuffer();
	}
	pManager->GetOutput()->GetPwind()->SetBuffering(false);
}

void AreaSelect::Undo( )
{
}

void AreaSelect::Redo( )
{
}
