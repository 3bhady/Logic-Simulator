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
	pManager->NewProject();
}

void New::undo()
{
}


void New::redo()
{
}
