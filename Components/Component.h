#pragma once

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
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
	//kero
	//=================
	static int ID;
	//========================
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Save(ofstream &fout) = 0;
	virtual void Load(ifstream &fout) = 0;
	virtual void Operate() = 0;					//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;		//for each component to Draw itself
	void  set_label(string);					//Set label of the component
	string get_label();							//Get label of the component
	virtual STATUS GetOutPinStatus() = 0;			//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1
	void Component::AddConnection(BFSOut& xx, ApplicationManager * pApp);
	virtual void setInputPinStatus(STATUS s,int n) = 0;	//set status of Inputpin # n, to be used by connection class.
	virtual int getNumberofInPins() = 0;
	GraphicsInfo& get_GraphicInfo();
	void set_GraphicInfo(GraphicsInfo GFX);
	virtual void AddComponent(ApplicationManager * pApp);		//Add component in 2D array and don't push it in complist	
	virtual void DeleteComponent( ApplicationManager * pApp ); //completly delete it
	virtual void EraseComponent( ApplicationManager * pApp );//remove it from the grid
	void Highlight();			//Make the component highlighted
	void Unhighlight();			//Make the component unhighlighted
	void Forbid( );				//Makes the component forbidden and it appears red
	void Allow( );				//makes the component not forbidden
	void ChangeState();			//Change the component highlight state
	bool isSelected( );			//an indication to whether the component is selected or not
	ComponentType getType();    // returns the type of the component
	Component();
	virtual void setCompIndex(int index);
	virtual int getCompIndex();
	virtual bool isInpinFloating(int n) = 0;
	virtual int getCompIndexConnectedToInPin(int n) = 0;

	//Destructor must be virtual
	virtual ~Component();
};

