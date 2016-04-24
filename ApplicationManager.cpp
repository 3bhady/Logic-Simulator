#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddGate.h"
#include "Actions\AddLED.h"
#include "Actions\AddSwitch.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	for ( int i = 0; i < 780; i++ )
	{
		Arr[i] = new Component*[1400];
	}
	
	memset( Arr , NULL , sizeof( Arr ) );
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	pComp->AddComponent( Arr );
	CompList[CompCount++] = pComp;

}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is required from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	/*switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;

		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;
	

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	*/
	switch (ActType)
	{
	case ADD_AND_GATE_2 || ADD_AND_GATE_3 || ADD_Buff || ADD_INV ||	ADD_OR_GATE_2 ||
		 ADD_NAND_GATE_2 || ADD_NOR_GATE_2 || ADD_XOR_GATE_2 || ADD_XNOR_GATE_2 || 	
		ADD_OR_GATE_3 || ADD_NOR_GATE_3 || ADD_NAND_GATE_3 || ADD_XOR_GATE_3 || ADD_XNOR_GATE_3:
			pAct = new AddGate(this,ActType);
			break;
	case ADD_LED:
		pAct = new AddLED(this);
		break;
	case ADD_Switch:
		pAct = new AddSwitch(this);
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}