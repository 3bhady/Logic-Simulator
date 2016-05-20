#pragma once
#include "Redo.h"

Redo::Redo(ApplicationManager *pApp) :Action(pApp)
{

}

Redo::~Redo(void)
{
}

bool Redo::ReadActionParameters()
{
	if (!pManager->getRedoStack().empty())
		return true;
	else return false;
}

void Redo::Execute()
{

	if (ReadActionParameters())
	{
		pManager->getRedoStack().top()->redo();								//Redo action
		pManager->getUndoStack().push(pManager->getRedoStack().top());		//Push action in undo stack
		pManager->getRedoStack().pop();										//Pop action from redo stack
	}
}
