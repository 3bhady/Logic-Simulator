#include "AreaSelect.h"
#include <iostream>
using namespace std;

AreaSelect::AreaSelect(ApplicationManager* pApp):Action(pApp )
{

}


AreaSelect::~AreaSelect( )
{

}

bool AreaSelect::ReadActionParameters( string s )
{

	if ( pManager->GetInput( )->DetectChange( ) )	  //if the mouse moved far away from the starting point then the user intends to do an Area select
		return true;
	else
		return false;
}

void AreaSelect::Execute()
{
	//this for loop is to unhighlight every component because either the user intended to click on an empty area to unhighlight
	//or the user intended to create a rectangle to do an AreaSelect and in either cases it's required to unhighlight every component

	for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
	{
		pManager->GetHighlightedList()[i]->Unhighlight();
		//HighlightedComponentsGfx.push_back(pManager->GetHighlightedList()[i]->get_GraphicInfo());
		InitialHighlightedCompGfx.push_back(pManager->GetHighlightedList()[i]->get_GraphicInfo());
	}
	pManager->GetHighlightedList().clear();
	
	//this loop is to check if the user wanted to draw a rect or just a simple click on an empty area to unselect every component

	if ( !ReadActionParameters( "" ) )
		return;

	int x , y;
	int j, sj, i, si;
	while ( pManager->GetInput()->GetButtonState( LEFT_BUTTON , x , y ) == NO_CLICK )  //exit if the user clicks anywhere
	{
		pManager->GetOutput( )->SetBuffering( true );

		//unselect every component in highlighted component list
		for ( unsigned int i = 0; i < pManager->GetHighlightedList().size( ); i++ )
		{
			pManager->GetHighlightedList()[i]->Unhighlight();
		}  			pManager->GetHighlightedList().clear();
		HighlightedComponentsGfx.clear();
		pManager->GetOutput( )->CreateGrid( );		//redraw the grid
		pManager->GetOutput( )->CreateToolBars( );	//recreate the toolbars
		pManager->GetOutput( )->DrawRect( x , y );	//draw the rectangle
		

		//the following conditions are to set the parameters of the rectangle to check for the selected gates
		j = x < UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		sj = x >= UI.u_GfxInfo.x1 ? x : UI.u_GfxInfo.x1;
		i = y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		si = y >= UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1;
		
		//this loop is for highlighting the components which lay within the drawn rectangle
		for ( j; j <= sj; j += 15 )
		{
			for ( i= y < UI.u_GfxInfo.y1 ? y : UI.u_GfxInfo.y1; i <= si; i += 15 )
			{
				if (pManager->GetArr()[i][j] && !(pManager->GetArr()[i][j]->isSelected()))
				{
					pManager->GetArr()[i][j]->Highlight();		// Highlight the component
					pManager->GetHighlightedList().push_back(pManager->GetArr()[i][j]);		//push the component in the highlighted comp list
					HighlightedComponentsGfx.push_back(pManager->GetArr()[i][j]->get_GraphicInfo());
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
	pManager->GetOutput( )->FlushMouseQueue( );		//to flush the mouse queue so that the application can work right
	pManager->GetOutput( )->SetBuffering( false );
}
void AreaSelect::undo( )
{
	for (unsigned int i = 0; i < InitialHighlightedCompGfx.size(); i++)
		pManager->GetArr()[InitialHighlightedCompGfx[i].y1][InitialHighlightedCompGfx[i].x1]->Highlight();
	for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
		pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Unhighlight();
	/*
	if (unselect)
	{
		for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
			pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Highlight();
	}
	else {
		//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);		//Draw the stored image before this action

		for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)		//Unhighlight the highlighted components by this action
			pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Unhighlight();
	}
	*/
}

void AreaSelect::redo( )
{
	for (int i = 0; i < InitialHighlightedCompGfx.size(); i++)
		pManager->GetArr()[InitialHighlightedCompGfx[i].y1][InitialHighlightedCompGfx[i].x1]->Unhighlight();
	for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
		pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Highlight();
	/*
	if (unselect)
	{
		for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)
			pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Unhighlight();
	}
	else {
		for (unsigned int i = 0; i < HighlightedComponentsGfx.size(); i++)		//Highlight the highlighted components by this action
			pManager->GetArr()[HighlightedComponentsGfx[i].y1][HighlightedComponentsGfx[i].x1]->Highlight();
	}
	*/
}
