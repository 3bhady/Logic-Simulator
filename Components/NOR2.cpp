#include "NOR2.h"



NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut, r_GfxInfo)
{
	Type = NOR2_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR2::Operate()
{
	if (CheckFloatingInPins())
		m_OutputPin.setStatus(FLOATING);
	else {
		if (m_InputPins[0].getStatus() == HIGH || m_InputPins[1].getStatus() == HIGH)
			m_OutputPin.setStatus(LOW);
		else
			m_OutputPin.setStatus(HIGH);
	}
}


// Function Draw
// Draws 2-input NOR gate
void NOR2::Draw(Output* pOut, ApplicationManager* AppManger)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, NOR2_, highlighted, forbidden);
}

/*
//returns status of outputpin
int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

*/

NOR2::~NOR2()
{
}
