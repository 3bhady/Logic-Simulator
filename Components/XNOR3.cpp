#include "XNOR3.h"


XNOR3::XNOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut, r_GfxInfo)
{
	Type = XNOR3_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XNOR3::Operate()
{
	if (CheckFloatingInPins())
		m_OutputPin.setStatus(FLOATING);
	else {
		if ((m_InputPins[0].getStatus() == HIGH&&m_InputPins[1].getStatus() == HIGH) ||
			(m_InputPins[0].getStatus() == HIGH&&m_InputPins[2].getStatus() == HIGH) ||
			(m_InputPins[1].getStatus() == HIGH&&m_InputPins[2].getStatus() == HIGH))
			m_OutputPin.setStatus(HIGH);
		else
			m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws 3-input AND gate
void XNOR3::Draw(Output* pOut, ApplicationManager* AppManger )
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, XNOR3_, highlighted, forbidden);
}
/*
//returns status of outputpin
int XNOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR3::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}
*/

XNOR3::~XNOR3()
{
}
