#include "Copy.h"

Copy::Copy( ApplicationManager * pApp ):Action(pApp )
{

}


Copy::~Copy( )
{
}

bool Copy::ReadActionParameters()
{
	bool selected = false; //it's true if at least there is one selected item to be copied

	if ( pManager->getHighlightedCompListSize() != 0 )
		selected = true, pManager->GetClipboard( ).clear( );

	return selected;
}

void Copy::Execute( )
{
	if ( UI.AppMode == EDIT_MODE )
		pManager->GetOutput( )->CloseEditMenu( pManager );

	if ( !ReadActionParameters( ) )
		return;

	int size = pManager->getHighlightedCompListSize();

	for (int i = 0; i < size; i++)
		pManager->GetClipboard().push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
}

void Copy::undo( )
{

}

void Copy::redo( )
{
}
