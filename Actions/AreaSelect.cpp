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

void AreaSelect::Execute( )
{
	
	vector<Component*> HighlightedVec;
	for ( int i = 0; i<pManager->GetCompList( ).size( ); i++ )
	{
		pManager->GetCompList( )[i]->Unhighlight( );
	}
	
		for ( int i = 0; i < HighlightedVec.size( ); i++ )
			HighlightedVec[i]->Unhighlight( );
	if ( !ReadActionParameters( "" ) )
	{
		return;
	}	
	int a , b;
	while ( pManager->GetOutput()->GetPwind()->GetButtonState(LEFT_BUTTON,a,b)==NO_CLICK)
	{
		int x , y;
		pManager->GetOutput( )->CreateGrid( );
		pManager->GetOutput( )->CreateToolBars( );
		pManager->GetOutput( )->DrawRect(x,y);
		int j = x < UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		int sj= x >= UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		int i = y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		int si = y >= UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		for ( i; i <= si; i+=15 )
		{
			for ( j; j <= sj; j+=15 )
			{
				if ( pManager->GetArr( )[i][j] )
					pManager->GetArr( )[i][j]->Highlight( );
			}
		}
		pManager->UpdateInterface( );
		pManager->GetOutput( )->CreateToolBars( );
		for ( int i = 0; i<pManager->GetCompList( ).size( ); i++ )
		{
			pManager->GetCompList( )[i]->Unhighlight( );
		}

	}
	
}

void AreaSelect::Undo( )
{
}

void AreaSelect::Redo( )
{
}
