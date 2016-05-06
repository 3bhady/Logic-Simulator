//#ifndef APPLICATION_MANAGER_H
//#define APPLICATION_MANAGER_H
#pragma once
#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include<vector>

class Component;

//Main class that manages everything in the application.
class ApplicationManager
{			

	Component *** Arr;		//Grid of pointers to components

	enum { MaxCompCount = 200 };	//Max no of Components
	vector< pair<GraphicsInfo,ComponentType> > Clipboard;

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

	void AddComponent(Component* pComp);	//Adds a new component to the list of components	
	 

	vector<Component*>& GetCompList();				//returns the components list
	vector<Component*>& GetHighlightedList();		//returns the highlighted components list

};

//#endif