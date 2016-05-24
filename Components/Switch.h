#pragma once
#include "Component.h"
#include "Pins\InputPin.h"
#include "Pins\OutputPin.h"
#include<string>
#include<fstream>
#include<iomanip>
class Switch : public Component
{
	OutputPin m_OutputPin;	//The Switch output pin
	pair<int, int>outP;//the coordinates of the output pin
	STATUS State;		//The Switch State .
	int switchID;
public:
	Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of switch
	virtual void Draw(Output* pOut);	//Draws switch

	virtual STATUS GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	void set_state(STATUS);//Set status of the switch on or off
	STATUS get_state();//return the switch status
	void setInputPinStatus(STATUS s, int n);
	virtual pair<int, int>* GetInputPinCoordinates(pair<int, int>&x);//the function that gets the inputtpin coordinates
	virtual pair<int, int>& GetOutputPinCoordinates();//the function that gets the outputpin coordinates
	virtual InputPin* GetInputPin(pair<int, int>&x);//the function that returns pointer to an inputpin
	virtual OutputPin* GetOutputPin();//the function that returns pointer to an outputpin
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual bool isOutpinFloating();
	virtual int getCompIndexConnectedToInPin(int n);
	void EraseComponent(ApplicationManager * pApp);

//kero
//===============================================
	void Save(ofstream &fout);
	void Load(ifstream &fout);
	//================================================
	~Switch();
};

