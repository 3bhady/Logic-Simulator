#include "XOR2.h"



XOR2::XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut, r_GfxInfo)
{
	Type = XOR2_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR2::Operate()
{
	if (CheckFloatingInPins())
		m_OutputPin.setStatus(FLOATING);
	else {
		if (m_InputPins[0].getStatus() != m_InputPins[1].getStatus())
			m_OutputPin.setStatus(HIGH);
		else
			m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output* pOut, ApplicationManager* AppManger)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, XOR2_, highlighted, forbidden);
}

/*
//returns status of outputpin
int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

*/


XOR2::~XOR2()
{
}
