#include "Output.h"
#include<iostream>

using namespace std;
 class LED{ };
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

Input::~Input()
{

}

clicktype Input::GetPointClicked(int &x, int &y)
{
	return pWind->GetMouseClick(x, y);	//Wait for mouse click
}

keytype Input::GetKeyPressed( )
{
	char C;
	
	return pWind->GetKeyPress( C );
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
		//cout << kvInput << endl;
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
ActionType Input::GetUserAction(ApplicationManager * pApp)const
{
	int x = 0, y = 0;	//User click coordinates	
	char HotKey;		//Key clicked by the user

	//clicktype cType=pWind->WaitMouseClick(x,y); //for testing only

	//Get user click and key pressed
	clicktype cType = pWind->GetMouseClick(x, y);

	keytype kType = pWind->GetKeyPress(HotKey);
	//Get the coordinates of the user click
	//if (cType == NO_CLICK && kType == NO_KEYPRESS)
	//	return DSN_TOOL;

	//Save the user left click coordinates
	UI.u_GfxInfo.x1 = x;
	UI.u_GfxInfo.y1 = y;

	//Save the user right click coordinates if RIGHTCLICK is pressed
	if (cType == RIGHT_CLICK)
	{
		UI.EditMenuStartY = y;
		UI.EditMenuStartX = x;
	}

	//if EDIT MODE
	if (UI.AppMode == EDIT_MODE)
	{
		//if LEFTCLICK PRESSED
		if (cType == LEFT_CLICK)
		{
			//if Clicked in Editmenu return the item selected in the menu
			if (UI.isInEditMenu(x, y))
			{
				int selecteditem = ((y - UI.EditMenuStartY) / UI.EditMenuItemHeight);
				switch (selecteditem)
				{
				case 0: return EDIT_Label;
				case 1: return COPY;
				case 2: return CUT;
				case 3: return PASTE;
				case 4: return DEL;
				case 5: return SELECT;
				}
			}
			return SELECT;
		}
	}

	//if DESIGN MODE
	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//User pressed hotkey
		if (kType == ASCII || kType == FUNCTION)
		{
			switch (HotKey)
			{
			case 'c':
				return COPY;
			case 'x':
				return CUT;
			case 'v':
				return PASTE;
			case (-48) :
				return 	DEL;
				// ctrl is -17
			default:
				break;
			}
		}

		//If user clicks on Toolbar while it's not hidden
		if (UI.isInToolBar(x, y) && !UI.HiddenToolBar)
		{
			//Check which Menu item was clicked
			int ClickedItemOrder = (x / UI.ToolBarItemWidth);

			if (ClickedItemOrder <= 13)
				return (ActionType)((int)ClickedItemOrder);
			switch (ClickedItemOrder)
			{
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
			default: return DSN_TOOL;	//A click on empty place in design toolbar
			}
		}

		//User clicks on editbar while it's not hidden
		if (UI.isInEditBar(x, y) && !UI.HiddenEditBar)
		{
			int ClickedItemOrder = ((y - UI.EditBarStartY) / UI.EditBarItemHeight);
			switch (ClickedItemOrder)
			{
			case 0: return UNDO;
			case 1: return REDO;
			case 2: return Create_TruthTable;
			case 3: return SIM_MODE;
			default:	break;
			}
		}
	}

	//User clicks on filebar while it's not hidden
	if (UI.isInFileBar(x, y) && !UI.HiddenFileBar)
	{
		int ClickedItemOrder = ((y - UI.FileBarStartY) / UI.FileBarItemHeight);
		switch (ClickedItemOrder)
		{
		case 0: {return NEW; break; }
		case 1: {return LOAD; break; }
		case 2: {return SAVE; break; }
		case 3: {return EXIT; break; }
		default:
			break;
		}
	}

	//if SIMULATION MODE
	if (UI.AppMode == SIMULATION)
	{
		//if Switch clicked, toggle its state
		if (pApp->GetComponent(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1))
			if (pApp->GetComponent(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1)->getType() == Switch_)
				return Change_Switch;

		//User clicks on editbar
		if (UI.isInEditBar(x, y) && !UI.HiddenEditBar)
		{
			int ClickedItemOrder = ((y - UI.EditBarStartY) / UI.EditBarItemHeight);
			switch (ClickedItemOrder)
			{
			case 2: return Create_TruthTable;
			case 3: return DSN_MODE;
			default:break;
			}
		}
		return SIM_MODE;
	}

	//if RIGHTCLICK PRESSED
	if (cType == RIGHT_CLICK)
	{
		//check if click not forbidden return edit menu action
		if (!UI.isForbidden(x, y)
			|| !UI.isForbidden(x + UI.EditMenuItemWidth, y)
			|| !UI.isForbidden(x, y + UI.EditMenuItemHeight)
			|| !UI.isForbidden(x + UI.EditMenuItemWidth, y + UI.EditMenuItemHeight))
			return EDIT_MENU;
		return SELECT;
	}

	//if LEFTCLICK PRESSED
	if (cType == LEFT_CLICK)
	{
		//User clicks on a bar title, toggle the status of this bar
		if (UI.isInToolBarTitle(x, y) 
			|| UI.isInFileBarTitle(x, y)
			|| UI.isInEditBarTitle(x, y))
			return TOGGLE_BARS;
	}

	//User clicks on design area
	if (!UI.isForbidden(x, y))
	{
		if ( pApp->GetComponent( x , y ) )
		{
			pair<int , int> ExactPin = pApp->GetComponent( x , y )->GetOutputPinCoordinates( );
		//	if ( !dynamic_cast< LED* >(pApp->GetComponent( x , y )) &&
			if(  ExactPin.first - x  <= 10&& ExactPin.first - x >0
				&& abs( ExactPin.second - y ) <= 10 )
					return ADD_CONNECTION;

			else
			return SELECT;
		}
		else
			return AREASELECT;
	}

	//User clicks on the status bar
	if (UI.isInStatusBar(x, y))
		return STATUS_BAR;
}

bool Input::close()
{
	char HotKey;
	keytype kType = pWind->GetKeyPress(HotKey); 
	if (kType == ESCAPE)
		return true;
	return false;
}
