#include "ApplicationManager.h"
#include "Actions\AddGate.h"
#include "Actions\AddLED.h"
#include "Actions\AddSwitch.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	Arr = new Component**[780];
	for ( int i = 0; i < 780; i++ )
	{
		Arr[i] = new Component*[1400];
	for ( int j = 0; j < 1400; j++ )
			Arr[i][j] = NULL;
	}


	//memset( Arr , NULL , sizeof( Arr ) );
	//Arr[0][0] = NULL;
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
	OutputInterface->MouseHovering(  );
	GraphicsInfo GfInfo;
	return InputInterface->GetUserAction(this,GfInfo,Arr,false);
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
	if(ActType<=13)
			pAct = new AddGate( this , ActType );
	/*case ADD_AND_GATE_2 || ADD_AND_GATE_3 || ADD_Buff || ADD_INV ||	ADD_OR_GATE_2 ||
		 ADD_NAND_GATE_2 || ADD_NOR_GATE_2 || ADD_XOR_GATE_2 || ADD_XNOR_GATE_2 ||
		ADD_OR_GATE_3 || ADD_NOR_GATE_3 || ADD_NAND_GATE_3 || ADD_XOR_GATE_3 || ADD_XNOR_GATE_3:
						pAct = new AddGate(this,ActType); break;
*/


	if(ActType== ADD_LED)
		pAct = new AddLED(this);

	if(ActType== ADD_Switch)
		pAct = new AddSwitch(this);

	if ( ActType == EXIT )

		return;

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

Component *** ApplicationManager::GetArr( )
{
	return Arr;
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
