//#include "Input.h"
#include "Output.h"

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



//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	
	//pWind->WaitMouseClick(x,y); //for testing only
	pWind->GetMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (UI.AppMode == DESIGN)	//application is in design mode
		{
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < UI.ToolBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolBarItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_AND2: return ADD_AND_GATE_2;
				case ITM_OR2: return ADD_OR_GATE_2;
				case ITM_EXIT: return EXIT;
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
				case ITM_XNOR3: return ADD_XNOR_GATE_3;
				case ITM_Switch: return ADD_Switch;
				case ITM_LED: return ADD_LED;
				case ITM_CONNECTION: return ADD_CONNECTION;
				//case ITM_ADD_Label: return ADD_Label;
				case ITM_EDIT_Label: return EDIT_Label;
				case ITM_SELECT: return SELECT;
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

			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				return SELECT;	//user want to select/unselect a statement in the flowchart
			}

			//[3] User clicks on the status bar
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
