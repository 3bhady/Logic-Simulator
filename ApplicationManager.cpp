#include "ApplicationManager.h"
#include "Actions\AddGate.h"
#include "Actions\AddLED.h"
#include "Actions\AddSwitch.h"
#include "Actions\Select.h"
#include "Actions\AreaSelect.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
#include"Actions\Undo.h"
#include"Actions\Redo.h"
#include"Actions\AddConnection.h"
#include"Actions\Action.h"
#include"Actions\EditMenu.h"
#include"Actions\Label.h"
#include"Actions\Save.h"
#include"Actions\Load.h"
#include "Actions\Delete.h"
#include"Actions\ToggleBars.h"
#include"Actions\Simulate.h"
#include"Actions\New.h"
#include"Actions\TruthTable.h"
#include "Actions\ToggleSwitchState.h"
#include<fstream>

ApplicationManager::ApplicationManager()
{
	//Initialize Components count
	CompCount = 0;

	//Create Grid
	Arr = new Component**[780];
	for ( int i = 0; i < 780; i++ )
	{
		Arr[i] = new Component*[1400];
	for ( int j = 0; j < 1400; j++ )
			Arr[i][j] = NULL;
	}

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output(this);
	InputInterface = OutputInterface->CreateInput();
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::AddComponent(Component* pComp)
{
	//Add Components in Grid
	if (dynamic_cast<Connection*>(pComp))
		pComp->AddConnection(((Connection*)pComp)->get_path(), this);
	else
	{
		pComp->AddComponent(this);
	}
		//Push Component in CompList
		CompList.push_back(pComp);

		//Set index of Component
		pComp->setCompIndex(CompCount);

		//Increase Components count
		CompCount++;
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::save(ofstream &fout)
{
	int CompSize = 0;
	for (unsigned int i = 0; i < CompList.size(); i++)
		if (!dynamic_cast<Connection*>(CompList[i]))
		{
			CompSize++;
		}
	fout << CompSize;
	fout << endl;
		for (unsigned int i = 0; i < CompList.size(); i++)
		if (!dynamic_cast<Connection*>(CompList[i]))
			CompList[i]->Save(fout);
		fout << endl;
		fout << "Connections: "<< endl;
		for (unsigned int i = 0; i < CompList.size(); i++)
			if (dynamic_cast<Connection*>(CompList[i]))
			{
				CompList[i]->Save(fout);
				fout << endl;
			}
		fout << "-1";
		
}

void ApplicationManager::load(ifstream & fin)
{
	Component*pG;
	int CompNum;
	fin >> CompNum;
	string type;
	GraphicsInfo L_GfxInfo;
	for (int i = 0; i < CompNum; i++)
	{
		fin >> type;
		if (type == "AND2")
		{
			pG = new AND2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "AND3")
		{
			pG = new AND3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "BUFFER")
		{
			pG = new BUFFER(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "LED")
		{
			pG = new LED(L_GfxInfo);// , AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "NAND2")
		{
			pG = new NAND2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "NAND3")
		{
			pG = new NAND3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "NOR2")
		{
			pG = new NOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "NOR3")
		{
			pG = new NOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "INVERTER")
		{
			pG = new NOT(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "OR2")
		{
			pG = new OR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "OR3")
		{
			pG = new OR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "SWITCH")
		{
			pG = new Switch(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "XNOR2")
		{
			pG = new XNOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "XNOR3")
		{
			pG = new XNOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "XOR2")
		{
			pG = new XOR2(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
		if (type == "XOR3")
		{
			pG = new XOR3(L_GfxInfo, AND2_FANOUT);
			pG->Load(fin);
			AddComponent(pG);
		}
	}
	string s = "";
	fin >> s;
	while (true)
	{
		int SrcID;
		int DstID;
		int x;
		fin >> SrcID;
		if (SrcID == -1)
			break;
		fin >> DstID;
		fin >> x;
		AddConnection*Load = new AddConnection(this);
		Load->LoadConnection(SrcID, DstID);
	}
}

////////////////////////////////////////////////////////////////////

int ApplicationManager::GetComplistSize()
{
	return CompCount;
}

void ApplicationManager::ClearComplist()
{
	for ( int i = 0; i < CompList.size( ); i++ )
	{
		CompList[i]->DeleteComponent( this );
	}
	CompList.clear();
}

Component* ApplicationManager::GetComponent( int x , int y )
{
	return Arr[y][x];
}

Component*& ApplicationManager::GetComponent(int index)
{
	return CompList[index];
}

void ApplicationManager::PointToNull(int x, int y)
{
	Arr[y][x] = NULL;
}

void ApplicationManager::DeleteComponent( int x , int y )
{
	//DeleteComponent( Arr[y][x] );
	Arr[y][x]->DeleteComponent( this );
}

void ApplicationManager::DeleteComponent( Component * pComp )
{
	
	for ( unsigned int i = 0; i < HighlightedCompList.size( ); i++ )
		if ( HighlightedCompList[i] == pComp )
		{
			HighlightedCompList.erase( HighlightedCompList.begin( ) + i );
			break;
		}

	for ( unsigned int i = 0; i < CompList.size( ); i++ )
		if ( CompList[i] == pComp )
		{

			delete CompList[i];
			CompList.erase( CompList.begin( ) + i );
			break;
		}
}

void ApplicationManager::EraseComponent(GraphicsInfo GFX)
{
	for (int j = GFX.x1; j < GFX.x2; j++)
		for (int i = GFX.y1; i < GFX.y2; i++)
			Arr[i][j] = NULL;
}

vector<Component*>& ApplicationManager::GetCompList()
{
	return CompList;
}

////////////////////////////////////////////////////////////////////

vector<Component*>& ApplicationManager::GetHighlightedList()
{
	return HighlightedCompList;
}

////////////////////////////////////////////////////////////////////

stack<Action*>& ApplicationManager::getUndoStack()
{
	return UndoStack;
}

////////////////////////////////////////////////////////////////////

stack<Action*>& ApplicationManager::getRedoStack()
{
	return RedoStack;
}

////////////////////////////////////////////////////////////////////

/*Component * ApplicationManager::GetComponent(int x ,int y)
{
	return Arr[y][x];
}  */

////////////////////////////////////////////////////////////////////

void ApplicationManager::ClearHighlightedCompList()
{
	for (unsigned int i = 0; i < HighlightedCompList.size(); i++)		//Unhighlight all components
		HighlightedCompList[i]->Unhighlight();

	HighlightedCompList.clear();	//Clear List
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::HighlightComponent(Component *pC)
{
	pC->Highlight();
	HighlightedCompList.push_back(pC);
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::HighlightComponent(int x, int y)
{
	if ( Arr[y][x] )
	{
		Arr[y][x]->Highlight( );
		HighlightedCompList.push_back( Arr[y][x] );
	}
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UnhighlightComponent(Component *pC)
{
	if ( pC )
	{
		pC->Unhighlight( );
		for ( unsigned int i = 0; i < HighlightedCompList.size( ); i++ )
			if ( HighlightedCompList[i] == pC )
			{
				HighlightedCompList.erase( HighlightedCompList.begin( ) + i );
				return;
			}
	}
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UnhighlightComponent(int x, int y)
{
	if ( Arr[y][x] )
	{
		Arr[y][x]->Unhighlight( );
		for ( unsigned int i = 0; i < HighlightedCompList.size( ); i++ )
			if ( HighlightedCompList[i] == Arr[y][x] )
			{
				HighlightedCompList.erase( HighlightedCompList.begin( ) + i );
				return;
			}
	}
}

////////////////////////////////////////////////////////////////////

Component * ApplicationManager::GetHighlightedComponent(int index)
{
	return HighlightedCompList[index];
}

unsigned int ApplicationManager::getHighlightedCompListSize()
{
	return HighlightedCompList.size();
}

void ApplicationManager::UpdateComponentsIndexes()
{
	for (unsigned int i = 0; i < CompList.size(); i++)
		CompList[i]->setCompIndex(i);
}

void ApplicationManager::NewProject()
{
	ClearComplist();
	//function in appmanger btfady the two stacks
	while (!UndoStack.empty())
	{
		Action* temp = UndoStack.top();
		UndoStack.pop();
		delete temp;
	}
	while (!RedoStack.empty())
	{
		Action* temp = RedoStack.top();
		RedoStack.pop();
		delete temp;
	}
	GetOutput()->ClearDrawingArea();
	GetOutput()->CreateToolBars();
	UpdateInterface();
	GetOutput()->UpdateBuffer();
	Component::setID(1);
}

////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is required from the user
	OutputInterface->MouseHovering(this);
	return InputInterface->GetUserAction(this);
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//Create Action 
	if(ActType<=13)
		pAct = new AddGate( this , ActType );
	if ( ActType == COPY )
		pAct = new Copy( this );
	if ( ActType == CUT )
		pAct = new Cut( this );
	if ( ActType == PASTE )
		pAct = new Paste( this );
	if ( ActType == AREASELECT )
		pAct = new AreaSelect( this );
	if (ActType == SELECT)
		pAct = new Select(this);
	if(ActType== ADD_LED)
		pAct = new AddLED(this);
	if(ActType== ADD_Switch)
		pAct = new AddSwitch(this);
	if (ActType == ADD_CONNECTION)
		pAct = new AddConnection(this);
	if (ActType == UNDO)
		pAct = new Undo(this);
	if (ActType == REDO)
		pAct = new Redo(this);
	if (ActType == EDIT_MENU)
		pAct = new EditMenu(this);
	if (ActType == TOGGLE_BARS)
		pAct = new ToggleBars(this);
	if (ActType == EDIT_Label)
		pAct = new Label(this);
	if (ActType == SAVE)
		pAct = new Save(this);
	if (ActType == LOAD)
		pAct = new Load(this);
	if (ActType == SIM_MODE)
		pAct = new Simulate(this);
	if (ActType == EXIT)
		return;
	if ( ActType == DEL )
		pAct = new Delete( this );
	if (ActType == NEW)
		pAct = new New(this);
	if (ActType ==Create_TruthTable)
		pAct = new TruthTable(this);
	if (ActType == Change_Switch)
		pAct = new ToggleSwitchState(this);
	if(pAct)
	{
		//if Action undo or redo don't push in stacks
		if (ActType != UNDO && ActType != REDO&&ActType!=LOAD
			&&ActType!=SAVE&&ActType!=NEW)
		{
			UndoStack.push(pAct);					//Push Action into Undo Stack
			while (!getRedoStack().empty())			//Empty the stack
				getRedoStack().pop();
		}
		pAct->Execute();		//Execute Action
	}
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	//if not Edit Mode Draw Components
	if (UI.AppMode != EDIT_MODE)
	for (unsigned int i = 0; i < CompList.size(); i++)
		CompList[i]->Draw(OutputInterface);
	//OutputInterface->UpdateBuffer( );
}

////////////////////////////////////////////////////////////////////

Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////

Component *** ApplicationManager::GetArr( )
{
	return Arr;
}

vector< pair<GraphicsInfo , ComponentType> >& ApplicationManager::GetClipboard( )
{
	return Clipboard;
}

void ApplicationManager::AddToClipboard( Component * pComp )
{

	Clipboard.push_back( make_pair( pComp->get_GraphicInfo( ) , pComp->getType( ) ) );

}

////////////////////////////////////////////////////////////////////

Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	//Free memory
	for(unsigned int i=0; i<CompList.size(); i++)
		delete CompList[i];
	while (!UndoStack.empty())
	{
		Action* temp = UndoStack.top();
		UndoStack.pop();
		delete temp;
	}
	while (!RedoStack.empty())
	{
		Action* temp = RedoStack.top();
		RedoStack.pop();
		delete temp;
	}
	delete OutputInterface;
	delete InputInterface;
}



