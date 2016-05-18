#pragma once
#include "Component.h"
#include "Pins\InputPin.h"
#include "Pins\OutputPin.h"
class Switch : public Component
{
	OutputPin m_OutputPin;	//The Switch output pin
	pair<int, int>outP;//the coordinates of the output pin
	STATUS State;		//The Switch State .
public:
	Switch(const GraphicsInfo &r_GfxInfo, int, pair<int, int>);
	virtual void Operate();	//Calculates the output of switch
	virtual void Draw(Output* pOut);	//Draws switch

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	void set_state(STATUS);//Set status of the switch on or off
	STATUS get_state();//return the switch status
	OutputPin* get_OPP();
	void setInputPinStatus(STATUS s, int n);
	virtual pair<int, int> get_OP();//the function that gets the outputpin coordinates
	~Switch();
};

