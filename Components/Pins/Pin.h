#pragma once

#include "..\..\Defs.h"
#include "..\..\ApplicationManager.h"
class Pin
{
protected:
	STATUS m_Status;	//Status of the Pin
public:
	Pin();
	void setStatus(STATUS r_Status);
	STATUS getStatus();
};