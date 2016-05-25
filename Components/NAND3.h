#pragma once
#include "Gate.h"
class NAND3 :
	public Gate
{
public:
	NAND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the NAND gate
	virtual void Draw(Output* pOut, ApplicationManager* AppManger = NULL);	//Draws 3-input gate

	//virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	//virtual void setInputPinStatus(STATUS s, int n);	//set status of Inputpin # n, to be used by connection class.
	~NAND3();
};

