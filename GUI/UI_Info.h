#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	bool ToolBarHidden = false;
	
	 const int	width = 1360, height = 700,	//Window width and height
						wx = 15, wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,		//Status bar height
						StatusBarWidth = 1360,		//Status bar Width
						ToolBarHeight = 67,			//Tool bar height
						ToolBarWidth = 1300,		//Tool bar width
						ToolBarTitleHeight = 33,	//Tool bar title height
						ToolBarTitleWidth = 264,	//Tool bar title width
						EditBarHeight = 320,		//Edit bar height
						EditBarWidth = 66,			//Edit bar width
						EditBarTitleHeight = 100,	//Edit bar title height
						EditBarTitleWidth = 34,		//Edit bar title width
						FileBarHeight = 320,		//File bar height
						FileBarTitleHeight = 100,	//File bar title height
						FileBarTitleWidth = 34,		//File bar title width
						FileBarWidth = 66,			//File bar Width
						ToolBarItemWidth = 77,		//Width  of each item in toolbar 
						EditbarItemHeight = 80,		//Height of each item in editbar 
						FilebarItemHeight = 80,		//Height of each item in filebar
						EditmenuItemHeight = 26;	//Height of each item in editmenu

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	Gate_Width = 75,		// Gate Image default width
						Gate_Height = 60,		// Gate Image default height
						Switch_Width = 60,		// Switch Image default width
						Switch_Height = 30,		// Switch Image default height
						LED_Width = 45,			// LED Image default width
						LED_Height = 45,		// LED Image default height
						EditMenu_Width = 102,	// EditMenu Image default width
						EditMenu_Height = 161;	// EditMenu Image default height
	
}UI;	//create a single global object UI

#endif