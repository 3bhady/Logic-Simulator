#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	bool HiddenToolBar = false;
	bool HiddenFileBar = false;
	bool HiddenEditBar = false;

	GraphicsInfo u_GfxInfo;		//User interaction

	const int	width = 1360 , height = 700 ,	//Window width and height
		wx = 15 , wy = 15 ,			//Window starting coordinates
		ToolBarHeight = 67 ,			//Tool bar height
		ToolBarWidth = 1300 ,		//Tool bar width
		ToolBarTitleHeight = 33 ,	//Tool bar title height
		ToolBarTitleWidth = 264 ,	//Tool bar title width
		ToolBarItemWidth = 77 ,		//Width  of each item in toolbar
		ToolBarStartX = 0,
		ToolBarTitleStartX = 0 ,

		StatusBarHeight = 50 ,		//Status bar height
		StatusBarWidth = 1360 ,		//Status bar Width
		StatusBarStartX = 0 ,
		StatusBarStartY = height - StatusBarHeight - 15 ,


		EditBarHeight = 320 ,		//Edit bar height
		EditBarWidth = 66 ,			//Edit bar width
		EditBarTitleHeight = 100 ,	//Edit bar title height
		EditBarTitleWidth = 34 ,		//Edit bar title width
		EditBarItemHeight = 80 ,		//Height of each item in editbar
		EditBarStartY = ToolBarHeight,
		EditBarTitleStartY = EditBarStartY,

		FileBarHeight = 320 ,		//File bar height
		FileBarTitleHeight = 100 ,	//File bar title height
		FileBarTitleWidth = 34 ,		//File bar title width
		FileBarStartY = height - 15 - StatusBarHeight - FileBarHeight,
		FileBarTitleStartY = FileBarStartY + FileBarHeight - FileBarTitleHeight,
		FileBarWidth = 66 ,			//File bar Width
		FileBarItemHeight = 80 ,		//Height of each item in filebar
		EditmenuItemHeight = 26,	//Height of each item in editmenu
	    ConnectionOffset = 5;//the thickness of the drawing line


	int ToolBarStartY = 0,
		ToolBarTitleStartY = ToolBarHeight,
		FileBarStartX = 0,
		FileBarTitleStartX = FileBarWidth,
		EditBarStartX = width - EditBarWidth - 14,
		EditBarTitleStartX = width - EditBarWidth - EditBarTitleWidth - 14;


	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor = GREY;	//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50

	const int	Gate_Width = 75,		// Gate Image default width
		Gate_Height = 50,		// Gate Image default height
		Switch_Width = 60,		// Switch Image default width
		Switch_Height = 30,		// Switch Image default height
		LED_Width = 50,			// LED Image default width
		LED_Height = 50;		// LED Image default height

int		EditMenuStartX,
		EditMenuStartY;
	const int EditMenuItemHeight = 26,	//Height of each item in editmenu
		EditMenuItemWidth = 102,	// EditMenu Image default width
		EditMenuHeight = 161;	// EditMenu Image default height


	/////////////////////////////////
	/////**Checking functions**//////
	/////////////////////////////////

bool isInToolBar( int x , int y )
{
	if (y >= ToolBarStartY && y<ToolBarTitleStartY
		&& x>ToolBarStartX && x <= ToolBarStartX + ToolBarWidth)
			return true;
	return false;
}

bool isInEditMenu(int x, int y)
{
	if (x >= EditMenuStartX&&x < (EditMenuStartX + UI.EditMenuItemWidth))
		if (y >= EditMenuStartY&&y < EditMenuStartY + EditMenuHeight)
			return true;
	return false;
}

bool  isInToolBarTitle( int x , int y )
{
	if (y >= ToolBarTitleStartY && y < ToolBarTitleStartY + ToolBarTitleHeight
		&& x>ToolBarTitleStartX && x < UI.ToolBarTitleWidth)
			return true;
	return false;
}

bool isInStatusBar(int x, int y)
{
	return (y > height - StatusBarHeight - 20);
}

bool isInFileBar(int x, int y)
{
	if (x > FileBarStartX && x < ToolBarItemWidth
		&&	y > FileBarStartY && y <= FileBarStartY + FileBarHeight)
			return true;
	return false;
}

bool isInFileBarTitle(int x, int y)
{
	if (x > FileBarTitleStartX && x < FileBarTitleStartX + FileBarTitleWidth
		&&	y < FileBarTitleStartY + FileBarTitleHeight && y > UI.FileBarTitleStartY)
			return true;
	return false;
}

bool isInEditBar(int x, int y)
{
	if (x > EditBarStartX && x < UI.width-15
		&&	y < EditBarHeight + EditBarStartY && y > EditBarStartY)
			return true;
	return false;
}

bool isInEditBarTitle(int x, int y)
{
	if (x > EditBarTitleStartX && x < EditBarStartX
		&&	y > EditBarTitleStartY && y < EditBarTitleHeight + EditBarTitleStartY)
			return true;
	return false;
}

bool isInBar(int x, int y)
{
	return (isInStatusBar(x, y) || isInEditBar(x, y) || isInFileBar(x, y));
}

bool isForbidden(int x,int y)
{
	return (isInEditBar(x, y) || isInEditBarTitle(x, y) ||
		isInFileBar(x, y) || isInFileBarTitle(x, y) ||
		isInToolBar(x, y) || isInToolBarTitle(x, y) ||
		isInStatusBar(x, y) || x>UI.width - UI.wx || x < 15 );
}

}UI;	//create a single global object UI
