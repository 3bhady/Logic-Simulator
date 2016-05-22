#pragma once
#include <queue>
#include <vector>
#include "Component.h"
#include "Pins\InputPin.h"
#include "Pins\OutputPin.h"

using namespace std;
class Connection : public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	//int		DstPin;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	BFSOut outx;//the connection path
public:
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const GraphicsInfo &r_GfxInfo, BFSOut* outs, OutputPin *pSrcPin = NULL, InputPin *pDstPin = NULL);

	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself

	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();
	void Save(ofstream &fout);
	void Load(ifstream &fout);
	/*
	void bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx);//the function the determines the path of the conncetion
	bool isvalid(int x, int y, bool** vis, bool** ifc, bool** oth, int x0, int y0, int x2, int y2);//the function the determines whether a piont is valied or not
	*/
	BFSOut& get_path();
	void set_path(BFSOut);

	virtual STATUS GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(STATUS s, int n);	//set status of Inputpin # n, to be used by connection class.
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual int getCompIndexConnectedToInPin(int n);
	Component* DeleteConnection(ApplicationManager*);//remove all pointers of this connection from the 2-D array

};
