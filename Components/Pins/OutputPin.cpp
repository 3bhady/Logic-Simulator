
#include "OutputPin.h"
#include "..\Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS : r_FanOut;	//set the fan out of the pin.
	m_Conn = 0;		//initially Pin is not connected to anything.
	
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

void OutputPin::EraseConnections(ApplicationManager* app)
{
	for (unsigned int i = 0;i < VOC.size();i++)
	{
		if (VOC[i] != NULL) {
			Connection* ptr = VOC[i];
			VOC[i] = NULL;
			ptr->DeleteComponent(app);
		}
	}
}

Connection * OutputPin::GetConnection(int x)
{
	return VOC[x];
}

void OutputPin::EraseConnection(Connection *x)
{
	int found = 1000;
	for (int i = 0;i < VOC.size();i++)
		if (VOC[i] == x)found = i;
	if (found != 1000) {
		m_Conn--;
		VOC.erase(VOC.begin() + found);
	}
}

vector<Connection*>& OutputPin::GetConnections()
{
	return VOC;
}

int OutputPin::GetNum()
{
	return m_Conn;
}

OutputPin::~OutputPin()
{

}

void OutputPin::SetComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* OutputPin::getComponent()
{
	return pComp;
}

int OutputPin::getCompIndex()
{
	return pComp->getCompIndex();
}
bool OutputPin::CheckForAdd()
{
	if (m_FanOut <= m_Conn)
		return false;
	else
		return true;

}

