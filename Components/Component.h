#pragma once

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class InputPin;
class OutputPin;
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool forbidden = false;
	bool highlighted = false;
	ComponentType Type;
	int Width;		//Width of the component
	int Height;		//Height of the component
	int compIndex;	//Index of Component in CompList
	static int ID;
public:
	Component();
	Component(const GraphicsInfo &r_GfxInfo);
	virtual ~Component();	//Destructor must be virtual

	virtual void Save(ofstream &fout) = 0;
	virtual void Load(ifstream &fout) = 0;
	virtual void Operate() = 0;					//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;		//for each component to Draw itself
	void  set_label(string);					//Set label of the component
	string get_label();							//Get label of the component
	virtual OutputPin* getSourcePin();
	virtual InputPin* getDestPin();
	static void setID(int id);
	virtual STATUS GetOutPinStatus() = 0;			//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1
	void AddConnection(BFSOut& xx, ApplicationManager * pApp);
	virtual void setInputPinStatus(STATUS s,int n) = 0;	//set status of Inputpin # n, to be used by connection class.
	virtual int getNumberofInPins() = 0;
	GraphicsInfo& get_GraphicInfo();
	void set_GraphicInfo(GraphicsInfo GFX);
	virtual void AddComponent(ApplicationManager * pApp);		//Add component in 2D array and don't push it in complist	
	virtual void DeleteComponent( ApplicationManager * pApp ); //completly delete it
	virtual void EraseComponent( ApplicationManager * pApp );//remove it from the grid
	virtual pair<int, int>* GetInputPinCoordinates(pair<int, int>&x) = 0;//the function that gets the inputtpin coordinates
	virtual pair<int, int>& GetOutputPinCoordinates() = 0;//the function that gets the outputpin coordinates
	virtual InputPin* GetInputPin(pair<int, int>&x) = 0;//the function that returns pointer to an inputpin
	virtual OutputPin* GetOutputPin() = 0;//the function that returns pointer to an outputpin
	void Highlight();			//Make the component highlighted
	void Unhighlight();			//Make the component unhighlighted
	void Forbid( );				//Makes the component forbidden and it appears red
	void Allow( );				//makes the component not forbidden
	void ChangeState();			//Change the component highlight state
	virtual InputPin*GetInputPin(int)=0;//the function that returns pointer to an inputpin
	virtual int GetInputPinIndex(pair<int, int> &coordinates) ;
	virtual pair<int, int>*GetInputPinCoordinates(int) = 0;//the function that returns pointer to an inputpin
	bool isSelected( );			//an indication to whether the component is selected or not
	virtual bool ChangePath(ApplicationManager*);
	ComponentType getType();    // returns the type of the component
	virtual void setCompIndex(int index);
	virtual int getCompIndex();
	virtual bool isInpinFloating(int n) = 0;
	virtual bool isOutpinFloating() = 0;
	virtual int getCompIndexConnectedToInPin(int n) = 0;
	virtual void SetOutPinStatus(STATUS s) = 0;
	virtual int getID() = 0;
	virtual  int GetInputPinIndex(InputPin*DstPin) = 0;
	virtual int GetWidth();
	virtual int GetHeight();
};

