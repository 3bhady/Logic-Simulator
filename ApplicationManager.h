#pragma once

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Components\Component.h"
#include<vector>
#include<stack>

class Component;
class Action;

//Main class that manages everything in the application.
class ApplicationManager
{			

	Component *** Arr;		//Grid of pointers to components

	enum { MaxCompCount = 200,MaxundoActions =10 };	//Max no of Components
	vector< pair<GraphicsInfo, ComponentType> > Clipboard;
	stack<Action*> UndoStack;
	stack<Action*> RedoStack;

private:
	int CompCount;		//Actual number of Components

	vector<Component*> CompList;				//List of all Components (Array of pointers)
	vector<Component*> HighlightedCompList;		//List of highlighted Components (Array of pointers)
	
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface


public:	

	ApplicationManager();		//constructor
	~ApplicationManager();		//destructor

	ActionType GetUserAction();		//Reads the required action from the user and returns the corresponding action type
	
	void ExecuteAction(ActionType);		//Creates an action and executes it
	
	void UpdateInterface();		//Redraws all the drawing window

	Output* GetOutput();	//Gets a pointer to Output Object
	Input* GetInput();		//Gets a pointer to Input  Object

	Component *** GetArr( );	//returns the grid
	vector< pair<GraphicsInfo , ComponentType> >& GetClipboard( );
	void AddToClipboard(Component* pComp);

	void AddComponent(Component* pComp);	//Add component in 2D array and push it in complist	
	 
	void save(ofstream &fout);
	//void load(ifstream &fin);

	//Component* GetComponent( int x , int y );
	void DeleteComponent(int x,int y);
	void DeleteComponent( Component* pComp );
	void EraseComponent(GraphicsInfo GFX);

	vector<Component*>& GetCompList();				//returns the components list
	vector<Component*>& GetHighlightedList();		//returns the highlighted components list

	stack<Action*>& getUndoStack();		//returns the undo Stack
	stack<Action*>& getRedoStack();		//returns the redo Stack

	int GetComplistSize();							//returns the size of complist 
	void ClearComplist();							//Deletes all components and clears the complist
	Component* GetComponent(int x,int y);			//Get component from GRID
	Component* &GetComponent(int index);				//Get component by index from complist
	void PointToNull(int x, int y);					//Make point points to NULL in the GRID
	void ClearHighlightedCompList();				//Clear the HighlightedComplist
	void HighlightComponent(Component*);			//Highlight component
	void HighlightComponent(int x, int y);			//Highlight component
	void UnhighlightComponent(Component*);			//Unhighlight component
	void UnhighlightComponent(int x, int y);		//Unhighlight component
	Component* GetHighlightedComponent(int index);	//Get component from highlighted list
	unsigned int getHighlightedCompListSize();		//returns highlighted list size
	void UpdateComponentsIndexes();					//updates the indexes of the components in the complist
	void PreSimulation();							//Makes the components ready to simulation
	void TurnOffLEDs();								//Turn all LEDS off
};