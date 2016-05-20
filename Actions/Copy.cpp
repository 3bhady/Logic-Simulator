#include "Copy.h"

Copy::Copy( ApplicationManager * pApp ):Action(pApp )
{

}


Copy::~Copy( )
{
}

bool Copy::ReadActionParameters()
{
	//int size = pManager->GetCompList( ).size( );
	bool selected = false; //it's true if at least there is one selected item to be copied
	if ( pManager->getHighlightedCompListSize() != 0 )
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
	if ( !ReadActionParameters( ) )
		return;
	//int size = pManager->GetCompList( ).size( );
	int size = pManager->getHighlightedCompListSize();
	//PreviousClipboard = pManager->GetClipboard();
	for (int i = 0; i < size; i++)
		//if ( pManager->GetCompList( )[i]->isSelected( ) )
		//{	
		pManager->GetClipboard().push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
	//	}


}

void Copy::undo( )
{

}

void Copy::redo( )
{
}
