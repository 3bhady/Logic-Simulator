#include "Save.h"
#include<iomanip>
#include<fstream>
Save::Save(ApplicationManager*pApp):Action(pApp)
{
}


Save::~Save()
{
}

bool Save::ReadActionParameters()
{
	return true;
}

void Save::Execute()
{
string FileName=pManager->GetInput()->GetString(pManager->GetOutput());
string s = FileName + ".txt";
if (s == ".txt")
{
	pManager->GetOutput()->PrintMsg("you must enter a label to the file");
	return;
}
	ofstream fout(s);
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
