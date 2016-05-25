#include "New.h"



New::New(ApplicationManager*pApp):Action(pApp)
{
}


New::~New()
{
}

bool New::ReadActionParameters()
{
	return false;
}

void New::Execute()
{
	pManager->ClearComplist();

	//function in appmanger btfady the two stacks
	while (!pManager->getUndoStack().empty())
		pManager->getUndoStack().pop();
	while (!pManager->getRedoStack().empty())
		pManager->getRedoStack().pop();
	pManager->GetOutput()->ClearDrawingArea();
	pManager->GetOutput()->CreateToolBars();
	pManager->UpdateInterface();
	pManager->GetOutput()->UpdateBuffer();
	Component::setID(1);

}

void New::undo()
{
}

void New::redo()
{
}
