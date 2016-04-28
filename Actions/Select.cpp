#include "Select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

bool Select::ReadActionParameters(string s)
{
	return true;
}

void Select::Execute()
{
	if (pManager->GetArr()[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1])
	{
		pManager->GetArr()[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1]->ChangeState();
	}
}

void Select::Undo()
{
}

void Select::Redo()
{
}

Select::~Select()
{
}
