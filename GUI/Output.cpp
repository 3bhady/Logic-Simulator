#include "Output.h"
#include<iostream>
#include "..\Utility\Utility.h"
#include "..\Components\Connection.h"

using namespace std;

class Gate { };
Output::Output(ApplicationManager* x)
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
	CreateDesignToolBar();	
	CreateFileToolBar( );
	CreateEditToolBar( );
	CreateStatusBar();		

	AppManger = x;
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

//////////////////////////////////////////////////////////////////////////////////

void Output::Magnetize(int &x, int &y)
{

	double a, b;
	a = double(x);
	b = double(y);
	x = (int)(round( a / 15 ) * 15);
	y = (int)(round( b / 15 ) * 15);
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
	pWind->DrawImage( "Images\\ToolBars\\Statusbar\\SB1.jpg" , UI.StatusBarStartX , UI.StatusBarStartY);
}

//////////////////////////////////////////////////////////////////////////////////

void Output::CreateToolBars( ) const
{
	CreateDesignToolBar( );
	CreateFileToolBar( );
	CreateEditToolBar( );
	CreateStatusBar( );
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

void Output::StoreImage(image & imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight)
{
	pWind->StoreImage(imgThis, usX, usY, usWidth, usHeight);
}

//////////////////////////////////////////////////////////////////////////////////

void Output::ClearStatusBar()const
{
	CreateStatusBar( );
}

//////////////////////////////////////////////////////////////////////////////////////////

//Clears the drawing (design) area
void Output::ClearDrawingArea() const
{
	CreateGrid();
}

//////////////////////////////////////////////////////////////////////////////////////////

//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	pWind->DrawImage( "Images\\ToolBars\\Toolbar\\TB1.jpg" ,UI.ToolBarStartX , UI.ToolBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Toolbar\\TB2.jpg" ,UI.ToolBarTitleStartX , UI.ToolBarTitleStartY );

}

//////////////////////////////////////////////////////////////////////////////////

void Output::CreateFileToolBar( ) const
{

	pWind->DrawImage( "Images\\ToolBars\\Filebar\\FB1.jpg" , UI.FileBarStartX , UI.FileBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Filebar\\FB2.jpg" , UI.FileBarTitleStartX ,UI.FileBarTitleStartY );

}

//////////////////////////////////////////////////////////////////////////////////

void Output::CreateEditToolBar( ) const
{
	pWind->DrawImage( "Images\\ToolBars\\Editbar\\EB2.jpg" , UI.EditBarStartX , UI.EditBarStartY );
	pWind->DrawImage( "Images\\ToolBars\\Editbar\\EB3.jpg" , UI.EditBarTitleStartX ,UI.EditBarTitleStartY );
}

//////////////////////////////////////////////////////////////////////////////////

void Output::CreateGrid( ) const
{
/*
	pWind->SetPen( WHITE );
	pWind->DrawRectangle( 0 , 0 , UI.width , UI.height , FILLED );
	for ( int j = 0; j < 700; j += 15 )

	{
		for ( int i = 0; i < 1360; i += 15 )
		{
			pWind->SetPen( SKYBLUE , 1 );
			pWind->DrawCircle( i , j , 1 );
		}
	}  */
	pWind->DrawImage( "Images\\Grid.jpg" , 0 , 0 );
}

//////////////////////////////////////////////////////////////////////////////////

/*window * Output::GetPwind() const
{
	return pWind;
}  */

void Output::DrawDots(int xStart, int yStart,int xFinish,int yFinish)
{
	Magnetize(xStart, yStart);
	for (int j = yStart+15; j < yFinish; j += 15)
	{
		for (int i = xStart+15; i < xFinish; i += 15)
		{
			pWind->SetPen(WHITE, 1);
			pWind->DrawCircle(i, j, 1);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

void Output::MouseHovering( )const
{
	string z1 = "Images\\ToolBars\\Toolbar\\toolbar";
	string z2 = ".jpg";
	string z3 = "Images\\ToolBars\\Filebar\\filebar";
	string z4 = "Images\\ToolBars\\Editbar\\editbarDSN";
	string z5 = "Images\\ToolBars\\Editbar\\editbarSIM";
	image i;
	

	int x , y;
	pWind->GetMouseCoord( x , y );

	if(UI.isInToolBar(x,y ) )
	{
		if ( UI.HiddenToolBar ) return;
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


			
			}
		}

	}
	else {
		if(!UI.HiddenToolBar)CreateDesignToolBar( );
		
	}
	if (UI.isInFileBar(x,y))
	{
		if ( UI.HiddenFileBar )return;
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
			
			}
		}

	}
	else
	{
		if(!UI.HiddenFileBar)CreateFileToolBar();
		
	}
	if (UI.AppMode == DESIGN)
	{
		if (UI.isInEditBar(x, y))
		{
			if ( UI.HiddenEditBar )return;
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
				case 2: {PrintMsg("Truth table"); break; }
				case 3: {PrintMsg("Run"); break; }
				
				}
			}

		}
		else
		{
			if(!UI.HiddenEditBar)CreateEditToolBar();
			
		}
	}
	else {
		if (UI.isInEditBar(x, y))
		{
			if ( UI.HiddenEditBar )return;
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
				case 2: {PrintMsg("Truth Table"); break; }
				case 3: {PrintMsg("Design mode"); break; }
				
				}

			}

		}
		else
		{
			if ( !UI.HiddenEditBar )CreateEditToolBar( );  //TODO make it draw simulation
			
		}
	}
	if ( !UI.isInEditBar( x , y ) && !UI.isInFileBar( x , y ) && !UI.isInToolBar( x , y ) )
		PrintMsg( "" );
	pWind->UpdateBuffer( );
}

//////////////////////////////////////////////////////////////////////////////////

bool Output::FollowMouseAndDraw( GraphicsInfo & r_GfxInfo , ComponentType gType , Component ** Arr[780] , bool selected , int xOffset , int yOffset)
{
 	GraphicsInfo temp = r_GfxInfo;
	image initImage; pWind->StoreImage( initImage , 0 , 0 , UI.width , UI.height );
	  pWind->SetBuffering( true );

	  pWind->FlushKeyQueue( );
	  char cEscape;	//the character pressed to cancle the addition of the gate
	  bool forbidden = false; // it's true when the user hovers on forbidden area like an existing gate or one of the toolbars
		do {
			
			
			pWind->DrawImage( initImage , 0 , 0 );
			
			pWind->GetMouseCoord( r_GfxInfo.x1 , r_GfxInfo.y1 );
			r_GfxInfo.x1 = r_GfxInfo.x1 - UI.Gate_Width / 2 + xOffset;
			r_GfxInfo.y1 = r_GfxInfo.y1 - UI.Gate_Height / 2+ yOffset;
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
		


			forbidden = false;

		
			for ( int i = r_GfxInfo.x1; i < r_GfxInfo.x2; i++ )
			{
				for ( int j = r_GfxInfo.y1; j < r_GfxInfo.y2; j++ )
				{
					if(i>0&&j>0&&j<700&&i<1390 )
						if ( Arr[j][i] )
						{
							forbidden = true; break;
						}
				}
				if ( forbidden )break;
			}
			if ( forbidden )
			{
				PrintMsg( "You can't draw here!" );
				DrawGate(r_GfxInfo, gType, false, true);
			}
			else
			{
				DrawGate( r_GfxInfo , gType );
			}

			if ( !UI.HiddenToolBar )CreateDesignToolBar( );
			if ( !UI.HiddenFileBar )CreateFileToolBar( );
			if ( !UI.HiddenEditBar )CreateEditToolBar( );
			

				 
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
		
		
		r_GfxInfo.x1 = r_GfxInfo.x1 - UI.Gate_Width / 2 + xOffset;
		r_GfxInfo.y1 = r_GfxInfo.y1 - UI.Gate_Height / 2 + yOffset;
		Magnetize( r_GfxInfo.x1 , r_GfxInfo.y1 );
		r_GfxInfo.x2 = r_GfxInfo.x1 + UI.Gate_Width;
		r_GfxInfo.y2 = r_GfxInfo.y1 + UI.Gate_Height;
		
		PrintMsg( "" );
		pWind->SetBuffering( false );
return true;
		
}

//////////////////////////////////////////////////////////////////////////////////

bool Output::MoveComponents(ApplicationManager* pApp,Component* selected)
{

	vector<Component*> HighlightedVec = pApp->GetHighlightedList();
	Component*** Arr = pApp->GetArr( );

	GraphicsInfo & GfxSelected = selected->get_GraphicInfo();	//Gfxinfo of the selected gate

	vector<GraphicsInfo> initialGFxInfo;			//Initial position of components to restore them if ESCAPE was pressed

	image GateImage;

	for (int i = 0; i <int( HighlightedVec.size()); i++)
	{
		initialGFxInfo.push_back(HighlightedVec[i]->get_GraphicInfo());
		//DeleteGate(HighlightedVec[i]->get_GraphicInfo());
	}

	// screenshot of the current image and store it to draw over it

	image initImage;
	pWind->StoreImage(initImage, 0, 0, UI.width, UI.height);
	pWind->SetBuffering(true);
	
	pWind->FlushKeyQueue();
	
	char cEscape;	//the character pressed to cancle the addition of the gate
	bool forbidden = false; // it's true when the user hovers on forbidden area like an existing gate or one of the toolbars
	int x, y;  //Mouse coordinates
	do {
		pWind->DrawImage(initImage, 0, 0);

		int initialX = GfxSelected.x1, initialY = GfxSelected.y1;   // the initial coordinates of the selected gate

		pWind->GetMouseCoord(GfxSelected.x1, GfxSelected.y1);		// Center of the gate = mouse coordinates

		GfxSelected.x1 = GfxSelected.x1 - UI.Gate_Width / 2;		// changing the coordinates of the gate according to the new center
		GfxSelected.y1 = GfxSelected.y1 - UI.Gate_Height / 2;
		Magnetize(GfxSelected.x1, GfxSelected.y1);
		GfxSelected.x2 = GfxSelected.x1 + UI.Gate_Width;
		GfxSelected.y2 = GfxSelected.y1 + UI.Gate_Height;

		int xChange = GfxSelected.x1 - initialX;	// the change of the move in the X-direction
		int yChange = GfxSelected.y1 - initialY;	// the change of the move in the Y-direction

		for (unsigned int i = 0; i < HighlightedVec.size(); i++)
		{
			if (HighlightedVec[i] != selected)		//changing the coordinates of the other gates according to the xChange and yChange
			{
				GraphicsInfo &GfxInfo = HighlightedVec[i]->get_GraphicInfo();
				GfxInfo.x1 += xChange;
				GfxInfo.y1 += yChange;
				Magnetize(GfxInfo.x1, GfxInfo.y1);
				GfxInfo.x2 = GfxInfo.x1 + UI.Gate_Width;
				GfxInfo.y2 = GfxInfo.y1 + UI.Gate_Height;
			}
			
		}


		if (pWind->GetKeyPress(cEscape) == ESCAPE)		// if user pressed ESCAPE , all the components return to their initial positions
		{
			pWind->DrawImage(initImage, 0, 0);
			for (int i = 0; i < HighlightedVec.size(); i++)
				HighlightedVec[i]->set_GraphicInfo(initialGFxInfo[i]);
			pWind->UpdateBuffer();
			pWind->SetBuffering(false);
			return false;
		}

		forbidden = false;

		for (unsigned int k = 0; k < HighlightedVec.size(); k++)
		{
			GraphicsInfo r_GfxInfo = HighlightedVec[k]->get_GraphicInfo();

			for (int i = r_GfxInfo.x1; i <= r_GfxInfo.x2; i+=15)
			{
				for (int j = r_GfxInfo.y1; j <= r_GfxInfo.y2; j+=15)

				{
					if ( i > 0 && j > 0 && j < 700 && i < 1390 )
					{
						if ( Arr[j][i] )
						{
							forbidden = true; break;
						}
					}
					else
					{
						forbidden = true; break;
					}
				}
				if (forbidden)break;
			}
			
		}
		for ( unsigned int k = 0; k < HighlightedVec.size( ); k++ )
		{
			if ( forbidden )
				HighlightedVec[k]->Forbid( );
			else
				HighlightedVec[k]->Allow( );
			HighlightedVec[k]->Draw( this );
		}
		if (forbidden)
			PrintMsg("You can't draw here!");

		if (!UI.HiddenToolBar)CreateDesignToolBar();
		if (!UI.HiddenFileBar)CreateFileToolBar();
		if (!UI.HiddenEditBar)CreateEditToolBar();
		

		for (unsigned int k = 0; k < HighlightedVec.size(); k++)
		{
			GraphicsInfo GInfo=HighlightedVec[k]->get_GraphicInfo();
			if (UI.isForbidden(GInfo.x2, GInfo.y2)
				|| UI.isForbidden(GInfo.x1, GInfo.y1)
				|| UI.isForbidden(GInfo.x1, GInfo.y2)
				|| UI.isForbidden(GInfo.x2, GInfo.y1)
				|| forbidden)
			{
				PrintMsg("You can't draw here!");	forbidden = true;
			}
			else
			{
				PrintMsg("");  forbidden = false;
			}
		}
		pWind->UpdateBuffer();


	} while (pWind->GetMouseClick(x,y) == NO_CLICK || forbidden);

	PrintMsg("");
	pWind->SetBuffering(false);

	return true;

}

bool Output::PasteComponents( ApplicationManager * pApp )
{
	image initImage; pWind->StoreImage( initImage , 0 , 0 , UI.width , UI.height );
	pWind->SetBuffering( true );
	pWind->FlushKeyQueue( );
	char cEscape;	//the character pressed to cancle the addition of the gate
	bool forbidden = false; // it's true when the user hovers on forbidden area like an existing gate or one of the toolbars
 //  Component








	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////

//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)

}

//==========================================================================//
//								 Drawing Functions							//
//==========================================================================//

void Output::DrawJPEGImage(const image & imgThis, const int iX, const int iY, const int iWidth, const int iHeight)
{
	pWind->DrawImage(imgThis, iX, iY);
}

void Output::DrawPNGImage( string r_filename, GraphicsInfo GfxInfo )
{
	DrawPNG(pWind, r_filename, GfxInfo);
}

void Output::DrawGate(GraphicsInfo  r_GfxInfo, ComponentType gate,bool selected,bool forbidden)
{
	//Getting the image of the gate

	stringstream sstream;
	string GateNum;
	sstream << int(gate);
	sstream >> GateNum;
	string GateImage = "Images\\PNG Gates\\" + GateNum ;
	if ( forbidden )			//Forbidden
		GateImage += "F";
	else if (selected)			//Highlighted
		GateImage += "H";
	
	GateImage += ".png";

	//pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
	clock_t t = clock();
	DrawPNG	(pWind, GateImage, r_GfxInfo);
	cout << clock() - t<<endl;
}

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

void Output::DrawRect(int& x, int &y)
{
	pWind->GetMouseCoord(x, y);
	pWind->SetBrush(SLATEGRAY);
	pWind->SetPen(GRAY, 2);
	pWind->DrawRectangle(x, y, UI.u_GfxInfo.x1, UI.u_GfxInfo.y1, FILLED);

	int xstart, ystart, xfinish, yfinish;

	if (x <= UI.u_GfxInfo.x1)
		xstart = x, xfinish = UI.u_GfxInfo.x1;
	else xfinish = x, xstart = UI.u_GfxInfo.x1;
	if (y <= UI.u_GfxInfo.y1)
		ystart = y, yfinish = UI.u_GfxInfo.y1;
	else yfinish = y, ystart = UI.u_GfxInfo.y1;

	DrawDots(xstart, ystart, xfinish, yfinish);
}

//////////////////////////////////////////////////////////////////////////////////

void Output::DeleteGate( GraphicsInfo GfxInfo )
{
	pWind->DrawImage( "Images\\Images\\Gates\\emptygate.jpg" , GfxInfo.x1 , GfxInfo.y1 );
}


//TODO: Add similar functions to draw all components


bool Output::SetBuffering( const bool bSetting )
{
	return pWind->SetBuffering(bSetting);
}

void Output::UpdateBuffer( )
{
	pWind->UpdateBuffer( );
}

void Output::FlushMouseQueue( )
{
	pWind->FlushMouseQueue( );
}

void Output::FlushKeyQueue( )
{
	pWind->FlushKeyQueue( );
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, BFSOut &kol, Component*con, bool selected) const
{
	//TODO: Add code to draw connection
	if (selected)
		pWind->SetPen(ROYALBLUE, 5);
	else
		pWind->SetPen(BLACK, 5);
	int a = r_GfxInfo.x2, b = r_GfxInfo.y2;
	//for (int i = 0;i < 780;i++)for (int j = 0;j < 1400;j++)if (AppManger->GetArr()[i][j] == con)pWind->DrawPixel(j, i);
	
	while (true)
	{
		if (a == r_GfxInfo.x1 &&b == r_GfxInfo.y1)break;
		int c = a;int d = b;
		a = kol.arr[c][d].first;
		b = kol.arr[c][d].second;
		bool test = false;

		if ((AppManger->GetArr()[d][c] == con || (c == r_GfxInfo.x2&&d == r_GfxInfo.y2))
			&& (AppManger->GetArr()[b][a] == con || (a == r_GfxInfo.x1&&b == r_GfxInfo.y1) || dynamic_cast<Connection*>(AppManger->GetArr()[b][a])->getSourcePin() == dynamic_cast<Connection*>(con)->getSourcePin()))
		{
			
			pWind->DrawLine(c, d - UI.ConnectionOffset, a, b - UI.ConnectionOffset);
		}
		else if(!(dynamic_cast<Connection*>(AppManger->GetArr()[b][a])->getSourcePin() == dynamic_cast<Connection*>(con)->getSourcePin()))
		{
			
			if (c == a) {
				if(d>b)
				pWind->DrawBezier(c, d - 4, a - 15, b, a - 7, b - 7, a, b - 17);
				else
				pWind->DrawBezier(a, b +8, c - 15, d, c - 7, d - 7, c, d - 7);
			}
			else
				if(c>a)
					pWind->DrawBezier(c - 1, d -7, a +3, b-15, a - 6, b - 14, a-16, b-7 );
				else
					pWind->DrawBezier(a +15, b - 7, c+19, d - 15, c +16, d - 14, c+2 , d - 7);
		}

	}
}
Output::~Output()
{
	delete pWind;
}


