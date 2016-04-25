#include "NAND3.h"



NAND3::NAND3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NAND3::Operate()
{
	if (m_InputPins[0].getStatus() == HIGH&&m_InputPins[1].getStatus() == HIGH&&m_InputPins[2].getStatus() == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 3-input NAND gate
void NAND3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawGate(m_GfxInfo, ITM_NAND3);
}

//returns status of outputpin
int NAND3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND3::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

NAND3::~NAND3()
{
}
