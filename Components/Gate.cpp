#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut, GraphicsInfo in_Gfxinfo) :m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];

	inP = new pair<int, int>[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	switch (r_Inputs)
	{
	case 1:
		inP[0] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 30);
		break;
	case 2:
		inP[0] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 15);inP[1] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 45);
		break;
	case 3:
		inP[0] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 15);inP[2] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 45);
		inP[1] = make_pair(in_Gfxinfo.x1, in_Gfxinfo.y1 + 30);
		break;
	}
	outP = make_pair(in_Gfxinfo.x2, in_Gfxinfo.y1 + 30); //TODO
														 //Associate all input pins to this gate

	for (int i = 0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
	m_OutputPin.SetComponent(this);

}

pair<int, int>& Gate::get_OP()
{
	return outP;
}
pair<int, int>* Gate::get_INPC()
{
	for (int i = 0;i < m_Inputs;i++)if (m_InputPins[i].get_connection() == NULL)return &inP[i];
	return NULL;
}
OutputPin * Gate::get_Opin()
{
	return &m_OutputPin;
}
InputPin * Gate::get_INpin(pair<int, int>& x)
{
	int i, y55 = 10;
	for (i = 0;i < m_Inputs;i++)
		if (inP[i].first == x.first&&inP[i].second == x.second)
			y55 = i;
	if (y55 >= m_Inputs)return NULL;
	return &m_InputPins[y55];
}

