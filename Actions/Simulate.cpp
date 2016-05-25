#include "Simulate.h"
#include"..\Components\Gate.h"
#include"..\Components\LED.h"

Simulate::Simulate(ApplicationManager *pApp):Action(pApp)
{
}


Simulate::~Simulate()
{
}

bool Simulate::ReadActionParameters()
{
	return true;
}

void Simulate::Execute()
{
	if (Run(pManager))
	{
		UI.AppMode = SIMULATION;
		if (!UI.HiddenToolBar)
			pManager->GetOutput()->HideDesignToolBar();
		for ( int i = 0; i < pManager->GetComplistSize(); i++)
		{
			if (dynamic_cast<Gate*>(pManager->GetComponent(i)))
				((Gate*)pManager->GetComponent(i))->ShowPinsStatuses(pManager->GetOutput());
		}
	}
	else {
		for ( int i = 0; i < pManager->GetComplistSize(); i++)
		{
			if (dynamic_cast<LED*>(pManager->GetComponent(i)))
				(((LED*)pManager->GetComponent(i)))->setState(LOW);
		}
	}
}

void Simulate::undo()
{
}

void Simulate::redo()
{
}


bool Simulate::Run(ApplicationManager*pManager)
{
	pManager->UpdateComponentsIndexes();
	vector<bool> visited;
	int size = pManager->GetComplistSize();
	visited.resize(size, false);
	int SimulationResult = 0;
	for (int i = 0; i < size; i++)
	{
		Component* Comp = pManager->GetComponent(i);
		if (Comp->getType() == Switch_)
			Comp->Operate();
		else Comp->SetOutPinStatus(FLOATING);
	}
	for (int i = 0; i < size; i++)
		if (pManager->GetComponent(i)->getType() == LED_)
			dfs(visited, pManager->GetComponent(i), i, SimulationResult, pManager);
	for (int i = 0; i < size; i++)
	{
		if (!visited[i] && pManager->GetComponent(i)->getType() != Switch_)
		{
			SimulationResult = 1;
			break;
		}
	}
	if (SimulationResult == 1)
	{
		pManager->GetOutput()->PrintMsg("Simulation Failed ... Floating Pins !!");
		pManager->GetOutput()->UpdateBuffer();
		return false;
	}
	if (SimulationResult == 2)
	{
		pManager->GetOutput()->PrintMsg("Simulation Failed ... Circuit contains feedback !!");
		pManager->GetOutput()->UpdateBuffer();
		return false;
	}
	return true;
}

STATUS Simulate::dfs(vector<bool>& visited,Component*&Comp, int index, int &result, ApplicationManager* pApp)
{

	//if (result)return FLOATING;
	if (Comp->GetOutPinStatus() != FLOATING)return Comp->GetOutPinStatus();
	if (visited[index]) { result = 2; return FLOATING; }
	visited[index] = true;
	for (int i = 0; i < Comp->getNumberofInPins(); i++)
	{
		if (!Comp->isInpinFloating(i))
			Comp->setInputPinStatus(STATUS(dfs(visited, pApp->GetComponent(Comp->getCompIndexConnectedToInPin(i)),
				Comp->getCompIndexConnectedToInPin(i), result,pApp)), i);
		else {
			result = 1; return FLOATING;
		}
	}
	Comp->Operate();
	return Comp->GetOutPinStatus();
}