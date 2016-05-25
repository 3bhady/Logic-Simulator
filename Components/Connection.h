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
	Connection( const GraphicsInfo &r_GfxInfo , BFSOut* outs , OutputPin *pSrcPin = NULL , InputPin *pDstPin = NULL );

	virtual void Operate( );	//Calculates the output according to the inputs
	virtual void Draw( Output* pOut );	//for each component to Draw itself

	void setSourcePin( OutputPin *pSrcPin );
	void setDestPin( InputPin *pDstPin );
	virtual OutputPin* getSourcePin( );
	virtual InputPin* getDestPin( );
	void Save( ofstream &fout );
	void Load( ifstream &fin );
	virtual pair<int, int>* GetInputPinCoordinates(pair<int, int>&x);//the function that gets the inputtpin coordinates
	virtual pair<int, int>& GetOutputPinCoordinates();//the function that gets the outputpin coordinates
	virtual InputPin* GetInputPin(pair<int, int> &x);//the function that returns pointer to an inputpin
	virtual OutputPin* GetOutputPin();//the function that returns pointer to an outputpin
	void bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx);//the function the determines the path of the conncetion
	bool isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1);
	BFSOut& get_path( );

	virtual STATUS GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual int getID();
	virtual bool ChangePath(ApplicationManager*);

	virtual void setInputPinStatus(STATUS s, int n);	//set status of Inputpin # n, to be used by connection class.
	virtual int getNumberofInPins();
	virtual bool isInpinFloating(int n);
	virtual bool isOutpinFloating();
	virtual int getCompIndexConnectedToInPin(int n);
	void SetOutPinStatus(STATUS s);
	virtual  int GetInputPinIndex(InputPin*DstPin);
	virtual void EraseComponent(ApplicationManager * pApp);//remove it from the grid
	virtual InputPin*GetInputPin(int) ;//the function that returns pointer to an inputpin
	virtual pair<int, int>*GetInputPinCoordinates(int);//the function that returns pointer to an inputpin

};
