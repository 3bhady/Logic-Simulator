#include "Switch.h"



Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut) :m_OutputPin(r_FanOut)
{
State = LOW;
m_InputPin.setComponent(this);

m_GfxInfo.x1 = r_GfxInfo.x1;
m_GfxInfo.y1 = r_GfxInfo.y1;
m_GfxInfo.x2 = r_GfxInfo.x2;
m_GfxInfo.y2 = r_GfxInfo.y2;
}


void Switch::Operate()
{
	if (State==HIGH)
		m_OutputPin.setStatus(m_InputPin.getStatus());
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws swtich
void Switch::Draw(Output* pOut)
{
	//Call output class and pass switch drawing info to it.
	pOut->DrawSwitch(m_GfxInfo, State, highlighted);
}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin 
int Switch::GetInputPinStatus(int n=1)
{
	return	-1;	//n starts from 1 but array index starts from 0.
}
//Set status of the switch on or off
void Switch::set_state(STATUS x)
{
	State = x;
}
//return the switch status
STATUS Switch::get_state()
{
	return State;
}

//Set status of an input pin ot HIGH or LOW
void Switch::setInputPinStatus( STATUS s, int n = 1)
{
	m_InputPin.setStatus(s);
}

Switch::~Switch()
{
}
