#include "XNOR2.h"



XNOR2::XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut)
{
	Type = XNOR2_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XNOR2::Operate()
{
	if (m_InputPins[0].getStatus() == m_InputPins[1].getStatus())
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input XNOR gate
void XNOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, XNOR2_, highlighted,forbidden);
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

XNOR2::~XNOR2()
{
}
