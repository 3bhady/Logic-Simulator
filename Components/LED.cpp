#include "LED.h"

LED::LED(const GraphicsInfo &r_GfxInfo, int r_FanOut) :m_OutputPin(r_FanOut) {
	S = LOW;
	m_InputPin.setComponent(this);

	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void LED::Operate()
{
	m_OutputPin.setStatus(m_InputPin.getStatus());
	if (m_InputPin.getStatus() == HIGH)S = HIGH;
	else S = LOW;
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut)
{
	//Call output class and pass led drawing info to it.
	pOut->DrawLED(m_GfxInfo, LOW);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n = 1)
{
	return m_InputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//return the switch status
STATUS LED::get_state()
{
	return S;
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(STATUS s, int n = 1)
{
	m_InputPin.setStatus(s);
}



LED::~LED()
{
}
