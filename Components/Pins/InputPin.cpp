#include "InputPin.h"

InputPin::InputPin()
{
	pCon = NULL;
	pComp = NULL;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;

}

Connection* InputPin::get_connection()
{
	return pCon;
}

void InputPin::set_connection(Connection* x)
{
	pCon = x;
}
