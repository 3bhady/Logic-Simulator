#pragma once
//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_OR_GATE_3,		//Add 3-input OR gate
	ADD_NAND_GATE_3,	//Add 3-input NAND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_XNOR_GATE_3,	//Add 3-input XNOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	//ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Create_TruthTable,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	AREASELECT,
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	COPY,
	CUT,
	PASTE,

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//undo the last Action preformed
	REDO,		//redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION ,
	MULTISELECT,	   //TODO:: when multiple components are selected individually
	SELECTION,		  //TODO::
	SELECTAREA	// TODO::
	
};

enum ComponentType //The items of the design menu (you should add more items)
{
	AND2_,		// 2-input AND gate
	OR2_,		// 2-input OR gate
	Buff_,		// 1-input Buffer gate
	INV_,		// 1-input Inverter gate
	NAND2_,		// 2-input NAND gate
	NOR2_,		// 2-input NOR gate
	XOR2_,		// 2-input XOR gate
	XNOR2_,		// 2-input XNOR gate
	AND3_,		// 3-input AND gate
	OR3_,		// 3-input OR gate
	NAND3_,		// 3-input NAND gate
	NOR3_,		// 3-input NOR gate
	XOR3_,		// 3-input XOR gate
	XNOR3_,		// 3-input XNOR gate
	Switch_,			// Switch
	LED_,				// LED
	CONNECTION_,		// Wire Connection
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//AND gate item in menu
	ITM_OR2,		//OR gate item in menu
	ITM_Buff,		// 1-input Buffer gate
	ITM_INV,		// 1-input Inverter gate
	ITM_NAND2,		// 2-input NAND gate
	ITM_NOR2,		// 2-input NOR gate
	ITM_XOR2,		// 2-input XOR gate
	ITM_XNOR2,		// 2-input XNOR gate
	ITM_AND3,		// 3-input AND gate
	ITM_OR3,		// 3-input OR gate
	ITM_NAND3,		// 3-input NAND gate
	ITM_NOR3,		// 3-input NOR gate
	ITM_XOR3,		// 3-input XOR gate
	ITM_XNOR3,		// 3-input XNOR gate
	ITM_Switch,			// Switch
	ITM_LED,			// LED
	ITM_CONNECTION,		// Wire Connection
						//ITM_ADD_Label ,			//Add Label to a Component, a Connection
	ITM_EDIT_Label,			//Edit Label of a Component, a Connection

	ITM_SELECT,		//Select a Component, a Connection
	ITM_DEL,		//Delete a Component, a Connection
	ITM_MOVE,		//Move a Component, a Connection

	ITM_SAVE,		//Save the whole Circuit to a file
	ITM_LOAD,		//Load a Circuit from a file

	ITM_UNDO,		//undo the last Action preformed
	ITM_REDO,		//redo the last Action canceled


	ITM_SIM_MODE,	//Switch to Simulatiom mode

	ITM_EXIT,		//Exit item

					//TODO: Add more items names here

	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_SIM,	 //run
	ITM_TRUTH,	//Truth table menu item
	ITM_Create_TruthTable,	//Create Truth Table of the Circuit

	ITM_Change_Switch,		//Change Switch Status in Simulation Mode
							//TODO:Add more items names here
	ITM_DSN_MODE,	//Switch to Design mode
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};						

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5	//Default fan out of 2-input AND gate
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1,y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif
