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
	vector<Component*> highlighlted;
	if ( !ReadActionParameters( "" ) )
	{
		for ( int i = 0; i < highlighlted.size( ); i++ )
			highlighlted[i]->Unhighlight( );
		return;
	}
	
}

void AreaSelect::Undo( )
{
}

void AreaSelect::Redo( )
{
}
