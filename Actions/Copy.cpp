#include "Copy.h"

Copy::Copy( ApplicationManager * pApp ):Action(pApp )
{

}


Copy::~Copy( )
{
}

bool Copy::ReadActionParameters( string s )
{
	int size = pManager->GetCompList( ).size( );
	bool selected = false; //it's true if at least there is one selected item to be copied
	if ( pManager->GetHighlightedList( ).size( ) != 0 )
	{
		selected = true; pManager->GetClipboard( ).clear( );
	}

	/*for ( int i = 0; i < size;i++)
		if ( pManager->GetCompList( )[i]->isSelected( ) )
		{
			selected = true; pManager->GetClipboard( ).clear( );  break;
		}		 */
	return selected;
}

void Copy::Execute( )
{	  
	if ( !ReadActionParameters( "" ) )
		return;
	//int size = pManager->GetCompList( ).size( );
	int size = pManager->GetHighlightedList( ).size( );
	//PreviousClipboard = pManager->GetClipboard();
	for ( int i = 0; i < size; i++ )
		//if ( pManager->GetCompList( )[i]->isSelected( ) )
		//{	
	pManager->GetClipboard( ).push_back( make_pair( pManager->GetHighlightedList()[i]->get_GraphicInfo( ) , pManager->GetHighlightedList()[i]->getType( ) ) );
	//	}


}

void Copy::undo( )
{

}

void Copy::redo( )
{
}
