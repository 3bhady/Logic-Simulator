#pragma once
#include "Gate.h"
class NOT :
	public Gate
{
public:
	NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the not gate
	virtual void Draw(Output* pOut, ApplicationManager* AppManger = NULL);	//Draws NOT gate

	//virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n);	//returns status of the Inputpinif SWITCH, return -1

	//virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	~NOT();
};

