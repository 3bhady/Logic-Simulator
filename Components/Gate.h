#pragma once
/*
Class Gate
-----------
- Base class for all types of gates
- Each gate has n inputs pins and one output pin
*/


#include "Pins\OutputPin.h"
#include "Pins\InputPin.h"
#include "Component.h"
#include<iomanip>
#include<iostream>
#include<fstream>
using namespace std;
class Gate :public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	pair<int , int>* inP;//Array of input pins coordinates
	pair<int , int>outP;//the coordinates of the output pin
	int m_Inputs;		//No. of input pins of that Gate.
	int r_Inputs;		//No. of active input pins of that Gate.
	int gateID;
public:
	Gate( int r_Inputs , int r_FanOut , GraphicsInfo x );
	virtual pair<int, int>* GetInputPinCoordinates(pair<int, int>&x);//the function that gets the inputtpin coordinates
	virtual pair<int, int>& GetOutputPinCoordinates();//the function that gets the outputpin coordinates
	virtual InputPin* GetInputPin(pair<int, int>&x);//the function that returns pointer to an inputpin
	virtual OutputPin* GetOutputPin();//the function that returns pointer to an outputpin
	virtual void EraseComponent(ApplicationManager * pApp);//remove it from the grid
													  //kero
													  //==================================================

	void Save( ofstream &fout );
	void Load( ifstream &fin );
	virtual STATUS GetOutPinStatus();
	virtual STATUS GetInputPinStatus(int n);
	virtual void setInputPinStatus(STATUS s, int n);
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual bool isOutpinFloating();
	virtual int getCompIndexConnectedToInPin(int n);
	virtual InputPin*GetInputPin(int);//the function that returns pointer to an inputpin
	virtual void ShowPinsStatuses(Output* pOut);
	virtual bool CheckFloatingInPins();
	virtual void SetOutPinStatus(STATUS s);
	virtual pair<int, int>*GetInputPinCoordinates(int);//the function that returns pointer to an inputpin
	virtual int GetInputPinIndex(pair<int, int>& coordinates);

	~Gate();
};
