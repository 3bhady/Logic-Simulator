#include "Cut.h"



Cut::Cut(ApplicationManager* pApp):Action(pApp )
{

}


Cut::~Cut( )
{
}

bool Cut::ReadActionParameters( string s )
{
	int size = pManager->GetCompList( ).size( );
	bool selected = false; //it's true if at least there is one selected item to be copied
	for ( int i = 0; i < size; i++ )
		if ( pManager->GetCompList( )[i]->isSelected( ) )
		{
			selected = true; pManager->GetClipboard( ).clear( );  break;
		}
	return selected;
}

void Cut::Execute( )
{
	if ( !ReadActionParameters( "" ) )
		return;
	pManager->GetHighlightedList( ).clear( );
	for ( int i = 0; i <pManager->GetCompList( ).size( ); i++ )
		if ( pManager->GetCompList( )[i]->isSelected( ) )
		{
			
			pManager->GetClipboard( ).push_back( make_pair( pManager->GetCompList( )[i]->get_GraphicInfo( ) , pManager->GetCompList( )[i]->getType( ) ) );
			pManager->GetCompList( )[i]->DeleteComponent( pManager );
			delete pManager->GetCompList( )[i];
			pManager->GetCompList( ).erase( pManager->GetCompList( ).begin() + i );
			i--;
		}
}

void Cut::Undo( )
{
}

void Cut::Redo( )
{
}
