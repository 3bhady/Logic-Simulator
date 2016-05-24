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
	if (Run())
	{
		UI.AppMode = SIMULATION;
		for (unsigned int i = 0; i < pManager->GetCompList().size(); i++)
		{
			if (dynamic_cast<Gate*>(pManager->GetCompList()[i]))
				((Gate*)pManager->GetCompList()[i])->ShowPinsStatuses(pManager->GetOutput());
		}
	}
	else {
		for (unsigned int i = 0; i < pManager->GetCompList().size(); i++)
		{
			if (dynamic_cast<LED*>(pManager->GetCompList()[i]))
				(((LED*)pManager->GetCompList()[i]))->setState(LOW);
		}
	}
}

void Simulate::undo()
{
}

void Simulate::redo()
{
}


bool Simulate::Run()
{
	pManager->UpdateComponentsIndexes();
	vector<bool> visited;
	unsigned int size = pManager->GetCompList().size();
	visited.resize(size, false);
	int SimulationResult = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		if (pManager->GetCompList()[i]->getType() == Switch_)
			pManager->GetCompList()[i]->Operate();
		else pManager->GetCompList()[i]->SetOutPinStatus(FLOATING);
	}
	for (unsigned int i = 0; i < size; i++)
		if (pManager->GetCompList()[i]->getType() == LED_)
			dfs(visited, pManager->GetCompList(), i, SimulationResult);
	for (unsigned int i = 0; i < size; i++)
	{
		if (!visited[i] && pManager->GetCompList()[i]->getType() != Switch_)
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

STATUS Simulate::dfs(vector<bool>& visited, const vector<Component*>& Complist, int index, int &result)
{

	//if (result)return FLOATING;
	if (Complist[index]->GetOutPinStatus() != FLOATING)return Complist[index]->GetOutPinStatus();
	if (visited[index]) { result = 2; return FLOATING; }
	visited[index] = true;
	for (int i = 0; i < Complist[index]->getNumberofInPins(); i++)
	{
		if (!Complist[index]->isInpinFloating(i))
			Complist[index]->setInputPinStatus(STATUS(dfs(visited, Complist, Complist[index]->getCompIndexConnectedToInPin(i), result)), i);
		else {
			result = 1; return FLOATING;
		}
	}
	Complist[index]->Operate();
	return Complist[index]->GetOutPinStatus();
}