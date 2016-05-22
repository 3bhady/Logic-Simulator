#pragma once
#include "Gate.h"
class BUFFER :	public Gate
{
public:
	BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the buffer
	virtual void Draw(Output* pOut);	//Draws buffer

	//virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	//virtual int GetInputPinStatus(int n);	//returns status of the Inputpin if SWITCH, return -1

	//virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	~BUFFER();
};

