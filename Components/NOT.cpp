#include "NOT.h"



NOT::NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	Type = INV_;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}
void NOT::Operate()
{
	if (m_InputPins[0].getStatus() == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws NOT gate
void NOT::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo,INV_, highlighted);
}

//returns status of outputpin
int NOT::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of The Inputpin 
int NOT::GetInputPinStatus(int n=1)
{
	return m_InputPins->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOT::setInputPinStatus(STATUS s, int n=1)
{
	m_InputPins->setStatus(s);
}


NOT::~NOT()
{
}
