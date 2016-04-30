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
	
	bool highlighted = false;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;					//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;		//for each component to Draw itself
	void  set_label(string);					//Set label of the component
	string get_label();							//Get label of the component
	virtual int GetOutPinStatus() = 0;			//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) = 0;		//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(STATUS s,int n) = 0;	//set status of Inputpin # n, to be used by connection class.
	GraphicsInfo& get_GraphicInfo();
	virtual void AddComponent(ApplicationManager * pApp);
	virtual void DeleteComponent( ApplicationManager * pApp );
	void Highlight();			//Make the component highlighted
	void Unhighlight();			//Make the component unhighlighted
	void ChangeState();			//Change the component highlight state
	bool isSelected( );			//an indication to whether the component is selected or not
	Component();

	//Destructor must be virtual
	virtual ~Component();
};

