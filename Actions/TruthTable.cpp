#include "TruthTable.h"
#include<cmath>
#include<iostream>
using namespace std;
TruthTable::TruthTable(ApplicationManager*pApp):Action(pApp)
{
}


TruthTable::~TruthTable()
{
}



bool TruthTable::ReadActionParameters()
{
	return false;
}

void TruthTable::Execute()
{
	int SwitchCount = 0, LedCount=0;
	for (int i = 0; i<pManager->GetCompList().size(); i++)
	{
		if (dynamic_cast<Switch*>(pManager->GetCompList()[i]))
			SwitchCount++;
		if (dynamic_cast<LED*>(pManager->GetCompList()[i]))
			LedCount++;
	}
	int RowsCount = (int)pow(2, SwitchCount);
	Arr = new int*[RowsCount];
	for (int i = 0; i < RowsCount; i++)
		Arr[i] = new int[SwitchCount+LedCount];

	//making combination of Values
	int zerocount = 0;
	int onecount = 0;
	int divisor = 2;

	for (int j = 0; j < SwitchCount; j++)
	{
		for (int i = 0; i < RowsCount; i++)
		{
			if (zerocount < RowsCount / divisor)
			{
				Arr[i][j] = 0;
				zerocount++;
			}
			else if(onecount < RowsCount / divisor)
			{
				Arr[i][j] = 1;
				onecount++;
			}
			if (onecount == RowsCount / divisor)
			{
				 zerocount = 0;
				 onecount = 0;
			}
			
		}
	
		divisor *= 2;
	}

/*	for (int i = 0; i < RowsCount; i++)
	{
		for (int j = 0; j < SwitchCount ; j++)
			cout << Arr[i][j];
		cout << endl;
	}*/

	if (SwitchCount < 5)
	{
		pManager->GetOutput()->CreateTruthTableWindow(pow(2, SwitchCount), SwitchCount + LedCount, ColumnWidth, RowWidth, StartX, StartY);
		pManager->GetOutput()->DrawTruthTable(SwitchCount, LedCount, pow(2, SwitchCount), SwitchCount + LedCount, ColumnWidth, RowWidth);
		for (int i = 0; i < RowsCount; i++)
		{
			for (int j = 0; j < SwitchCount; j++)
			{
				int value = Arr[i][j];
				pManager->GetOutput()->DrawCellValue((j)*ColumnWidth + 2, (i + 1)*RowWidth + 2, value);
			}
		}
	}
}

void TruthTable::undo()
{
}

void TruthTable::redo()
{
}
