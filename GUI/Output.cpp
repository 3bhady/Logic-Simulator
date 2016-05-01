#include "Output.h"
#include "..\Utility\Utility.h"
using namespace std;
#include<iostream>
class Gate { };
Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = GREY;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateGrid( );
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateFileToolBar( );
	CreateEditToolBar( );
	CreateStatusBar();		//Create Status bar


}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
void Output::Magnetize(int &x, int &y)
{

	double a, b;
	a = double(x);
	b = double(y);
	x = round( a / 15 ) * 15;
	y = round( b / 15 ) * 15;
	//Magnetizing
	/*if (a - (15 * (a / 15)) < a - (15 * ((a / 15) + 1)))
	{
	x = (15 * (int(a) / 15));
	}
	else x = (15 * ((int(a) / 15) + 1));

	if (b - (15 * (b / 15)) < b - (15 * ((b / 15) + 1)))
	{
	y = (15 * (int(b) / 15));
	}
	else y = (15 * ((int(b) / 15) + 1));	*/
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	//pWind->SetPen(RED,3);
	//pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);

	pWind->DrawImage( "Images\\ToolBars\\Statusbar\\SB1.jpg" , UI.StatusBarStartX , UI.StatusBarStartY);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 200;
	int MsgY = UI.StatusBarHeight - 3;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX+50, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{

	CreateStatusBar( );
/*	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	//pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);		 */
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (design) area
void Output::ClearDrawingArea() const
{
	//pWind->SetPen(RED, 1);
	//pWind->SetBrush(WHITE);
	//pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height  );// UI.StatusBarHeight);
	CreateGrid();
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	pWind->DrawImage( "Images\\ToolBars\\Toolbar\\TB1.jpg" ,UI.ToolBarStartX , UI.ToolBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Toolbar\\TB2.jpg" ,UI.ToolBarTitleStartX , UI.ToolBarTitleStartY );
	/*//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list
	pWind->DrawImage( MenuItemImages[0] , 0*UI.ToolBarItemWidth , 0 , UI.ToolBarItemWidth , UI.ToolBarHeight );
	pWind->DrawImage( MenuItemImages[1] , 1*UI.ToolBarItemWidth , 0 , UI.ToolBarItemWidth , UI.ToolBarHeight );
	pWind->DrawImage( MenuItemImages[ITM_EXIT] , 2*UI.ToolBarItemWidth , 0 , UI.ToolBarItemWidth , UI.ToolBarHeight );
	//Draw menu item one image at a time
//	for(int i=0; i<ITM_DSN_CNT; i++)
	//	pWind->DrawImage(MenuItemImages[i],i*UI.ToolBarItemWidth,0,UI.ToolBarItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	  */

}
void Output::CreateFileToolBar( ) const
{

	pWind->DrawImage( "Images\\ToolBars\\Filebar\\FB1.jpg" , UI.FileBarStartX , UI.FileBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Filebar\\FB2.jpg" , UI.FileBarTitleStartX ,UI.FileBarTitleStartY );

}
void Output::CreateEditToolBar( ) const
{
	pWind->DrawImage( "Images\\ToolBars\\Editbar\\EB2.jpg" , UI.EditBarStartX , UI.EditBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Editbar\\EB3.jpg" , UI.EditBarTitleStartX ,UI.EditBarTitleStartY );
}
void Output::CreateGrid( ) const
{
	for ( int j = 0; j < 700; j += 15 )
	{
		for ( int i = 0; i < 1360; i += 15 )
		{
			pWind->SetPen( SKYBLUE , 1 );
			pWind->DrawCircle( i , j , 1 );
		}
	}
}
window * Output::GetPwind() const
{
	return pWind;
}

void Output::MouseHovering( )const
{
	if ( UI.HiddenToolBar ) return; //TODO m7taga tt3adl w yb2a feha hovering
	string z1 = "Images\\ToolBars\\Toolbar\\toolbar";
	string z2 = ".jpg";
	string z3 = "Images\\ToolBars\\Filebar\\filebar";
	string z4 = "Images\\ToolBars\\Editbar\\editbarDSN";
	string z5 = "Images\\ToolBars\\Editbar\\editbarSIM";
	image i;
	//pWind->StoreImage( i , 0 , 0 , UI.width , UI.height );

	int x , y;
	pWind->GetMouseCoord( x , y );
//	cout << "x: " << x << " y: " << y << endl;

	//if ( y >= 0 && y < UI.ToolBarHeight && x <= UI.ToolBarItemWidth * 17 )
	if(UI.isInToolBar(x,y ) )
	{
		string num = "" , s = "";
		stringstream ss;
		int ClickedItemOrder = (x / UI.ToolBarItemWidth);
		ss << ClickedItemOrder;
		ss >> num;
		s = z1 + num + z2;
		if ( ClickedItemOrder < 17 )
		{
			pWind->DrawImage( s , 0 , 0 );
			switch ( ClickedItemOrder ) {
			case ITM_AND2: {PrintMsg( "Add AND2 Gate" ); break; }
			case ITM_OR2: {PrintMsg( "Add OR2 Gate" ); break; }
			case ITM_EXIT: {PrintMsg( "EXIT" ); break; }
			case ITM_Buff: {PrintMsg( "Add Buffer" ); break; }
			case ITM_INV: {PrintMsg( "ADD Inverter" ); break; }
			case ITM_NAND2: {PrintMsg( "Add NAND2 Gate" ); break; }
			case ITM_NOR2: {PrintMsg( "Add NOR2 Gate " ); break; }
			case ITM_XOR2: {PrintMsg( "Add XOR2 Gate" ); break; }
			case ITM_XNOR2: {PrintMsg( "Add XNOR2 Gate" ); break; }
			case ITM_AND3: {PrintMsg( "Add AND3 Gate" ); break; }
			case ITM_OR3: {PrintMsg( "Add OR3 Gate" ); break; }
			case ITM_NAND3: {PrintMsg("Add NAND3 Gate"); break; }
			case ITM_NOR3: {PrintMsg( "Add NOR3 Gate" ); break; }
			case ITM_XOR3: {PrintMsg( "Add XOR3 Gate" ); break; }
			case ITM_XNOR3: {PrintMsg( "Add XNOR3 Gate" ); break; }
			case ITM_Switch: {PrintMsg( "Add Switch" ); break; }
			case ITM_LED: {PrintMsg( "Add Led" ); break; }
			case ITM_CONNECTION: {PrintMsg( "Add Connection" ); break; }


			//default:PrintMsg( "" );
			}
		}

	}
	else {
		CreateDesignToolBar( );
		//PrintMsg( "" );
	}
	if (UI.isInFileBar(x,y))
	{
		string num = "", s = "";
		stringstream ss;
		int ClickedItemOrder = ((y-UI.FileBarStartY) / UI.FileBarItemHeight);
		ss << ClickedItemOrder;
		ss >> num;
		s = z3 + num + z2;
		if (ClickedItemOrder < 4)
		{
			pWind->DrawImage(s, UI.FileBarStartX, UI.FileBarStartY);
			switch (ClickedItemOrder) {
			case 0: {PrintMsg("New project"); break; }
			case 1: {PrintMsg("Load project"); break; }
			case 2: {PrintMsg("Save project"); break; }
			case 3: {PrintMsg("Exit"); break; }
			//default:PrintMsg("");
			}
		}

	}
	else
	{
		CreateFileToolBar();
		//PrintMsg("");
	}
	if (UI.AppMode == DESIGN)
	{
		if (UI.isInEditBar(x, y))
		{
			string num = "", s = "";
			stringstream ss;
			int ClickedItemOrder = ((y - UI.EditBarStartY) / UI.EditBarItemHeight);
			ss << ClickedItemOrder;
			ss >> num;
			s = z4 + num + z2;
			if (ClickedItemOrder < 4)
			{
				pWind->DrawImage(s, UI.EditBarStartX , UI.EditBarStartY);
				switch (ClickedItemOrder) {
				case 0: {PrintMsg("undo"); break; }
				case 1: {PrintMsg("redo"); break; }
				case 2: {PrintMsg("truth table"); break; }
				case 3: {PrintMsg("Run"); break; }
				//default:PrintMsg("");
				}
			}

		}
		else
		{
			CreateEditToolBar();
			//PrintMsg("");
		}
	}
	else {
		if (UI.isInEditBar(x, y))
		{
			string num = "", s = "";
			stringstream ss;
			int ClickedItemOrder = ((y - UI.EditBarStartY) / UI.EditBarItemHeight);
			ss << ClickedItemOrder;
			ss >> num;
			s = z5 + num + z2;
			if (ClickedItemOrder < 4)
			{
				pWind->DrawImage(s, UI.EditBarStartX - 34, UI.EditBarStartY);
				switch (ClickedItemOrder) {
				case 0: {PrintMsg("undo"); break; }
				case 1: {PrintMsg("redo"); break; }
				case 2: {PrintMsg("truth table"); break; }
				case 3: {PrintMsg("Design mode"); break; }
				//default:PrintMsg("");
				}

			}

		}
		else
		{
			CreateEditToolBar();
			//PrintMsg("");
		}
	}
	if ( !UI.isInEditBar( x , y ) && !UI.isInFileBar( x , y ) && !UI.isInToolBar( x , y ) )
		PrintMsg( "" );
	pWind->UpdateBuffer( );
}

bool Output::FollowMouseAndDraw( GraphicsInfo & r_GfxInfo , DsgnMenuItem gType , Component ** Arr[780] , bool selected )
{
	GraphicsInfo temp = r_GfxInfo;
	image initImage; pWind->StoreImage( initImage , 0 , 0 , UI.width , UI.height );
	  pWind->SetBuffering( true );
//while ( true )
	//{
		 // screenshot of the current image and store it to draw over it
	  pWind->FlushKeyQueue( );
	  char cEscape;	//the character pressed to cancle the addition of the gate
	  bool forbidden = false; // it's true when the user hovers on forbidden area like an existing gate or one of the toolbars
		do {
			
			
			pWind->DrawImage( initImage , 0 , 0 );
			
			pWind->GetMouseCoord( r_GfxInfo.x1 , r_GfxInfo.y1 );
			r_GfxInfo.x1 = r_GfxInfo.x1 - UI.Gate_Width / 2;
			r_GfxInfo.y1 = r_GfxInfo.y1 - UI.Gate_Height / 2;
			Magnetize( r_GfxInfo.x1 , r_GfxInfo.y1 );
			r_GfxInfo.x2 = r_GfxInfo.x1 + UI.Gate_Width;
			r_GfxInfo.y2 = r_GfxInfo.y1 + UI.Gate_Height;

			
			if ( pWind->GetKeyPress( cEscape ) == ESCAPE )
			{
				pWind->DrawImage( initImage , 0 , 0 );
				r_GfxInfo =	temp ;
				pWind->UpdateBuffer( );
				pWind->SetBuffering( false );
				return false;
			}
			//if ( r_GfxInfo.y1 - UI.Gate_Height / 2 < UI.ToolBarHeight )
			//{


			forbidden = false;

			//for ( int i = r_GfxInfo.x1; i < UI.Gate_Width + r_GfxInfo.x1; i++ )
			for ( int i = r_GfxInfo.x1; i < r_GfxInfo.x2; i++ )
			{
				//for ( int j = r_GfxInfo.y1; j < UI.Gate_Height + r_GfxInfo.y1; j++ )
				for ( int j = r_GfxInfo.y1; j < r_GfxInfo.y2; j++ )
				{
					if(i>0&&j>0&&j<700&&i<1390 )
					if ( Arr[j][i] )
						if ( dynamic_cast< Gate* > (Arr[j][i]) )
						{
							forbidden = true; break;
						}
				}
				if ( forbidden )break;
			}
			if ( forbidden )
			{
				PrintMsg( "You can't draw here!" );
				//selected = 1;
				DrawGate( r_GfxInfo , gType ,true);
				//selected = 0;
			}
			else
			{
				DrawGate( r_GfxInfo , gType , selected );
				//forbidden = false;
				//, PrintMsg( "" );
			}

			if ( !UI.HiddenToolBar )CreateDesignToolBar( );
			if ( !UI.HiddenFileBar )CreateFileToolBar( );
			if ( !UI.HiddenEditBar )CreateEditToolBar( );
			/*//}
			//else
			//	DrawGate( r_GfxInfo , gType , selected );
			if ( r_GfxInfo.y1 - UI.Gate_Height / 2 < UI.ToolBarHeight + 1 || r_GfxInfo.y1 + UI.Gate_Height / 2 > UI.height - UI.StatusBarHeight + 3 )
			{
			PrintMsg( "You can't draw here!" );
			}	*/

				 
			if (UI.isForbidden(r_GfxInfo.x2,r_GfxInfo.y2 )
				|| UI.isForbidden( r_GfxInfo.x1 , r_GfxInfo.y1 ) 
				||UI.isForbidden(r_GfxInfo.x1, r_GfxInfo.y2 )
				||UI.isForbidden(r_GfxInfo.x2,r_GfxInfo.y1 )
				||forbidden )
			{
				PrintMsg( "You can't draw here!" );	forbidden = true;
			}
			else
			{
				PrintMsg( "" );  forbidden = false;
			}
			pWind->UpdateBuffer( );


		} while ( pWind->GetMouseClick( r_GfxInfo.x1 , r_GfxInfo.y1 ) == NO_CLICK||forbidden );
		
		
		r_GfxInfo.x1 = r_GfxInfo.x1 - UI.Gate_Width / 2;
		r_GfxInfo.y1 = r_GfxInfo.y1 - UI.Gate_Height / 2;
		Magnetize( r_GfxInfo.x1 , r_GfxInfo.y1 );
		r_GfxInfo.x2 = r_GfxInfo.x1 + UI.Gate_Width;
		r_GfxInfo.y2 = r_GfxInfo.y1 + UI.Gate_Height;
		
		PrintMsg( "" );
	/*	bool forbidden = false;
		for ( int i = r_GfxInfo.x1; i < UI.Gate_Width + r_GfxInfo.x1; i++ )
		{
			for ( int j = r_GfxInfo.y1; j < UI.Gate_Height + r_GfxInfo.y1; j++ )
			{
				if ( Arr[j][i] )
					if ( dynamic_cast< Gate* > (Arr[j][i]) )
					{
						forbidden = true; break;
					}
			}
			if ( forbidden )break;
		}
		if ( !forbidden )
		{
			DrawGate( r_GfxInfo , gType , selected ) , PrintMsg( "" );
			return true;
		}

									  */
	  pWind->SetBuffering( false );
	//}
return true;
		
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)

}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawGate(GraphicsInfo  r_GfxInfo, DsgnMenuItem gate,bool selected)
{
	//Getting the image of the gate

	stringstream sstream;
	string GateNum;
	sstream << int(gate);
	sstream >> GateNum;
	string GateImage = "Images\\Gates\\" + GateNum ;
	if (selected)
		GateImage += "H";
	GateImage += ".jpg";
	/*
	//Getting mouse coordiantes

	//int x, y;
	//pWind->GetMouseCoord(r_GfxInfo.x1, r_GfxInfo.y1);
	*/
	//Magnetize(r_GfxInfo.x1, r_GfxInfo.y1);

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
	//if (selected)	//use image in the highlighted case
	//	GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	//else
	//{
		//Getting mouse coordiantes
		//int x, y;
		//pWind->GetMouseCoord(x, y);
		//Magnetize(x, y);
		//pWind->DrawImage("Images\\Gates\\afr.jpg", x-30,y-15, 60, 30);
		//pWind->DrawImage("Images\\Gates\\LLL.jpg", x + 22.5, y + 22.5, 45, 45);
		//pWind->DrawImage("Images\\Gates\\NAND3.jpg", x, y, UI.Gate_Width, UI.Gate_Height);
		//pWind->DrawImage("Images\\Gates\\NOR2.jpg", x+90, y+90, UI.Gate_Width, UI.Gate_Height);
		//pWind->DrawImage("Images\\Gates\\qqq2.jpg", 758, 577, UI.Gate_Width, UI.Gate_Height);
		//GateImage = "Images\\Gates\\qq.jpg";
	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	//pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo,  bool state, bool selected , string colour)
{
	//Getting the switch image

	string LEDImage = "Images\\LED\\";
	if (state)			  // ON or OFF
		LEDImage += "ON" + colour;
	else LEDImage += "OFF";
	if (selected)		 // Highlighted
		LEDImage += "H";
	LEDImage += ".jpg";

	Magnetize(r_GfxInfo.x1, r_GfxInfo.y1);

	pWind->DrawImage(LEDImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.LED_Width, UI.LED_Height);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo,STATUS status, bool selected, MODE mode)
{
	//Getting the switch image

	string SwitchImage = "Images\\Switch\\";
	if (mode == DESIGN)		  // Design or Simulation mode
		SwitchImage += "DSN";
	else {
		if (status)			  // ON or OFF
			SwitchImage += "ON";
		else SwitchImage += "OFF";
	}
	if (selected)		 // Highlighted
		SwitchImage += "H";
	SwitchImage += ".jpg";


	Magnetize(r_GfxInfo.x1, r_GfxInfo.y1);

	pWind->DrawImage(SwitchImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Switch_Width, UI.Switch_Height);
}

void Output::DrawEditMenu(int x, int y, int selectedItem = 6) const
{
	//Getting the menu image according to the selected item

	string MenuImage="Images\\EDIT MENU\\";
	stringstream sstream;
	if (selectedItem < 6)
	{
		string Item;
		sstream << selectedItem;
		sstream >> Item;
		MenuImage += Item;
	}
	else MenuImage += "EDIT MENU";
	MenuImage += ".jpg";

	pWind->DrawImage(MenuImage, x, y, UI.EditMenu_Width, UI.EditMenu_Height);
}

void Output::DeleteGate( GraphicsInfo GfxInfo )
{
	pWind->DrawImage( "Images\\Gates\\empty.jpg" , GfxInfo.x1 , GfxInfo.y1 );
}

//TODO: Add similar functions to draw all components


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
	
}


Output::~Output()
{
	delete pWind;
}


