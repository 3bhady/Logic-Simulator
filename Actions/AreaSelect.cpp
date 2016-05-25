#include "AreaSelect.h"
#include <iostream>
using namespace std;

AreaSelect::AreaSelect(ApplicationManager* pApp):Action(pApp )
{

}


AreaSelect::~AreaSelect( )
{

}

bool AreaSelect::ReadActionParameters()
{
	//if the mouse moved far away from the starting point then the user intends to do an Area select
	if ( pManager->GetInput( )->DetectChange( ) )
		return true;

	else return false;
}

void AreaSelect::Execute()
{
	/*this for loop is to unhighlight every component because either the user intended to click on an empty area to unhighlight
	or the user intended to create a rectangle to do an AreaSelect and in either cases it's required to unhighlight every component*/
	for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
		InitialHighlightedCompGfx.push_back(pManager->GetHighlightedList()[i]->get_GraphicInfo());

	pManager->ClearHighlightedCompList();

	if ( !ReadActionParameters( ) )
		return;

	int x , y;
	int j, sj, i, si;
	while ( pManager->GetInput()->GetButtonState( LEFT_BUTTON , x , y ) == NO_CLICK )  //exit if the user clicks anywhere
	{
		pManager->ClearHighlightedCompList();		//clear Highlightcomplist
		HighlightedComponentsGfx.clear();			//clear the list highlighted by this action
		pManager->GetOutput( )->CreateGrid( );		//redraw the grid
		pManager->GetOutput( )->CreateToolBars( );	//recreate the toolbars
		pManager->GetOutput( )->DrawRect( x , y );	//draw the rectangle
		

		//the following conditions are to set the parameters of the rectangle to check for the selected gates
		j = x < UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		sj = x >= UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		i = y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		si = y >= UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		
		//this loop is for highlighting the components which lie within the drawn rectangle
		for ( j; j <= sj; j++ )
		{
			for ( i= y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1; i <= si; i++ )
			{
				if (pManager->GetComponent(j, i) && !(pManager->GetComponent(j, i)->isSelected()))
				{
					pManager->HighlightComponent(pManager->GetComponent(j, i));
					HighlightedComponentsGfx.push_back(pManager->GetComponent(j, i)->get_GraphicInfo());
				}
			}
		}
		pManager->UpdateInterface( );		//to redraw every component after the rect
		pManager->GetOutput( )->CreateToolBars( );		//to draw the toolbars above everything else like the rect
		pManager->GetOutput( )->UpdateBuffer( );	 //to make the operations smooth
	}

	//these functions are done after finishing the selection and they are called to clear the rectangle after selecting
	pManager->GetOutput( )->CreateGrid( );
	pManager->UpdateInterface( );
	pManager->GetOutput( )->CreateToolBars( );
	pManager->GetOutput( )->UpdateBuffer( );
	pManager->GetOutput( )->FlushMouseQueue( );		//Flush the mouse queue after the action
	
}
void AreaSelect::undo( )
{
	pManager->ClearHighlightedCompList();

	//Unhighlight the components highlighted by this action and highlight the components which were highlighted before this action

	for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
		pManager->GetComponent(HighlightedComponentsGfx[i].x1, HighlightedComponentsGfx[i].y1)->Unhighlight();

	for (unsigned int i = 0; i < InitialHighlightedCompGfx.size(); i++)
		pManager->HighlightComponent(pManager->GetComponent(InitialHighlightedCompGfx[i].x1, InitialHighlightedCompGfx[i].y1));
}

void AreaSelect::redo( )
{
	pManager->ClearHighlightedCompList();

	//Highlight the components highlighted by this action and unhighlight the components which were highlighted before this action

	for (unsigned int i = 0; i < InitialHighlightedCompGfx.size(); i++)
		pManager->GetComponent(InitialHighlightedCompGfx[i].x1, InitialHighlightedCompGfx[i].y1)->Unhighlight();

	for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
		pManager->HighlightComponent(pManager->GetComponent(HighlightedComponentsGfx[i].x1, HighlightedComponentsGfx[i].y1));
}
