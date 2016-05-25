#include "Connection.h"

Connection::Connection( const GraphicsInfo &r_GfxInfo , BFSOut* outs , OutputPin *pSrcPin , InputPin *pDstPin ) :Component( r_GfxInfo )

{
	outx = *outs;
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}
void Connection::setSourcePin( OutputPin *pSrcPin )
{
	SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin( )
{
	return SrcPin;
}


void Connection::setDestPin( InputPin *pDstPin )
{
	DstPin = pDstPin;
}

InputPin* Connection::getDestPin( )
{
	return DstPin;
}

void Connection::Save( ofstream & fout )
{
}

void Connection::Load( ifstream & fout )
{
}


void Connection::Operate( )
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus( ( STATUS )SrcPin->getStatus( ) );

}

void Connection::Draw( Output* pOut )
{

	pOut->DrawConnection( m_GfxInfo , outx , this , highlighted );

}
pair<int, int>&Connection::GetOutputPinCoordinates()//the function that gets the outputpin coordinates
{

	return FalsePoint;
}
pair<int, int>* Connection::GetInputPinCoordinates(pair<int, int> &Pair)//the function that gets the inputtpin coordinates
{

	return NULL;
}

OutputPin * Connection::GetOutputPin()//the function that returns pointer to an outputpin
{
	return NULL;
}
InputPin * Connection::GetInputPin(pair<int, int> &x)
{
	return NULL;
}
BFSOut& Connection::get_path( )
{
	return outx;
}

STATUS Connection::GetOutPinStatus()	//returns status of outputpin
{
	return DstPin->getStatus( );
}


STATUS Connection::GetInputPinStatus(int n = 1)	//returns status of Inputpin #n
{
	return SrcPin->getStatus( );	//n is ignored as connection has only one input pin (src pin)
}

void Connection::setInputPinStatus( STATUS s , int n = 1 )
{
	SrcPin->setStatus( s );
}

int Connection::getNumberofInPins()
{
	return 1;
}

bool Connection::isInpinFloating(int n)
{
	return false;
}

bool Connection::isOutpinFloating()
{
	return (!DstPin->get_connection());
}

int Connection::getCompIndexConnectedToInPin(int n)
{
	return SrcPin->getCompIndex();
}

void Connection::SetOutPinStatus(STATUS s)
{
	DstPin->setStatus(s);
}


void Connection::EraseComponent(ApplicationManager * pApp)
{
	//Component *** Arr = pApp->GetArr();
	int a = m_GfxInfo.x2, b = m_GfxInfo.y2;
	while (true)
	{
		if (a == m_GfxInfo.x1 &&b == m_GfxInfo.y1)break;
		int c = a;int d = b;
		int x = a;
		a = outx.arr[a][b].first, b = outx.arr[x][b].second;
		if (a == c) {
			if (d > b) {
				for (int i = b - 5;i <= d - 5;i++)
					if (pApp->GetComponent(i,a) == this) {
						for (int j = a; j < a + 5; j++)if (pApp->GetComponent(i, j) == this)pApp->PointToNull(i, j);
					}
			}
			else
				for (int i = d - 5;i <= b - 5;i++)
					if (pApp->GetComponent(i, a) == this) {

						for (int j = a; j < a + 5; j++)if (pApp->GetComponent(i, j) == this)pApp->PointToNull(i, j);
					}
		}
		if (b == d) {
			if (a > c)
				for (int i = c;i <= a;i++) {
					if (pApp->GetComponent(b, i) == this) {
						for (int j = b - 7; j < b + 1; j++)if (pApp->GetComponent(j, i) == this)pApp->PointToNull(j, i);
					}
				}
			else
				for (int i = a;i <= c;i++)
					if (pApp->GetComponent(b, i) == this) {
						for (int j = b - 7; j < b + 1; j++)if (pApp->GetComponent(j, i) == this)pApp->PointToNull(j, i);
					}

		}
	}
	
	/*
	for (int i = 0; i < 780; i++)
		for (int j = 0; j < 1400; j++)
			if (pApp->GetArr()[i][j] == this)
				pApp->GetArr()[i][j] = NULL;*/
	this->getSourcePin()->EraseConnection(this);
	this->getDestPin()->set_connection(NULL);
	
}