#include "Save.h"
#include<iomanip>
#include<fstream>
Save::Save(ApplicationManager*pApp):Action(pApp)
{
}


Save::~Save()
{
}

bool Save::ReadActionParameters(string s)
{
	return true;
}

void Save::Execute()
{
	ofstream fout("save-load.txt");
	//fout.open("save-load.txt");
	pManager->save(fout);
    //fout.close();
}

void Save::undo()
{
}

void Save::redo()
{
}
