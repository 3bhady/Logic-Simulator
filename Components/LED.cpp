#include "LED.h"
#include"Connection.h"

LED::LED(const GraphicsInfo &r_GfxInfo)//, pair<int, int> x)
{

	Type = LED_;

	// generate random number between 0 and 5
	// choosing a LED color

	stringstream sstream;
	srand(time(NULL));
	int randNum = rand() % 6;
	sstream << randNum;
	sstream >> colour;
	State = LOW;
	m_InputPin.setComponent(this);
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	Width = UI.LED_Width;
	Height = UI.LED_Height;
	inP = make_pair(m_GfxInfo.x1,m_GfxInfo.y1+30);
	LEDID = ID++;
}

pair<int, int>* LED::GetInputPinCoordinates(InputPin * InputP)
{
	inP = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		return &inP;
}


void LED::Operate()
{
	State = m_InputPin.getStatus();
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut, ApplicationManager* AppManger )
{
	//Call output class and pass led drawing info to it.
	pOut->DrawLED(m_GfxInfo, State, highlighted, forbidden, colour);
}

//returns status of outputpin
STATUS LED::GetOutPinStatus()
{
	return FLOATING;
}


//returns status of Inputpin #n
STATUS LED::GetInputPinStatus(int n = 1)
{
	return m_InputPin.getStatus();	//n is ignored as connection has only one input pin
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(STATUS s, int n = 1)
{
	m_InputPin.setStatus(s);
}


pair<int, int>& LED::GetOutputPinCoordinates()//the function that gets the outputpin coordinates
{

	return FalsePoint;
}
pair<int, int>* LED::GetInputPinCoordinates(pair<int, int> &Pair)//the function that gets the inputtpin coordinates
{

	inP = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
	if (m_InputPin.get_connection() == NULL)
		return &inP;
	return NULL;
}

OutputPin * LED::GetOutputPin()//the function that returns pointer to an outputpin
{
	return NULL;
}
InputPin * LED::GetInputPin(pair<int, int> &x)
{
	return &m_InputPin;

}

int LED::getNumberofInPins()
{
	return 1;
}

bool LED::isInpinFloating(int n)
{
	return (!m_InputPin.get_connection());
}

bool LED::isOutpinFloating()
{
	return false;
}

int LED::getCompIndexConnectedToInPin(int n)
{
	return	m_InputPin.get_connection()->getCompIndex();
}

void LED::SetOutPinStatus(STATUS s)
{
	setState(s);
}

InputPin * LED::GetInputPin(int index)
{
	if (index != 0)return NULL;
	return &m_InputPin;
}

pair<int, int>* LED::GetInputPinCoordinates(int index)
{
	if (index != 0)return NULL;
	return &inP;
}

void LED::setState(STATUS s)
{
	State = s;
}


int LED::getID()
{
	return LEDID;
}

int LED::GetInputPinIndex(InputPin * DstPin)
{
	return 1;
}
int LED::GetInputPinIndex(pair<int, int>& coordinates)
{
	inP = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
	if (inP.first == coordinates.first&&inP.second == coordinates.second)
		return 0;
	return -1;
}

void LED::EraseConnections(ApplicationManager * pApp)
{
	m_InputPin.Erase(pApp);
}


void LED::Save(ofstream & fout)
{
	fout << left << setw(15) << "LED";
	fout << setw(15) << LEDID;
	fout << setw(15) << get_label();
	fout << setw(15) << (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	fout << setw(15) << (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	fout << "\n";
}

void LED::Load(ifstream & fin)
{
	int x, y;
	string label;
	fin >> LEDID;
	fin >> label;
	set_label(label);
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.LED_Width / 2;
	//m_GfxInfo.x2 = x + UI.Gate_Width / 2;
	m_GfxInfo.x2 = m_GfxInfo.x1 + UI.LED_Width;
	m_GfxInfo.y1 = y - UI.LED_Height / 2;
	//m_GfxInfo.y2 = y + UI.Gate_Height / 2;
	m_GfxInfo.y2 = m_GfxInfo.y1 + UI.LED_Height;
}

LED::~LED()
{
}
