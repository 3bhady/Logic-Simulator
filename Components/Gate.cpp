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

pair<int , int>& Gate::get_OP( )
{
	outP = make_pair(m_GfxInfo.x2, m_GfxInfo.y1 + 30);

	return outP;
}
pair<int , int>* Gate::get_INPC( )
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

	for (int i = 0;i < m_Inputs;i++)if (m_InputPins[i].get_connection() == NULL)return &inP[i];

	return NULL;
}
OutputPin * Gate::get_Opin( )
{
	return &m_OutputPin;
}
InputPin * Gate::get_INpin( pair<int , int>& x )
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

	int i, y55 = 10;
	for (i = 0;i < m_Inputs;i++)
		if (inP[i].first == x.first&&inP[i].second == x.second)

			y55 = i;
	if ( y55 >= m_Inputs )return NULL;
	return &m_InputPins[y55];
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
	string label;
	int ahbal;
	fin >> ahbal;
	fin >> label;
	set_label( label );
	fin >> x >> y;
	m_GfxInfo.x1 = x - UI.Gate_Width / 2;
	m_GfxInfo.x2 = x + UI.Gate_Width / 2;
	m_GfxInfo.y1 = y - UI.Gate_Height / 2;
	m_GfxInfo.y2 = y + UI.Gate_Height / 2;
}

STATUS Gate::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

STATUS Gate::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0;
}

void Gate::setInputPinStatus(STATUS s, int n)
{
	m_InputPins[n - 1].setStatus(s);
}

int Gate::getNumberofInPins()
{
	return m_Inputs;
}

bool Gate::isInpinFloating(int n)
{
	return (m_InputPins[n - 1].get_connection() == NULL);
}

bool Gate::isOutpinFloating()
{
	return (GetOutPinStatus() == FLOATING);
}

int Gate::getCompIndexConnectedToInPin(int n)
{
	return m_InputPins[n].get_connection()->getCompIndex();
}

Gate::~Gate()
{
	

	delete[] m_InputPins;
	delete[]inP;
}
void Gate::EraseComponent(ApplicationManager * pApp)
{
	Component *** Arr = pApp->GetArr();
	for (int j = m_GfxInfo.x1; j < m_GfxInfo.x2; j++)
		for (int i = m_GfxInfo.y1; i < m_GfxInfo.y2; i++)
			Arr[i][j] = NULL;
	for (int i = 0;i < m_Inputs;i++)
		m_InputPins[i].Erase(pApp);
	m_OutputPin.EraseConnections(pApp);
	pApp->GetOutput()->DeleteGate(m_GfxInfo);
}


