#include "Output.h"
#include<iostream>

using namespace std;

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

Input::~Input()
{

}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString( Output *pOut )
{
	pOut->PrintMsg( "Please enter the label" );
	pWind->UpdateBuffer( );
	string label = "";	 //label
	char kvInput;		 //value of input key pressed by user
	keytype ktInput;	 //type of input key
	while ( true )
	{
		ktInput = pWind->WaitKeyPress( kvInput );
		//ktInput = pWind->GetKeyPress( kvInput );
		cout << kvInput << endl;
		switch ( ktInput )
		{
		case ESCAPE:
		{
			label = "";
			pOut->PrintMsg( "" );
			return label;
		}
		case ASCII:
		{
			if ( kvInput == '\r' )			//SPACE
			{
				pOut->PrintMsg( "" );
				return label;

			}
			if (kvInput == '\b')			//BACKSPACE
			{
				if (label.size() != 0)
					label.erase(label.length() - 1);
			}
			else
				label += kvInput;
		}
		}
		pOut->PrintMsg( label );		//Print the label on Status bar
		pWind->UpdateBuffer( );
	}
}

bool Input::DetectChange( )
{
	int x , y;
	pWind->GetMouseCoord( x , y );
	int a , b ;
	clock_t t = clock( );
	//while ( pWind->GetMouseClick( a , b ) == NO_CLICK )
	while(true )
	{
		pWind->GetMouseCoord( a , b );
		if ( abs( a - x ) > 30 || abs( b - y ) > 30 )		//if Coordinates changed > 30 pixels return true
		{
			return true;
		}
		if ( clock( )-t >= 150 )		//if Coordinates didn't change for 150ms return false
			return false;
	}	
	return false;
}

buttonstate Input::GetButtonState( const button btMouse , int & iX , int & iY )
{
	return pWind->GetButtonState( btMouse , iX , iY );
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction( ApplicationManager * pApp )const
{
	int x = 0, y = 0;
	Component*** Arr = pApp->GetArr();
	//clicktype cType=pWind->WaitMouseClick(x,y); //for testing only
	char HotKey;

	clicktype cType= pWind->GetMouseClick( x , y );
	keytype kType =pWind->GetKeyPress( HotKey );
	
	//Get the coordinates of the user click
	if  (cType== NO_CLICK&&kType==NO_KEYPRESS)
		return DSN_TOOL;

	//Save the user click coordinates
	UI.u_GfxInfo.x1 = x;
	UI.u_GfxInfo.y1 = y;

	//if RIGHTCLICK PRESSED Save the coordinates
	if (cType == RIGHT_CLICK)
	{
		UI.EditMenuStartY = y;
		UI.EditMenuStartX = x;
	}

	//if EDITMODE
	if (UI.AppMode == EDIT_MODE)
	{
		//if LEFTCLICK PRESSED
		if (cType == LEFT_CLICK)
		{
			//pWind->GetMouseCoord(x, y);

			//if Clicked in Editmenu return the item selected in the menu
			if (UI.isInEditMenu(x, y))
			{
				int selecteditem = ((y - UI.EditMenuStartY) / UI.EditMenuItemHeight);
				switch (selecteditem)
				{
				case 0: return EDIT_Label;
				case 1: return COPY;
				case 2:return CUT;
				case 3:return PASTE;
				case 4:return DEL;
				case 5:return MOVE;
				}
			}
			return SELECT;
		}
	}

	//if not in SIMULATIONMODE
	if (UI.AppMode != SIMULATION)
	{
		//if RIGHTCLICK PRESSED
		if (cType == RIGHT_CLICK)
		{
			//check if click not forbidden return edit menu action
			if (!UI.isForbidden(x, y)
				|| !UI.isForbidden(x + UI.EditMenuItemWidth, y)
				|| !UI.isForbidden(x, y + UI.EditMenuItemHeight)
				|| !UI.isForbidden(x + UI.EditMenuItemWidth, y + UI.EditMenuItemHeight))
				//if (pApp->GetArr()[y][x])
				return EDIT_MENU;
			return SELECT;
		}
	}

	//if LEFTCLICK PRESSED
	if (cType == LEFT_CLICK)
	{
		//if the click is in a bar toggle the status of this bar
		if (UI.HiddenToolBar&&UI.isInToolBarTitle(x, y))
			return SHOW_DESIGN_B;
		if (!UI.HiddenToolBar && UI.isInToolBarTitle(x, y))
			return HIDE_DESIGN_B;
		if (UI.HiddenFileBar  &&UI.isInFileBarTitle(x, y))
			return SHOW_FILE_B;
		if (!UI.HiddenFileBar && UI.isInFileBarTitle(x, y))
			return HIDE_FILE_B;
		if (!UI.HiddenEditBar&&UI.isInEditBarTitle(x, y))
			return HIDE_EDIT_B;
		if (UI.HiddenEditBar&& UI.isInEditBarTitle(x, y))
			return SHOW_EDIT_B;
	}

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (UI.AppMode == DESIGN)	//application is in design mode
		{
			if ( kType == ASCII||kType==FUNCTION )
			{
				switch ( HotKey )
				{
				case 'c':
					return COPY;
				case 'x':
					return CUT;
				case 'v':
					return PASTE;
				case (2000+'0'):
					return 	DEL;
					// ctrl is 3000
				default:
					break;
				}
			}
			//[1] If user clicks on the Toolbar
			//if (y >= 0 && y < UI.ToolBarHeight)
			if(UI.isInToolBar(x,y ))
			{						
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolBarItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				if ( ClickedItemOrder <= 13 )
				{

				//	pApp->GetOutput()->FollowMouseAndDraw( r_GfxInfo , (DsgnMenuItem)ClickedItemOrder , Arr );
					return (ActionType)((int)ClickedItemOrder);
				}
				switch (ClickedItemOrder)
				{ case ITM_EXIT: return EXIT;
				case ITM_AND2: return ADD_AND_GATE_2;
				case ITM_OR2: return ADD_OR_GATE_2;
				
				case ITM_Buff: return ADD_Buff;
				case ITM_INV: return ADD_INV;
				case ITM_NAND2: return ADD_NAND_GATE_2;
				case ITM_NOR2: return ADD_NOR_GATE_2;
				case ITM_XOR2: return ADD_XOR_GATE_2;
				case ITM_XNOR2: return ADD_XNOR_GATE_2;
				case ITM_AND3: return ADD_AND_GATE_3;
				case ITM_OR3: return ADD_OR_GATE_3;
				case ITM_NAND3: return ADD_AND_GATE_3;
				case ITM_NOR3: return ADD_NOR_GATE_3;
				case ITM_XOR3: return ADD_XOR_GATE_3;  
				case ITM_Switch: return ADD_Switch;
				case ITM_LED: return ADD_LED;
				case ITM_CONNECTION: return ADD_CONNECTION;
				//case ITM_ADD_Label: return ADD_Label;
				case ITM_EDIT_Label: return EDIT_Label;
				//case ITM_SELECT: return SELECT;
				case ITM_DEL: return DEL;
				case ITM_MOVE: return MOVE;
				case ITM_SAVE: return SAVE;
				case ITM_LOAD: return LOAD;
				case ITM_UNDO: return UNDO;
				case ITM_REDO: return REDO;
				case ITM_SIM_MODE: return SIM_MODE;

				default: return DSN_TOOL;	//A click on empty place in design toolbar
				}
			}
if (UI.isInFileBar(x, y))
			{
				int ClickedItemOrder = ((y - UI.FileBarStartY) / UI.FileBarItemHeight);
				switch (ClickedItemOrder)
				{
				case 0: {break; }
				case 1: {return LOAD; break; }
				case 2: {return SAVE; break; }
				case 3: {return EXIT; break; }
				default:
					break;
				}
			}
			if (UI.isInEditBar(x, y))
			{
				int ClickedItemOrder = ((y - UI.EditBarStartY) / UI.EditBarItemHeight);
				switch (ClickedItemOrder)
				{
				case 0: {return UNDO; break; }
				case 1: {return REDO; break; }
				case 2: {return Create_TruthTable; break; }
				case 3: {return SIM_MODE; break; }
				default:
					break;
				}
			}
			//[2] User clicks on the drawing area
			//if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			//{
				//return SELECT;	//user want to select/unselect a statement in the flowchart
			//}

			if ( !UI.isForbidden( x , y ) )
			{
				if ( pApp->GetArr()[y][x] )
					return SELECT;
				else
					return AREASELECT;
			}


			//[3] User clicks on the status bar

			if(UI.isInStatusBar(x,y))
				return STATUS_BAR;
		}
		else	//Application is in Simulation mode
		{
			return SIM_MODE;	//This should be changed after creating the compelete simulation bar
		}
	}
	//TO DO : return when sim mode
	return SIM_MODE;
}

bool Input::close()
{
	
	char HotKey;

	keytype kType = pWind->GetKeyPress(HotKey); 
	if (kType == ESCAPE)
		return true;
	return false;
}
