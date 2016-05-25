#include "TruthTable.h"
#include<cmath>
#include<iostream>
#include"Simulate.h"
#include<fstream>
#include<iomanip>
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
	for (int i = 0; i<pManager->GetComplistSize(); i++)
	{
		if (dynamic_cast<Switch*>(pManager->GetComponent(i)))
			SwitchCount++;
		if (dynamic_cast<LED*>(pManager->GetComponent(i)))
			LedCount++;
	}
	SwitchArr = new int[SwitchCount];
	int m = 0;
	for (int i = 0; i < pManager->GetComplistSize(); i++)
		if (dynamic_cast<Switch*>(pManager->GetComponent(i)))
		{
			SwitchArr[m] = pManager->GetComponent(i)->GetInputPinStatus(0);
			m++;
		}
	if (!Simulate::Run(pManager))
		return;
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
	for (int i = 0; i < RowsCount; i++)
	{
		int j = 0;
		for (int k = 0; k < pManager->GetComplistSize(); k++)
			if (dynamic_cast<Switch*>(pManager->GetComponent(k)))
			{
				pManager->GetComponent(k)->setInputPinStatus((STATUS)Arr[i][j], 0);
				j++;
			}
		Simulate::Run(pManager);
		j = 0;
		for (int k = 0; k < pManager->GetComplistSize(); k++)
			if (dynamic_cast<LED*>(pManager->GetComponent(k)))
			{
				Arr[i][j + SwitchCount] = (int)(pManager->GetComponent(k)->GetInputPinStatus(0));
				j++;
			}
	}
	
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

		
		for (int i = 0; i < RowsCount; i++)
		{
			for (int j = 0; j < LedCount; j++)
			{
				pManager->GetOutput()->DrawCellValue(j*ColumnWidth + SwitchCount*ColumnWidth, (i + 1)*RowWidth, Arr[i][j + SwitchCount]);
			}
		}
	}
	else
	{
		ofstream fout("Truth-Table.txt");
		fout << left;
		fout<<setw(5);
		for (int i = SwitchCount; i > 0; i--)
		{
			string order = "", s = "";
			stringstream ss;
			int x = (i - 1);
			ss << x;
			ss >> order;
			s = "S" + order;
			fout << s << setw(5);
		
		}
		for (int i = LedCount; i > 0; i--)
		{
			string order = "", s = "";
			stringstream ss;
			int x = (i - 1);
			ss << x;
			ss >> order;
			s = "Q" + order;
			fout << s << setw(5);
		}
		fout << endl;
		for (int i = 0; i < RowsCount; i++)
		{
			for (int j = 0; j < SwitchCount + LedCount;j++)
			{
				fout << Arr[i][j] << setw(5);
			}
			fout << endl;
		}
	}
		 m = 0;
		 for (int i = 0; i < pManager->GetComplistSize(); i++)
		if (dynamic_cast<Switch*>(pManager->GetComponent(i)))
		{
			pManager->GetComponent(i)->setInputPinStatus((STATUS)SwitchArr[m],0);
			m++;
		}
}

void TruthTable::undo()
{
}

void TruthTable::redo()
{
}
