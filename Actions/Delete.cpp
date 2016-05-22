#include "Delete.h"



Delete::Delete( ApplicationManager *pApp ):Action(pApp )
{

}


Delete::~Delete( )
{

}

bool Delete::ReadActionParameters( )
{
	//check if highlighted list is empty 

	return (pManager->getHighlightedCompListSize()==0);
}

void Delete::Execute( )
{	
	// all highlighted compoents from 2D array
	
	//empty the highlighted list by clear and leave them highlighted

	//remove highlighted elements from component list
	if ( UI.AppMode == EDIT_MODE )
		pManager->GetOutput( )->CloseEditMenu( pManager );
	for ( unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++ )
		pManager->GetHighlightedList( )[i]->DeleteComponent( pManager );

	pManager->ClearHighlightedCompList( );


}

void Delete::undo( )
{
}

void Delete::redo( )
{
}
