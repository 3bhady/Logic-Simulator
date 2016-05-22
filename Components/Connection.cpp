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
/*
bool Connection::isvalid(int x, int y, bool** vis, bool** ifc, bool** oth, int x0, int y0, int x2, int y2)
{
if (x <1335 && y <630)
if (x >= 0 && y >= 0) {
if (x == x2&&y == y2)return true;
if (oth[y][x])return false;
if (vis[y][x] == 0)
if (ifc[y][x] == 0)  return true;
else if (ifc[y0][x0])return false;else return true;
}
return false;
}
void Connection::bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx)
{
bool** vis = new bool*[780];for (int i = 0;i < 780;i++)vis[i] = new bool[1400];
for (int i = 0;i < 780;i++)for (int j = 0;j < 780;j++)vis[i][j] = false;
bool** ifc = new bool*[780];for (int i = 0;i < 780;i++)ifc[i] = new bool[1400];
bool** oth = new bool*[780];for (int i = 0;i < 780;i++)oth[i] = new bool[1400];
for (int i = 0;i < 780;i++)
for (int j = 0;j < 1400;j++) {
if (ifc[i][j] != NULL)
if (dynamic_cast<Connection*>(a[i][j])) { ifc[i][j] = 1;oth[i][j] = 0; }
else { ifc[i][j] = 0;oth[i][j] = 1; }
else { ifc[i][j] = 0;oth[i][j] = 0; }
}
queue< pair<int, int> > qu;
qu.push(make_pair(x1, y1));
while (!qu.empty())
{
pair<int, int> pr = qu.front();
vis[pr.first][pr.second] = 1;
qu.pop();
if (isvalid(pr.first + 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2))
{
qu.push(make_pair(pr.first + 15, pr.second));
outx.arr[pr.first + 15][pr.second] = make_pair(pr.first, pr.second);
vis[pr.first + 15][pr.second] = 1;
if (qu.back().first == x2 && qu.back().second == y2)
break;
}
if (isvalid(pr.first, pr.second + 15, vis, ifc, oth, pr.first, pr.second, x2, y2))
{
qu.push(make_pair(pr.first, pr.second + 15));
outx.arr[pr.first][pr.second + 15] = make_pair(pr.first, pr.second);
vis[pr.first][pr.second + 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
break;
}
if (isvalid(pr.first - 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2))
{
qu.push(make_pair(pr.first - 15, pr.second));
outx.arr[pr.first - 15][pr.second] = make_pair(pr.first, pr.second);
vis[pr.first - 15][pr.second] = 1;	if (qu.back().first == x2 && qu.back().second == y2)
break;
}
if (isvalid(pr.first, pr.second - 15, vis, ifc, oth, pr.first, pr.second, x2, y2))
{
qu.push(make_pair(pr.first, pr.second - 15));
outx.arr[pr.first][pr.second - 15] = make_pair(pr.first, pr.second);
vis[pr.first][pr.second - 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
break;
}
}

if (vis[y2][x2])outx.check = true;else outx.check = false;
for (int i = 0;i < 780;i++) { delete[]vis[i];delete[]ifc[i];delete[]oth[i]; }
delete[]vis;delete[]ifc;delete[]oth;
}
*/
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
	return (DstPin->get_connection()==NULL);
}

int Connection::getCompIndexConnectedToInPin(int n)
{
	return SrcPin->getCompIndex();
}

Component * Connection::DeleteConnection(ApplicationManager* ptr)
{

	for ( int i = 0; i < 780; i++ )
		for ( int j = 0; j < 1400; j++ )
			if ( ptr->GetArr( )[i][j] == this )ptr->GetArr( )[i][j] = NULL;
	this->getSourcePin( )->DeleteConnection( this );
	this->getDestPin( )->set_connection( NULL );
	return this;
}
