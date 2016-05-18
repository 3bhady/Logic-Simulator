#include "Switch.h"



Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut, pair<int, int> x) :m_OutputPin(r_FanOut)
{
	Type = Switch_;
	State = LOW;

	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	outP = make_pair(x.first, x.second);
}


void Switch::Operate()
{

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
int Switch::GetInputPinStatus(int n = 1)
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

OutputPin * Switch::get_OPP()
{
	return &m_OutputPin;
}

void Switch::setInputPinStatus(STATUS s, int n)
{
}



pair<int, int> Switch::get_OP()
{
	return outP;
}

Switch::~Switch()
{
}
