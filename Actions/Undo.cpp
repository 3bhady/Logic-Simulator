#pragma once
#include "Undo.h"
class Cut {};

Undo::Undo(ApplicationManager *pApp) :Action(pApp)
{
	
}

Undo::~Undo(void)
{
}

bool Undo::ReadActionParameters(string s)
{
	if(!pManager->getUndoStack().empty())
		return true;
	else return false;
}

void Undo::Execute()
{
	if (ReadActionParameters(""))
	{
		pManager->getUndoStack().top()->undo();
		if (!dynamic_cast<Cut*>(pManager->getUndoStack().top()))
			pManager->getRedoStack().push(pManager->getUndoStack().top());			//Push this action into the redo stack
		pManager->getUndoStack().pop();												//Pop this action out of the undo stack
	}
}
