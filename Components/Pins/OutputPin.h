#pragma once

/*class OutputPin
---------------
An output pin obtains its value as a result of calculating the outputs of
a component. The output pin propagates its value immediately to the associated connections
*/

#include "Pin.h"
#include<algorithm>
class Connection;	//Forward class declartion
class Component;//Forward class declartion

using namespace std;

class OutputPin : public Pin	//inherited from class Pin
{
private:
	//Vector of connections (poniters) to be connected to that OutputPin
	vector<Connection*> VOC;
	int m_FanOut;	//Maximum No. of connections connected to that output pin (depends on the component)
	int m_Conn;		//Actual No. of connections connected to that output pin
	Component* pComp;

public:
	OutputPin(int r_FanOut);
	bool CheckForAdd();//check if you can add a new connection
	bool ConnectTo(Connection *r_Conn);	//connect to a new connection
	void EraseConnections(ApplicationManager*);
	vector<Connection*>& GetConnections();//return the vector of connections
	int GetNum();//return the Actual No. of connections connected to that output pin.
	~OutputPin();
	Component* getComponent();	//returns the component of this pin
	int getCompIndex();	//returns the index of the component of this pin

	Connection* GetConnection(int);//return a connection
	void EraseConnection(Connection*);
	void SetComponent(Component *pCmp);

};

