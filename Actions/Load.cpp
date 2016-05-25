#include "Load.h"
#include"AddConnection.h"
Load::Load(ApplicationManager*pApp):Action(pApp)
{
}


Load::~Load()
{
}

bool Load::ReadActionParameters()
{
	return true;
}

void Load::Execute()
{

	
	//to do :clear the interface
	string FileName = pManager->GetInput()->GetString(pManager->GetOutput());
	string str = FileName + ".txt";
	if (str == "Truth-Table.txt")
		return;
	ifstream fin(str);
	if (fin.fail())
	{
		pManager->GetOutput()->PrintMsg("No such directory");
		pManager->GetOutput()->UpdateBuffer();
		return;
	}
	pManager->NewProject();
	//fin.open("save-load.txt");
	if (!fin.is_open())
		return;
	if (fin.eof())
		return;
	pManager->load(fin);
//	fin.close();
}

void Load::undo()
{
}

void Load::redo()
{
}
