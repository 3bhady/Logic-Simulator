#include "Switch.h"



Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut) :m_OutputPin(r_FanOut)
{
	Type = Switch_;
	State = FLOATING;
	Width = UI.LED_Width;
	Height = UI.LED_Height;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1 + 15);
	m_OutputPin.SetComponent(this);

	//kero
	//========================
	switchID = ID++;
	//==============================
}


void Switch::Operate()
{
	m_OutputPin.setStatus(State);
}


// Draw switch
void Switch::Draw(Output* pOut)
{
	//Call output class and pass switch drawing info to it.
	pOut->DrawSwitch(m_GfxInfo, State, forbidden, highlighted, UI.AppMode);
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

OutputPin * Switch::get_OPP()
{
	return &m_OutputPin;
}

void Switch::setInputPinStatus(STATUS s, int n)
{

}

pair<int, int>& Switch::get_OP()
{
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1 + 15);
	return outP;
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
void Switch::EraseComponent(ApplicationManager * pApp)
{
	Component *** Arr = pApp->GetArr();
	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = NULL;
	m_OutputPin.EraseConnections(pApp);
	pApp->GetOutput()->DeleteGate(m_GfxInfo);
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
	fin.ignore();
	fin >> label;
	set_label(label);
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.Gate_Width / 2;
	m_GfxInfo.x2 = x + UI.Gate_Width / 2;
	m_GfxInfo.y1 = y - UI.Gate_Height / 2;
	m_GfxInfo.y2 = y + UI.Gate_Height / 2;
}
Switch::~Switch()
{
}
