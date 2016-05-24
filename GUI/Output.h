#pragma once
#include "..\Defs.h"
#include "Input.h"
#include "..\ApplicationManager.h"
#include <sstream>
#include "..\Components\Component.h"
#include <vector>
#include <ctime>

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
	ApplicationManager* AppManger;
public:
	Output(ApplicationManager*);	//Performs the Window Initialization
	~Output();	//destructor

	Input* CreateInput() const;		//creates a pointer to the Input object

	void ChangeTitle(string Title) const;

	/////////////////////////////////////////
	//**Toolbars & Drawing area Functions**//
	/////////////////////////////////////////

	void CreateDesignToolBar() const;	
	void CreateFileToolBar( )const;		
	void CreateEditToolBar( )const;		
	void CreateGrid( )const;			
	void CreateSimulationToolBar() const;
	void CreateStatusBar() const;		
	void CreateToolBars( )const;
	void ClearStatusBar() const;		
	void ClearDrawingArea() const;
	//kero
	//========================================
	void HideDesignToolBar()const;
	void ShowDesignToolBar()const;
	void HideFileToolBar()const;
	void ShowFileToolBar()const;
	void HideEditToolBar()const;
	void ShowEditToolBar()const;
	void CloseEditMenu( ApplicationManager* pManager )const;
	//=============================================
	//window* GetPwind()const;

	void MouseHovering(ApplicationManager*pApp)const;		//Detect the hovering of the mouse and makes changes according to the hover

	bool FollowMouseAndDraw(GraphicsInfo & r_GfxInfo, ComponentType, Component ** Arr[780]);		//Drag & Drop

	void Magnetize(int &x,int &y);		//Gets the nearest dot in the grid


	/////////////////////////
	//**Drawing Functions**//
	/////////////////////////

	void DrawJPEGImage(const image &imgThis, const int iX, const int iY, const int iWidth = -1, const int iHeight = -1);
	void DrawPNGImage( string r_filename, GraphicsInfo GfxInfo );
	void DrawGate(GraphicsInfo  r_GfxInfo, ComponentType gate, bool selected = false, bool forbidden = false);
	void DrawLED(GraphicsInfo r_GfxInfo, bool state, bool selected, bool forbidden = false , string colour = "");
	void DrawSwitch(GraphicsInfo r_GfxInfo,STATUS status, bool forbidden = false, bool selected = false, MODE mode = DESIGN);
	void DrawEditMenu(int x, int y,int selectedItem)const;
	void DrawConnection(GraphicsInfo r_GfxInfo, BFSOut &kol, Component*con, bool selected) const;
	void DrawRect(int& x, int &y);
	void DrawDots(int xStart, int yStart, int xFinish, int yFinish);	//Make an area dotted
	void DeleteGate( GraphicsInfo GfxInfo );		//Draws an empty image on the gate
	void DrawPinStatus(STATUS status, int x,int y);
	/////////////////////////
	//**Window Functions**///
	/////////////////////////

	window* CreateWind(int wd, int h, int x, int y) const;		//Creates user interface window
	bool SetBuffering( const bool bSetting );
	void UpdateBuffer( );
	void FlushMouseQueue( );
	void FlushKeyQueue( );
	

	void PrintMsg(string msg) const;	//Print a message on Status bar
	void StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight);

	bool MoveComponents( ApplicationManager* pApp , Component* selected );	//Move highlighted components with the mouse
	bool PasteComponents( ApplicationManager* pApp );
};
