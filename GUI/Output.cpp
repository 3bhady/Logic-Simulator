#include "Output.h"
using namespace std;
#include<iostream>
Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
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

	//Magnetizing
	if (a - (15 * (a / 15)) < a - (15 * ((a / 15) + 1)))
	{
	x = (15 * (int(a) / 15));
	}
	else x = (15 * ((int(a) / 15) + 1));

	if (b - (15 * (b / 15)) < b - (15 * ((b / 15) + 1)))
	{
	y = (15 * (int(b) / 15));
	}
	else y = (15 * ((int(b) / 15) + 1));
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	//pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
//	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	//pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
//	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	//pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height  );// UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolBarItemWidth,0,UI.ToolBarItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
window * Output::GetPwind() const
{
	return pWind;
}
void Output::MouseHovering( )const
{
	if ( UI.ToolBarHidden ) return;
	string z1 = "images\\AA\\";
	string z2 = ".jpg";
	image i;
	//pWind->StoreImage( i , 0 , 0 , UI.width , UI.height );

	int x , y;
	pWind->GetMouseCoord( x , y );
	if ( y >= 0 && y < UI.ToolBarHeight&&x <= UI.ToolBarItemWidth * 17 )
	{
		string num = "" , s = "";
		stringstream ss;
		int ClickedItemOrder = (x / UI.ToolBarItemWidth);
		ss << ClickedItemOrder;
		ss >> num;
		s = z1 + num + num + z2;
		if ( ClickedItemOrder < 17 )
		{
			pWind->DrawImage( s , 0 , 0 );
			PrintMsg( "add " + ss.str( ) );
		}

	}
	else {
		pWind->DrawImage( "images\\Menu\\Toolbar1.jpg" , 0 , 0 );
		pWind->DrawImage( "images\\Menu\\Toolbar2.jpg" , 0 , 66 );
		PrintMsg( "" );
	}

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

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg";
	else
	{
		//Getting mouse coordiantes
		int x, y;
		pWind->GetMouseCoord(x, y);
		//Getting top left corner of the gate
		/*
		double a, b;
		a = x - (double(UI.Gate_Width) / 2);
		b = y - (double(UI.Gate_Height) / 2);

		//Magnet effect :D 
		if (a - (15 * (a / 15)) < a - (15 * ((a / 15) + 1)))
		{
			x = (15 * (int(a) / 15));
		}
		else x = (15 * ((int(a) / 15) + 1));

		if (b - (15 * (b / 15)) < b - (15 * ((b / 15) + 1)))
		{
			y = (15 * (int(b) / 15));
		}
		else y = (15 * ((int(b) / 15) + 1));
		*/
		pWind->DrawImage("Images\\Gates\\EDIT MENU.jpg", x, y, 102, 161);
		//pWind->DrawImage("Images\\Gates\\afr.jpg", x-30,y-15, 60, 30);
		//pWind->DrawImage("Images\\Gates\\LLL.jpg", x + 22.5, y + 22.5, 45, 45);
		//pWind->DrawImage("Images\\Gates\\NAND3.jpg", x, y, UI.Gate_Width, UI.Gate_Height);
		//pWind->DrawImage("Images\\Gates\\NOR2.jpg", x+90, y+90, UI.Gate_Width, UI.Gate_Height);
		//pWind->DrawImage("Images\\Gates\\qqq2.jpg", 758, 577, UI.Gate_Width, UI.Gate_Height);
		//GateImage = "Images\\Gates\\qq.jpg";
	}
	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	//pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawGate(GraphicsInfo r_GfxInfo, DsgnMenuItem gate,bool selected)
{
	//Getting the image of the gate

	stringstream sstream;
	string GateNum;
	sstream << int(gate);
	sstream >> GateNum;
	string GateImage = "Images\\Images\\Gates\\" + GateNum ;
	if (selected)
		GateImage += "H";
	GateImage += ".jpg";
	/*
	//Getting mouse coordiantes

	//int x, y;
	//pWind->GetMouseCoord(r_GfxInfo.x1, r_GfxInfo.y1);
	*/
	Magnetize(r_GfxInfo.x1, r_GfxInfo.y1);

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

void Output::DrawLED(GraphicsInfo r_GfxInfo,  bool state, bool selected)
{
	//Getting the switch image

	string LEDImage = "Images\\Images\\LED";
	if (state)			  // ON or OFF
	{
		string LEDcolor;
		// generate random number between 0 and 5 
		// choosing a LED color

		srand(time(NULL));
		int randNum = rand() % 6;
		stringstream sstream;
		sstream << randNum;
		sstream >> LEDcolor;
		LEDImage += "ON" + LEDcolor;
	}
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

	string SwitchImage = "Images\\Images\\Switch\\";
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

	string MenuImage="Images\\Images\\EDIT MENU\\";
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

//TODO: Add similar functions to draw all components


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
}


Output::~Output()
{
	delete pWind;
}
