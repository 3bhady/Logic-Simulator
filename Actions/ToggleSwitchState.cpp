#include "ToggleSwitchState.h"



ToggleSwitchState::ToggleSwitchState(ApplicationManager* pApp):Action(pApp)
{
}


ToggleSwitchState::~ToggleSwitchState()
{
}

bool ToggleSwitchState::ReadActionParameters()
{
	return true;
}

void ToggleSwitchState::Execute()
{
	//Component clicked by the user
	Component* Cmp = pManager->GetComponent(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1);
	if (Cmp->GetOutPinStatus() == LOW)
		Cmp->SetOutPinStatus(HIGH);
	else Cmp->SetOutPinStatus(LOW);
}

void ToggleSwitchState::undo()
{
}

void ToggleSwitchState::redo()
{
}
