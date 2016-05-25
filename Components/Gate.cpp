#include "Gate.h"
#include"Connection.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate( int r_Inputs , int r_FanOut , GraphicsInfo in_Gfxinfo ) :m_OutputPin( r_FanOut )
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];

	inP = new pair<int , int>[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	switch (m_Inputs)
	{
	case 1:
		inP[0] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 30 );
		break;
	case 2:
		inP[0] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 15 ); inP[1] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 45 );
		break;
	case 3:
		inP[0] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 15 ); inP[2] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 45 );
		inP[1] = make_pair( in_Gfxinfo.x1 , in_Gfxinfo.y1 + 30 );
		break;
	}
	outP = make_pair( in_Gfxinfo.x2 , in_Gfxinfo.y1 + 30 ); //TODO
															//Associate all input pins to this gate

	for (int i = 0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
	Width = UI.Gate_Width;
	Height = UI.Gate_Height;
	m_OutputPin.SetComponent(this);
	//m_OutputPin = FLOATING;

	//kero
	//===========================
	gateID = ID++;
	//=======================
}

pair<int, int>& Gate::GetOutputPinCoordinates()//the function that gets the outputpin coordinates
{
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1 + 30);
	if (m_OutputPin.CheckForAdd())
		return outP;
	else
		return FalsePoint;
}
pair<int, int>* Gate::GetInputPinCoordinates(pair<int, int> &Pair)//the function that gets the inputtpin coordinates
{
	switch (m_Inputs)
	{
	case 1:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	case 2:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		break;
	case 3:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[2] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	}
	for (int i = 0;i < m_Inputs;i++)
		if (inP[i].first == Pair.first&&inP[i].second == Pair.second&&m_InputPins[i].get_connection() == NULL) return &inP[i];
	for (int i = 0;i < m_Inputs;i++)if (m_InputPins[i].get_connection() == NULL)return &inP[i];

	return NULL;
}

OutputPin * Gate::GetOutputPin()//the function that returns pointer to an outputpin
{
	return &m_OutputPin;
}
InputPin * Gate::GetInputPin(pair<int, int> &x)
{
	switch (m_Inputs)
	{
	case 1:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	case 2:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		break;
	case 3:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[2] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	}

	int i, found = 10;
	for (i = 0;i < m_Inputs;i++)
		if (inP[i].first == x.first&&inP[i].second == x.second)
			found = i;
	if (found >= m_Inputs)return NULL;
	return &m_InputPins[found];
}

void Gate::Save(ofstream & fout)

{
	string str;
	switch ( Type )
	{
	case AND2_: {str = "AND2"; break; }
	case OR2_: {str = "OR2"; break; }
	case Buff_: {str = "BUFFER"; break; }
	case INV_: {str = "INVERTER"; break; }
	case NAND2_: {str = "NAND2"; break; }
	case NOR2_: {str = "NOR2"; break; }
	case XOR2_: {str = "XOR2"; break; }
	case XNOR2_: {str = "XNOR2"; break; }
	case AND3_: {str = "AND3"; break; }
	case OR3_: {str = "OR3"; break; }
	case NAND3_: {str = "NAND3"; break; }
	case NOR3_: {str = "NOR3"; break; }
	case XOR3_: {str = "XOR3"; break; }
	case XNOR3_: {str = "XNOR3"; break; }
	default:
		break;
	}
	fout << left << setw( 15 ) << str;
	fout << setw( 15 ) << gateID;
	fout << setw( 15 ) << get_label( );
	fout << setw( 15 ) << (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	fout << setw( 15 ) << (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	fout << "\n";
}

void Gate::Load( ifstream & fin )
{
	int x , y;

	string GateLabel;
	int ahbal;
	fin >> ahbal;
	fin >> GateLabel;
	set_label( GateLabel );
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.Gate_Width / 2;
	//m_GfxInfo.x2 = x + UI.Gate_Width / 2;
	m_GfxInfo.x2 = m_GfxInfo.x1 + UI.Gate_Width;
	m_GfxInfo.y1 = y - UI.Gate_Height / 2;
	//m_GfxInfo.y2 = y + UI.Gate_Height / 2;
	m_GfxInfo.y2 = m_GfxInfo.y1 + UI.Gate_Height;
}

STATUS Gate::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

STATUS Gate::GetInputPinStatus(int n)
{
	return m_InputPins[n].getStatus();
}

void Gate::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n].setStatus(s);
}

int Gate::getNumberofInPins()
{
	return m_Inputs;
}

bool Gate::isInpinFloating(int n)
{
	return (!m_InputPins[n].get_connection());
}

bool Gate::isOutpinFloating()
{
	return (GetOutPinStatus() == FLOATING);
}

int Gate::getCompIndexConnectedToInPin(int n)
{
	return m_InputPins[n].get_connection()->getCompIndex();
}


int Gate::getID()
{
	return gateID;
}

int Gate::GetInputPinIndex(InputPin*DstPin)
{
	int pinIndex = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].get_connection() == DstPin->get_connection())
			break;
		pinIndex++;
	}
	return pinIndex + 1;
		
}



InputPin * Gate::GetInputPin(int index)
{
	if (index >= r_Inputs)
		return NULL;
	else return &m_InputPins[index];
}

void Gate::ShowPinsStatuses(Output* pOut)
{
	for (int i = 0; i < m_Inputs; i++)
		pOut->DrawPinStatus(m_InputPins[i].getStatus(), inP[i].first, inP[i].second);
	pOut->DrawPinStatus(m_OutputPin.getStatus(), outP.first-5, outP.second);
}

bool Gate::CheckFloatingInPins()
{
	for (int i = 0; i < m_Inputs; i++)
		if (m_InputPins[i].getStatus()==FLOATING)return true;
	return false;
}

void Gate::SetOutPinStatus(STATUS s)
{
	m_OutputPin.setStatus(s);
}

pair<int, int>* Gate::GetInputPinCoordinates(int index)
{
	if (index >= r_Inputs)
		return NULL;
	else return &inP[index];
}

int Gate::GetInputPinIndex(pair<int, int> &coordinates)
{
	switch (m_Inputs)
	{
	case 1:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	case 2:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		break;
	case 3:
		inP[0] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 15);inP[2] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 45);
		inP[1] = make_pair(m_GfxInfo.x1, m_GfxInfo.y1 + 30);
		break;
	}

	
	for (int i = 0;i < m_Inputs;i++)
		if (inP[i].first == coordinates.first&&inP[i].second == coordinates.second)
			return i;
	return -1;
}


Gate::~Gate()
{
	

	delete[] m_InputPins;
	delete[]inP;
}
void Gate::EraseComponent(ApplicationManager * pApp)
{
	pApp->EraseComponent(m_GfxInfo);
	for (int i = 0;i < m_Inputs;i++)
		m_InputPins[i].Erase(pApp);
	m_OutputPin.EraseConnections(pApp);
	pApp->GetOutput()->DeleteGate(m_GfxInfo);
}


