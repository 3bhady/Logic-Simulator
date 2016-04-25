#pragma once

#include "Pin.h"
class Component; //Forward class declaration

class InputPin: public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
};

