#pragma once
#include "..\Defs.h"
#include "Input.h"
#include "..\ApplicationManager.h"
#include <sstream>
#include "..\Components\Component.h"

//class Component;
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateFileToolBar( )const;
	void CreateEditToolBar( )const;
	void CreateGrid( )const;
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	window* GetPwind()const;

	void MouseHovering( )const;
	bool FollowMouseAndDraw(GraphicsInfo & r_GfxInfo, DsgnMenuItem gType, Component ** Arr[780], bool selected = false, int xOffset = 0, int yOffset = 0);

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	void Magnetize(int &x,int &y);

	void DrawGate(GraphicsInfo  r_GfxInfo, DsgnMenuItem gate,bool selected = false);
	void DrawLED(GraphicsInfo r_GfxInfo, bool state , bool selected,string colour);
	void DrawSwitch(GraphicsInfo r_GfxInfo,STATUS status, bool selected = false, MODE mode = DESIGN);
	void DrawEditMenu(int x, int y,int selectedItem)const;
	void DeleteGate( GraphicsInfo GfxInfo );

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc

	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;

	void PrintMsg(string msg) const;	//Print a message on Status bar


	~Output();
};
