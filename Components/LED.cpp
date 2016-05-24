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
	//inP = make_pair(x.first, x.second);

	State = LOW;
	m_InputPin.setComponent(this);
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	Width = UI.LED_Width;
	Height = UI.LED_Height;
	inP = make_pair(m_GfxInfo.x1,m_GfxInfo.y1+30);
	//kero
	//=========================
	LEDID = ID++;
	//======================
}


void LED::Operate()
{
	State = m_InputPin.getStatus();
}


// Function Draw
// Draws Led
void LED::Draw(Output* pOut)
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
void LED::EraseComponent(ApplicationManager * pApp)
{
	Component *** Arr = pApp->GetArr();
	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = NULL;
	m_InputPin.Erase(pApp);
	pApp->GetOutput()->DeleteGate(m_GfxInfo);
}



pair<int, int>& LED::get_INPC()
{
	inP = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);

	return inP;
}

InputPin * LED::get_inputpin()
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

void LED::setState(STATUS s)
{
	State = s;
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
	fin.ignore();
	fin >> label;
	set_label(label);
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.Gate_Width / 2;
	m_GfxInfo.x2 = x + UI.Gate_Width / 2;
	m_GfxInfo.y1 = y - UI.Gate_Height / 2;
	m_GfxInfo.y2 = y + UI.Gate_Height / 2;
}

LED::~LED()
{
}
