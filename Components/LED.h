#pragma once
#include "Component.h"
#include "Pins\OutputPin.h"
#include "Pins\InputPin.h"
#include <stdlib.h>
#include <time.h>
#include<string>
#include<fstream>
#include<iomanip>
class LED : public Component
{
	InputPin m_InputPin;	//The input pins of the LED
	STATUS State;			//The LED State .
	pair<int, int> inP;//inputpin coordinates
	string colour;			//colour of the LED
	int LEDID;
public:
	LED(const GraphicsInfo &r_GfxInfo);//, pair<int, int> x);
	virtual void Operate();	//Calculates the output of led
	virtual void Draw(Output* pOut);	//Draws led
	virtual STATUS GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	pair<int, int>& get_INPC();//the function which gets an inputpin coordinates
	InputPin* get_inputpin();
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual bool isOutpinFloating();
	void EraseComponent(ApplicationManager * pApp);
	virtual int getCompIndexConnectedToInPin(int n);
	virtual void SetOutPinStatus(STATUS s);
	void setState(STATUS s);
	//kero	
	//==================================================
	void Save(ofstream &fout);
	void Load(ifstream &fout);
	//=============================================
	~LED();
};
