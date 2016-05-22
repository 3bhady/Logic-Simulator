#pragma once

#include "Pin.h"
class Component; //Forward class declaration
class Connection;	//Forward class declartion
class InputPin : public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	Connection* pCon;//pointer to the Connection witch this pin is connected to.

public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this pin
	Connection* get_connection();//returns the Connection witch this pin is connected to.
	void set_connection(Connection*);//set the connection 
};
