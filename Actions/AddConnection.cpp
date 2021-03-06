#include "AddConnection.h"


AddConnection::AddConnection( ApplicationManager *pApp ) :Action( pApp )
{
}

AddConnection::~AddConnection( void )
{
}

bool AddConnection::ReadActionParameters()
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->FlushKeyQueue();
	pOut->ClearStatusBar();
	//Print Action Message
	
	pOut->PrintMsg("Adding Connection : Click to add the first edge ");
	pOut->UpdateBuffer();
	if ( pManager->GetComponent( UI.u_GfxInfo.x1 , UI.u_GfxInfo.y1 )==NULL)
	do {
		if (pIn->GetKeyPressed() == ESCAPE)
			return false;
		if (pIn->GetPointClicked(Cx, Cy) == LEFT_CLICK&& (pManager->GetArr()[Cy][Cx])!=NULL) {
			if (((pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().first != 0
				&& (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().second != 0)) {
				GInfo.x1 = (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().first;
				GInfo.y1 = (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().second;
				break;
			}
			else {
				pOut->ClearStatusBar();
				pOut->PrintMsg("Please choose a vaild Gate or Switch  ");
				pOut->UpdateBuffer();
			}
		}

	} while (true);
	else
	{
		GInfo.x1 = (pManager->GetComponent( UI.u_GfxInfo.x1,UI.u_GfxInfo.y1))->GetOutputPinCoordinates( ).first;
		GInfo.y1 = (pManager->GetComponent(UI.u_GfxInfo.x1,UI.u_GfxInfo.y1))->GetOutputPinCoordinates( ).second;
	}
	pOut->ClearStatusBar();
	pOut->PrintMsg("Adding Connection : Click to add the second edge ");
	pOut->UpdateBuffer();
	do {
		if (pIn->GetKeyPressed() == ESCAPE)
			return false;
		if (pIn->GetPointClicked(Cx, Cy) == LEFT_CLICK && (pManager->GetArr()[Cy][Cx]) != NULL)
		{
			pOut->Magnetize(Cx, Cy);
			if (pManager->GetArr()[Cy][Cx]->GetInputPinCoordinates(make_pair(Cx, Cy)) != NULL) {
			
				GInfo.x2 = (pManager->GetComponent( Cx , Cy ))->GetInputPinCoordinates( make_pair( Cx , Cy ) )->first;
				GInfo.y2 = (pManager->GetComponent( Cx , Cy ))->GetInputPinCoordinates( make_pair( Cx , Cy ) )->second;
				break;
			}
			else
			{
				pOut->ClearStatusBar();
				pOut->PrintMsg("You choosed an invalid Component, please choose a Gate or Led !!");
				pOut->UpdateBuffer();
			}
		}
	} while (true);
	bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), outx);
	if (outx.check)
		return true;
	else {
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMsg("There is no valid path");
		pManager->GetOutput()->UpdateBuffer();
		return false;
	}
}

void AddConnection::Execute()
{
	Connection *pS = NULL;
	//Get Center point of the Connection
	if (!ReadActionParameters())
		return;																														  
	pS = new Connection(GInfo, &outx, (pManager->GetComponent( GInfo.x1 - 15 , GInfo.y1 ))->GetOutputPin(), (pManager->GetComponent( GInfo.x2 , GInfo.y2 ))->GetInputPin(make_pair(GInfo.x2, GInfo.y2)));
	//pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(pS);
	pManager->GetComponent(GInfo.x1 - 15, GInfo.y1 )->GetOutputPin( )->ConnectTo( pS );
	//pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(pS);
	pManager->GetComponent( GInfo.x2,GInfo.y2)->GetInputPin( make_pair( GInfo.x2 , GInfo.y2 ) )->set_connection( pS );
	pManager->AddComponent(pS);
}
void AddConnection::bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx)
{
	int** vis = new int*[1400];for (int i = 0;i < 1400;i++)vis[i] = new int[780];
	for (int i = 0;i < 1400;i++)for (int j = 0;j < 780;j++)vis[i][j] = 0;
	int** ifc = new int*[780];for (int i = 0;i < 780;i++)ifc[i] = new int[1400];
	int** oth = new int*[780];for (int i = 0;i < 780;i++)oth[i] = new int[1400];
	for (int i = 0;i < 780;i++)
		for (int j = 0;j < 1400;j++) {
			if (a[i][j] != NULL)
				if (a[i][j]->getSourcePin()!=NULL) {
					if (a[y1][x1 - 15]->getSourcePin()==NULL) {
						if  (((a[i][j]))->getSourcePin() == (a[y1][x1 - 15])->GetOutputPin())
							ifc[i][j] = 0;
						else
							ifc[i][j] = 1;
						oth[i][j] = 0;
					}
				}
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

		if (isvalid(pr.first + 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2, x1,y1))
		{
			qu.push(make_pair(pr.first + 15, pr.second));
			outx.arr[pr.first + 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first + 15][pr.second] = 1;
			if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first, pr.second + 15, vis, ifc, oth, pr.first, pr.second, x2, y2, x1,y1))
		{
			qu.push(make_pair(pr.first, pr.second + 15));
			outx.arr[pr.first][pr.second + 15] = make_pair(pr.first, pr.second);
			vis[pr.first][pr.second + 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first - 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2, x1,y1))
		{
			qu.push(make_pair(pr.first - 15, pr.second));
			outx.arr[pr.first - 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first - 15][pr.second] = 1;	if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first, pr.second - 15, vis, ifc, oth, pr.first, pr.second, x2, y2, x1,y1))
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
bool AddConnection::isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2,int x1,int y1)
{
	if (y < 630 && x < 1335)
		if (x >= 0 && y >= 0) {
			if (((x == x2||x+15==x2)&&y == y2)|| (x == x2 &&((y==y2-15)||y==y2+15)) )
		if	(x==x2&&y==y2)
				return true;
			if (oth[y][x] == 1)
				return false;
			if (oth[y][x + 15] == 1 && x + 15 != x2&&y!=y2)return false;
				//||(oth[y][x - 15] == 1&&!(x==x1|| x -15== x1))*/
			if( oth[y][x - 15] == 1 )
				if( !(y == y1 || y + 15 == y1 || y - 15 == y1))
				return false;
			if ( vis[x][y] == 0 )
				if ( ifc[y][x] == 0 )
					return true;
				else
					if ( ifc[y0][x0] == 1 )
						return false;
					else
						if ( (ifc[y][x] == ifc[y][x + 15] && ifc[y][x] == ifc[y][x - 15]) || (ifc[y][x] == ifc[y + 15][x] && ifc[y][x] == ifc[y - 15][x]) )
							return true;
						else return false;
		}
	return false;
}

void AddConnection::LoadConnection(int SrcID, int DstID)
{
	Component* pSrcComp = NULL;
	Component* pDstComp = NULL;
	for (int i = 0; i < pManager->GetComplistSize(); i++)
		if (pManager->GetComponent(i)->getID() == SrcID)
		{
			pSrcComp = pManager->GetCompList()[i];
			break;
		}
	for (int i = 0; i < pManager->GetComplistSize(); i++)
		if (pManager->GetComponent(i)->getID() == DstID)
		{
			pDstComp = pManager->GetComponent(i);
			break;
		}

	GInfo.x1 = pSrcComp->GetOutputPinCoordinates().first;
	GInfo.y1 = pSrcComp->GetOutputPinCoordinates().second;
	GInfo.x2 = pDstComp->GetInputPinCoordinates(make_pair(pDstComp->get_GraphicInfo().x1 + 5, pDstComp->get_GraphicInfo().y1 + 5))->first;
	GInfo.y2 = pDstComp->GetInputPinCoordinates(make_pair(pDstComp->get_GraphicInfo().x1 + 5, pDstComp->get_GraphicInfo().y1 + 5))->second;
	bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), outx);
	if (outx.check) {
		Connection *pS = NULL;
		pS = new Connection(GInfo, &outx, pSrcComp->GetOutputPin(), pDstComp->GetInputPin(make_pair(GInfo.x2, GInfo.y2)));
		pSrcComp->GetOutputPin()->ConnectTo(pS);
		pDstComp->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(pS);
		pManager->AddComponent(pS);
	}
	else return;

}

void AddConnection::undo( )
{
	if (pManager->GetArr()[GInfo.y2][GInfo.x2] != NULL&&pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2)) != NULL&&
		pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->get_connection() != NULL)
	pManager->GetComponent(GInfo.x2, GInfo.y2)->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->get_connection()->DeleteComponent(pManager);
	pManager->GetOutput()->CreateGrid();
	pManager->GetOutput()->CreateToolBars();
	pManager->UpdateInterface();
	pManager->GetOutput()->UpdateBuffer();
}

void AddConnection::redo( )
{
	bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), outx);
	Connection *pS = NULL;
	pS = new Connection(GInfo, &outx, (pManager->GetArr()[GInfo.y1][GInfo.x1 - 15])->GetOutputPin(), (pManager->GetArr()[GInfo.y2][GInfo.x2])->GetInputPin(make_pair(GInfo.x2, GInfo.y2)));
	pManager->GetComponent(GInfo.x1 - 15, GInfo.y1)->GetOutputPin()->ConnectTo(pS);
	pManager->GetComponent(GInfo.x2, GInfo.y2)->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(pS);
	pManager->AddComponent(pS);
}
