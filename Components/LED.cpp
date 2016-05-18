#include "LED.h"

LED::LED(const GraphicsInfo &r_GfxInfo, pair<int, int> x) {

	Type = LED_;
	// generate random number between 0 and 5
	// choosing a LED color

	stringstream sstream;
	srand(time(NULL));
	int randNum = rand() % 6;
	sstream << randNum;
	sstream >> colour;
	inP = make_pair(x.first, x.second);

	State = LOW;
	m_InputPin.setComponent(this);
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void LED::Operate()
{

	if (m_InputPin.getStatus() == HIGH)State = HIGH;
	else State = LOW;
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut)
{
	//Call output class and pass led drawing info to it.
	pOut->DrawLED(m_GfxInfo, HIGH, highlighted, colour);
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
	return State;
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(STATUS s, int n = 1)
{
	m_InputPin.setStatus(s);
}

pair<int, int> LED::get_INPC()
{
	return inP;
}

InputPin * LED::get_inputpin()
{
	return &m_InputPin;
}



LED::~LED()
{
}
