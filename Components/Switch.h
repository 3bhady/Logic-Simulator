#pragma once
#include "Component.h"
#include "Pins\InputPin.h"
#include "Pins\OutputPin.h"
class Switch :	public Component
{
	InputPin m_InputPin;	//The input pins of the Switch
	OutputPin m_OutputPin;	//The Switch output pin
	STATUS State;		//The Switch State .
public:
	Switch(const GraphicsInfo &r_GfxInfo, int);
	virtual void Operate();	//Calculates the output of switch
	virtual void Draw(Output* pOut);	//Draws switch

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	void set_state(STATUS);//Set status of the switch on or off
	STATUS get_state();//return the switch status
	virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	~Switch();
};

