#include "Switch.h"



Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut) :m_OutputPin(r_FanOut)
{
	Type = Switch_;
	State = LOW;
	Width = UI.Switch_Width;
	Height = UI.Switch_Height;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1+15);
	m_OutputPin.SetComponent(this);
	switchID = ID++;
}


void Switch::Operate()
{
	m_OutputPin.setStatus(State);
}


// Draw switch
void Switch::Draw(Output* pOut, ApplicationManager* AppManger )
{
	//Call output class and pass switch drawing info to it.
	pOut->DrawSwitch(m_GfxInfo, State, highlighted,forbidden, UI.AppMode);
}


//returns status of outputpin
STATUS Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

//returns status of Inputpin 
STATUS Switch::GetInputPinStatus(int n = 1)
{
	return	FLOATING;
}
//Set status of the switch on or off
void Switch::set_state(STATUS x)
{
	State = x;
}
//return the switch status
STATUS Switch::get_state()
{
	return State;
}



void Switch::setInputPinStatus(STATUS s, int n)
{
	set_state(s);
}

pair<int, int>& Switch::GetOutputPinCoordinates()//the function that gets the outputpin coordinates
{
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1 + 15);
	if (m_OutputPin.CheckForAdd())
		return outP;
	else
		return FalsePoint;
}
pair<int, int>* Switch::GetInputPinCoordinates(pair<int, int> &Pair)//the function that gets the inputtpin coordinates
{

	return NULL;
}

OutputPin * Switch::GetOutputPin()//the function that returns pointer to an outputpin
{
	return &m_OutputPin;
}
InputPin * Switch::GetInputPin(pair<int, int> &x)
{

	return NULL;
}

int Switch::getNumberofInPins()
{
	return 0;
}

bool Switch::isInpinFloating(int n)
{
	return false;
}

bool Switch::isOutpinFloating()
{
	return (m_OutputPin.getStatus()==FLOATING);
}

int Switch::getCompIndexConnectedToInPin(int n)
{
	return -1;
}
int Switch::getID()
{
	return switchID;
}
int Switch::GetInputPinIndex(InputPin * DstPin)
{
	return 0;
}
InputPin * Switch::GetInputPin(int)
{
	return NULL;

}
void Switch::EraseConnections(ApplicationManager * pApp)
{
	m_OutputPin.EraseConnections(pApp);
}


void Switch::SetOutPinStatus(STATUS s)
{
	State = s;
}

void Switch::Save(ofstream & fout)
{
	fout << left << setw(15) << "SWITCH";
	fout << setw(15) << switchID;
	fout << setw(15) << get_label();
	fout << setw(15) << (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	fout << setw(15) << (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	fout << "\n";
}

void Switch::Load(ifstream & fin)
{
	int x, y;
	string label;
	fin >> switchID;
	fin >> label;
	set_label(label);
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.Switch_Width / 2;
	m_GfxInfo.x2 = m_GfxInfo.x1 + UI.Switch_Width;
	m_GfxInfo.y1 = y - UI.Switch_Height / 2;
	m_GfxInfo.y2 = m_GfxInfo.y1 + UI.Switch_Height;
}
Switch::~Switch()
{
}

pair<int, int>* Switch::GetInputPinCoordinates(int)
{
	return NULL;
}
