#include "XOR3.h"



XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut, r_GfxInfo)
{
	Type = XOR3_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR3::Operate()
{
	if (CheckFloatingInPins())
		m_OutputPin.setStatus(FLOATING);
	else {
		if ((m_InputPins[0].getStatus() != m_InputPins[1].getStatus()))
			if (HIGH != m_InputPins[2].getStatus())
				m_OutputPin.setStatus(HIGH);
			else
				m_OutputPin.setStatus(LOW);
		else if (LOW != m_InputPins[2].getStatus())
			m_OutputPin.setStatus(HIGH);
		else
			m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut, ApplicationManager* AppManger)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, XOR3_, highlighted, forbidden);
}

/*
//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

*/
XOR3::~XOR3()
{
}
