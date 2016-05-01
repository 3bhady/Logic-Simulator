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
	
	//Component  
	Component *** Arr;
	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	vector<Component*> CompList;	//List of all Components (Array of pointers)
	
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface


public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	Component *** GetArr( );
	//Adds a new component to the list of components
	void AddComponent(Component* pComp);


	vector<Component*> GetCompList();

	//destructor
	~ApplicationManager();
};

//#endif