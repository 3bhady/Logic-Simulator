
#include "OutputPin.h"
#include "..\Connection.h"

OutputPin::OutputPin(int r_FanOut)
{	//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS : r_FanOut;	//set the fan out of the pin.
//	pComp = NULL;
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if (m_Conn < m_FanOut)
	{
		VOC.push_back(r_Conn);	//add a new connection the the Vector of connections
		m_Conn++;
		return true;
	}

	return false;	//can't connect to any more connections
}

Connection * OutputPin::GetConnection(int x)
{
	return VOC[x];
}

void OutputPin::DeleteConnection(Connection *x)
{
	int llkj = 0;
	for (int i = 0;i < m_Conn;i++)
		if (VOC[i] == x)llkj = i;
	m_Conn--;
	VOC.erase(VOC.begin() + llkj);
}

vector<Connection*>& OutputPin::GetConnections()
{
	return VOC;
}

int OutputPin::GetNum()
{
	return m_Conn;
}

void OutputPin::SetComponent(Component *pCmp)
{
	pComp = pCmp;
}

Component* OutputPin::getComponent()
{
	return pComp;
}

int OutputPin::getCompIndex()
{
	return pComp->getCompIndex();
}
