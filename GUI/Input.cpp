#include "Output.h"
#include<iostream>
using namespace std;
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pOut)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar

	return NULL;
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
		if ( abs( a - x ) > 30 || abs( b - y ) > 30 )
		{
			return true;
		}
		if ( clock( )-t >= 150 )
			return false;
	}	
	return false;
}

buttonstate Input::GetButtonState( const button btMouse , int & iX , int & iY )
{
	return pWind->GetButtonState( btMouse , iX , iY );
}



//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction( ApplicationManager * pApp, bool selected )const
{
	char z;
	int x = 0, y = 0;
	Component*** Arr = pApp->GetArr();
	//pWind->WaitMouseClick(x,y); //for testing only
	char HotKey;

	clicktype cType= pWind->GetMouseClick( x , y );
	keytype kType =pWind->GetKeyPress( HotKey );
	//Get the coordinates of the user click
	if  (cType== NO_CLICK&&kType==NO_KEYPRESS)
		return DSN_TOOL;
	


	UI.u_GfxInfo.x1 = x;
	UI.u_GfxInfo.y1 = y;
	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (UI.AppMode == DESIGN)	//application is in design mode
		{
			if ( kType == ASCII )
			{
				switch ( HotKey )
				{
				case 'c':
					return COPY;
				case 'x':
					return CUT;
				case 'v':
					return PASTE;

				default:
					break;
				}
			}
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < UI.ToolBarHeight)
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



Input::~Input()
{

}
