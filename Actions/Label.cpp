#include "Label.h"



Label::Label(ApplicationManager *pApp) :Action(pApp)
{
}


Label::~Label()
{
}

bool Label::ReadActionParameters()
{
	return true;
}

void Label::Execute()
{
	////the following three lines are repeated in every editmenu action!
	if (UI.AppMode == EDIT_MODE)
		pManager->GetOutput()->CloseEditMenu(pManager);

	if (pManager->getHighlightedCompListSize() != 0)
	{
		string str;
		str = pManager->GetInput()->GetString(pManager->GetOutput());
		str = str == "" ? "NO-LABEL" : str;
		for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
		pManager->GetHighlightedComponent(i)->set_label(str);	
	}

}

void Label::undo()
{
}

void Label::redo()
{
}
