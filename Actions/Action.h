#pragma once
#include"..\ApplicationManager.h"

//Base class for all possible actions (abstract class)
class Action
{
protected:
	ApplicationManager *pManager;	//Pointer to Appmanager
	image initImage;				//Image before the action
public:
	Action(ApplicationManager *pApp)
	{
		pManager = pApp;
		pApp->GetOutput()->StoreImage(initImage, 0, 0, UI.width, UI.height);	//constructor
	}
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters() = 0;
	
	//Execute action (code depends on action type)
	virtual void Execute() = 0;

	//To undo this action (code depends on action type)
	virtual void undo()=0;

	//To redo this action (code depends on action type)
	virtual void redo()=0;

};
