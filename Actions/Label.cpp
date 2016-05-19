#include "Label.h"



Label::Label(ApplicationManager *pApp) :Action(pApp)
{
}


Label::~Label()
{
}

bool Label::ReadActionParameters(string s)
{
	return true;
}

void Label::Execute()
{
	////the following three lines are repeated in every editmenu action!
	if (UI.AppMode == EDIT_MODE)
		pManager->GetOutput()->CloseEditMenu(pManager);
	for (int i = 0; i < pManager->GetCompList().size(); i++)
		pManager->GetCompList()[i]->Draw(pManager->GetOutput());
	if (!pManager->GetHighlightedList().empty())
	{
		string str;
		str = pManager->GetInput()->GetString(pManager->GetOutput());
		for (int i = 0; i < pManager->GetHighlightedList().size();i++)
		pManager->GetHighlightedList()[i]->set_label(str);	
	}

}

void Label::undo()
{
}

void Label::redo()
{
}
