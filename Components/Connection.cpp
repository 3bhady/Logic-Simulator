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

bool Connection::ChangePath(ApplicationManager* pManger)
{
	bfs(m_GfxInfo.x1, m_GfxInfo.y1, m_GfxInfo.x2, m_GfxInfo.y2, pManger->GetArr(), outx);
	if (outx.check)
		return true;
	else
		return false;
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

void Connection::bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx)
{
	for (int i = 0;i < 780;i++)
		for (int j = 0;j < 1400;j++)
			outx.arr[j][i] = make_pair(0, 0);
	int** vis = new int*[1400];for (int i = 0;i < 1400;i++)vis[i] = new int[780];
	for (int i = 0;i < 1400;i++)for (int j = 0;j < 780;j++)vis[i][j] = 0;
	int** ifc = new int*[780];for (int i = 0;i < 780;i++)ifc[i] = new int[1400];
	int** oth = new int*[780];for (int i = 0;i < 780;i++)oth[i] = new int[1400];
	for (int i = 0;i < 780;i++)
		for (int j = 0;j < 1400;j++) {
			if (a[i][j] != NULL)
				if (dynamic_cast<Connection*>(a[i][j])) {
					if (!dynamic_cast<Connection*>(a[y1][x1 - 15])) {
						if (((Connection*)(a[i][j]))->getSourcePin() == (a[y1][x1 - 15])->GetOutputPin())
							ifc[i][j] = 0;
						else
							ifc[i][j] = 1;
						oth[i][j] = 0;
					}
				}
				else { ifc[i][j] = 0;oth[i][j] = 1; }
			else { ifc[i][j] = 0;oth[i][j] = 0; }

		}
	int klk = 0;
	queue< pair<int, int> > qu;
	qu.push(make_pair(x1, y1));
	while (!qu.empty())
	{
		pair<int, int> pr = qu.front();
		vis[pr.first][pr.second] = 1;
		qu.pop();

		if (isvalid(pr.first + 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2, x1))
		{
			qu.push(make_pair(pr.first + 15, pr.second));
			outx.arr[pr.first + 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first + 15][pr.second] = 1;
			if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first, pr.second + 15, vis, ifc, oth, pr.first, pr.second, x2, y2, x1))
		{
			qu.push(make_pair(pr.first, pr.second + 15));
			outx.arr[pr.first][pr.second + 15] = make_pair(pr.first, pr.second);
			vis[pr.first][pr.second + 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first - 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2, x1))
		{
			qu.push(make_pair(pr.first - 15, pr.second));
			outx.arr[pr.first - 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first - 15][pr.second] = 1;	if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first, pr.second - 15, vis, ifc, oth, pr.first, pr.second, x2, y2, x1))
		{
			qu.push(make_pair(pr.first, pr.second - 15));
			outx.arr[pr.first][pr.second - 15] = make_pair(pr.first, pr.second);
			vis[pr.first][pr.second - 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
	}

	if (vis[x2][y2] == 1)
		outx.check = true;
	else outx.check = false;
	for (int i = 0; i < 780; i++) { delete[]vis[i]; delete[]ifc[i]; delete[]oth[i]; }
	delete[]vis; delete[]ifc; delete[]oth;
}


void Connection::EraseComponent(ApplicationManager * pApp)
{
	Component *** Arr = pApp->GetArr();
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
					if (Arr[i][a] == this) {
						for (int j = a;j < a + 5;j++)if(Arr[i][j]==this)(Arr[i][j]) = NULL;
					}
			}
			else
				for (int i = d - 5;i <= b - 5;i++)
					if (Arr[i][a] == this) {

						for (int j = a;j < a + 5;j++)if(Arr[i][j] == this)(Arr[i][j]) = NULL;
					}
		}
		if (b == d) {
			if (a > c)
				for (int i = c;i <= a;i++) {
					if (Arr[b][i] == this) {
						for (int j = b - 7;j < b + 1;j++)if(Arr[j][i] == this)(Arr[j][i]) = NULL;
					}
				}
			else
				for (int i = a;i <= c;i++)
					if (Arr[b][i] == this) {
						for (int j = b - 7;j < b + 1;j++)if(Arr[j][i] == this)Arr[j][i] = NULL;
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

bool Connection::isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1)
{
	if (y < 630 && x < 1335)
		if (x >= 0 && y >= 0) {
			//if (((x == x2||x+15==x2)&&y == y)|| (x == x2 &&(y==y2-15||y==y2+15)) )
			if (x == x2&&y == y2)
				return true;
			if (oth[y][x] == 1/*||(oth[y][x+15]==1)||(oth[y][x - 15] == 1&&!(x==x1|| x -15== x1))*/)
				return false;
			if (vis[x][y] == 0)
				if (ifc[y][x] == 0)
					return true;
				else
					if (ifc[y0][x0] == 1)
						return false;
					else
						if ((ifc[y][x] == ifc[y][x + 15] && ifc[y][x] == ifc[y][x - 15]) || (ifc[y][x] == ifc[y + 15][x] && ifc[y][x] == ifc[y - 15][x]))
							return true;
						else return false;
		}
	return false;
}


InputPin * Connection::GetInputPin(int index)
{
	return NULL;
}

pair<int, int>* Connection::GetInputPinCoordinates(int)
{
	return NULL;
}
