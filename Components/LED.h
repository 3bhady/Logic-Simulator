#pragma once
#include "Component.h"
#include "Pins\OutputPin.h"
#include "Pins\InputPin.h"

class LED : public Component
{
	InputPin m_InputPin;	//The input pins of the led
	OutputPin m_OutputPin;	//The led output pin
	STATUS State;		//The Switch State .
public:
	LED(const GraphicsInfo &r_GfxInfo, int);
	virtual void Operate();	//Calculates the output of led
	virtual void Draw(Output* pOut);	//Draws led
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	STATUS get_state();//return the led status
	virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	~LED();
};
