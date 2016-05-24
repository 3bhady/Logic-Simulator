#include "InputPin.h"
#include"..\Connection.h"

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

void InputPin::Erase(ApplicationManager * Ptr)
{
	if (pCon == NULL)return;
	Connection* ptrconnection = pCon;
	pCon = NULL;
	ptrconnection->DeleteComponent(Ptr);

}

Connection* InputPin::get_connection()
{
	return pCon;
}

void InputPin::set_connection(Connection* x)
{
	pCon = x;
}

