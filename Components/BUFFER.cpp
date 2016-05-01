#include "BUFFER.h"



BUFFER::BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	Type = Buff_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}
void BUFFER::Operate()
{
	if (m_InputPins[0].getStatus() == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws BUFFER
void BUFFER::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, Buff_, highlighted);
}

//returns status of outputpin
int BUFFER::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of The Inputpin 
int BUFFER::GetInputPinStatus(int n = 1)
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of the input pin ot HIGH or LOW
void BUFFER::setInputPinStatus(STATUS s, int n=1)
{
	m_InputPins[n - 1].setStatus(s);
}


BUFFER::~BUFFER()
{
}
