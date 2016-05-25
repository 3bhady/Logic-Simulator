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
	virtual pair<int, int>* GetInputPinCoordinates(InputPin* InputP);//the function that gets the inputtpin coordinates
	virtual void Operate();	//Calculates the output of led
	virtual void Draw(Output* pOut, ApplicationManager* AppManger = NULL);	//Draws led
	virtual STATUS GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n);	//returns status of the Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(STATUS s, int n);	//set status of the Inputpin, to be used by connection class.
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual bool isOutpinFloating();
	void EraseComponent(ApplicationManager * pApp);
	virtual int getCompIndexConnectedToInPin(int n);
	virtual pair<int, int>* GetInputPinCoordinates(pair<int, int>&x);//the function that gets the inputtpin coordinates
	virtual pair<int, int>& GetOutputPinCoordinates();//the function that gets the outputpin coordinates
	virtual InputPin* GetInputPin(pair<int, int>&x);//the function that returns pointer to an inputpin
	virtual OutputPin* GetOutputPin();//the function that returns pointer to an outputpin
	virtual void SetOutPinStatus(STATUS s);
	virtual InputPin*GetInputPin(int);//the function that returns pointer to an inputpin
	virtual pair<int, int>*GetInputPinCoordinates(int);//the function that returns pointer to an inputpin
	void setState(STATUS s);

	virtual int getID();
	virtual  int GetInputPinIndex(InputPin*DstPin);
	virtual int GetInputPinIndex(pair<int, int>& coordinates);


	//kero	
	//==================================================
	void Save(ofstream &fout);
	void Load(ifstream &fout);
	//=============================================
	~LED();
};
