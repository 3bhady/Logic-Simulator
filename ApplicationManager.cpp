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
#include"Actions\HideDesignToolBar.h"
#include"Actions\ShowDesignToolBar.h"
#include"Actions\ShowFileToolBar.h"
#include"Actions\HideFileToolBar.h"
#include"Actions\ShowEditToolBar.h"
#include"Actions\HideEditToolBar.h"
#include"Actions\EditMenu.h"
#include"Actions\Label.h"
#include"Actions\Save.h"
#include"Actions\Load.h"
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
		pComp->AddComponent(this);


	//Push Component in CompList
	CompList.push_back(pComp);

	//Increase Components count
	CompCount++;
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::save(ofstream &fout)
{
	fout << CompList.size();
	fout << endl;
	for (unsigned int i = 0; i < CompList.size(); i++)
		CompList[i]->Save(fout);
}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::GetComponent( int x , int y )
{
	return Arr[y][x];
}

void ApplicationManager::DeleteComponent( int x , int y )
{
	DeleteComponent( Arr[y][x] );
}

void ApplicationManager::DeleteComponent( Component * pComp )
{
	
	pComp->DeleteComponent( this );
	if ( pComp == NULL )
		return;

	/*for ( int j = m_GfxInfo.x1; j < m_GfxInfo.x2 - 1; j++ )
		for ( int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++ )
			Arr[i][j] = NULL;	
	for ( unsigned int i = 0; i < CompList.size( ); i++ )
		if ( CompList[i] == pComp )
		{
			OutputInterface->DeleteGate( m_GfxInfo );
			delete pApp->GetCompList( )[i];
			pApp->GetCompList( ).erase( pApp->GetCompList( ).begin( ) + i );
			break;
		}		
		*/
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

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is required from the user
	OutputInterface->MouseHovering(this);
	return InputInterface->GetUserAction(this,false);
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
	if (ActType == HIDE_DESIGN_B)
		pAct = new HideDesignToolBar(this);
	if (ActType == SHOW_DESIGN_B)
		pAct = new ShowDesignToolBar(this);
	if (ActType == SHOW_FILE_B)
		pAct = new ShowFileToolBar(this);
	if (ActType == HIDE_FILE_B)
		pAct = new HideFileToolBar(this);
	if (ActType == SHOW_EDIT_B)
		pAct = new ShowEditToolBar(this);
	if (ActType == HIDE_EDIT_B)
		pAct = new HideEditToolBar(this);
	if (ActType == EDIT_Label)
		pAct = new Label(this);
	if (ActType == SAVE)
		pAct = new Save(this);
	if (ActType == LOAD)
		pAct = new Load(this);
	if (ActType == EXIT)
		return;
	if(pAct)
	{
		//if Action undo or redo don't push in stacks
		if (ActType != UNDO && ActType != REDO)
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
