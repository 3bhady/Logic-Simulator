#include "AddConnection.h"


AddConnection::AddConnection(ApplicationManager *pApp) :Action(pApp)
{
}

AddConnection::~AddConnection(void)
{
}

bool AddConnection::ReadActionParameters(string s = "")
{

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearStatusBar();
	//Print Action Message
	pOut->PrintMsg(s);

	do {

		//pOut->FlushMouseQueue();
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);

		if (dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])) {
			GInfo.x1 = dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_OP().first;
			GInfo.y1 = dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_OP().second;
			first = GA;break;
		}
		if (dynamic_cast<Switch*>(pManager->GetArr()[Cy][Cx])) {
			GInfo.x1 = Cx;
			GInfo.y1 = Cy;
			first = S;
			break;

		}
		/*if (dynamic_cast<Connection*>(pManager->GetArr()[Cy][Cx])) {
		GInfo.x1 = Cx;
		GInfo.y1 = Cy;break;
		}*/
		pOut->ClearStatusBar();
		pOut->PrintMsg("Please choose a vaild Gate or Switch  ");
	} while (true);
	s = "Adding Connection : Click to add the second edge ";
	pOut->ClearStatusBar();
	//Print Action Message
	pOut->PrintMsg(s);
	do {

		if (pIn->close()) { pOut->PrintMsg("Cansel adding Connection");return false; }
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);

		if (dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])) {
			if (dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_INPC() != NULL) {
				if (dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_INpin(make_pair(((Cx / 15) * 15), (((Cy + 14) / 15) * 15))) != NULL&&dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_INpin(make_pair(((Cx / 15) * 15), (((Cy + 14) / 15) * 15)))->get_connection() == NULL)
				{
					GInfo.x2 = ((Cx) / 15) * 15;
					GInfo.y2 = ((Cy + 14) / 15) * 15;
				}
				else {
					GInfo.x2 = dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_INPC()->first;
					GInfo.y2 = dynamic_cast<Gate*>(pManager->GetArr()[Cy][Cx])->get_INPC()->second;
				}
				second = G;
				break;
			}


		}
		if (dynamic_cast<LED*>(pManager->GetArr()[Cy][Cx])) {

			GInfo.x1 = Cx;
			GInfo.y1 = Cy;
			break;
		}
		//pOut->ClearStatusBar();
		//pOut->PrintMsg("Please choose a vaild Gate or Led");
		pOut->ClearStatusBar();
		pOut->PrintMsg("You choosed a nonvalied Component,please choose a Gate or Led  ");
	} while (true);
	bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), outx);
	if (outx.check)
		return true;
	else
		return false;
}

void AddConnection::Execute()
{
	Connection *pS = NULL;
	//Get Center point of the Connection
	if (!
		ReadActionParameters("Adding Connection : Click to add the first edge ")
		) {
		pManager->GetOutput()->ClearStatusBar();
		pManager->GetOutput()->PrintMsg("there is no valid path");
		return;
	}
	if (first == GA&&second == G)
	{
		//if ((((Gate*)pManager->GetArr()[GInfo.y1][GInfo.x1-15]))->get_INpin(make_pair(GInfo.x2, GInfo.x2))->get_connection() == NULL)
		//if((((Gate*)pManager->GetArr()[GInfo.y2][GInfo.x2]))->get_INpin(make_pair(GInfo.x2, GInfo.x2))==NULL)

		pS = new Connection(GInfo, &outx, (((Gate*)pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]))->get_Opin(), (((Gate*)pManager->GetArr()[GInfo.y2][GInfo.x2]))->get_INpin(make_pair(GInfo.x2, GInfo.y2)));
		(((Gate*)pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]))->get_Opin()->ConnectTo(pS);
		(((Gate*)pManager->GetArr()[GInfo.y2][GInfo.x2]))->get_INpin(make_pair(GInfo.x2, GInfo.y2))->set_connection(pS);
	}if (first == GA&&second == L)
		pS = new Connection(GInfo, &outx);
	if (first == S&&second == G)
		pS = new Connection(GInfo, &outx);
	if (first == S&&second == L)
		pS = new Connection(GInfo, &outx);

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
				if (dynamic_cast<Connection*>(a[i][j])) { if (dynamic_cast<Connection*>(a[i][j])->getSourcePin() == dynamic_cast<Gate*>(a[y1][x1 - 15])->get_Opin())ifc[i][j] = 0;else  ifc[i][j] = 1;oth[i][j] = 0; }
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

		if (isvalid(pr.first - 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2))
		{
			qu.push(make_pair(pr.first - 15, pr.second));
			outx.arr[pr.first - 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first - 15][pr.second] = 1;
			if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first, pr.second + 15, vis, ifc, oth, pr.first, pr.second, x2, y2))
		{
			qu.push(make_pair(pr.first, pr.second + 15));
			outx.arr[pr.first][pr.second + 15] =
				make_pair(pr.first, pr.second);
			vis[pr.first][pr.second + 15] = 1;	   if (qu.back().first == x2 && qu.back().second == y2)
				break;
		}
		if (isvalid(pr.first + 15, pr.second, vis, ifc, oth, pr.first, pr.second, x2, y2))
		{
			qu.push(make_pair(pr.first + 15, pr.second));
			outx.arr[pr.first + 15][pr.second] = make_pair(pr.first, pr.second);
			vis[pr.first + 15][pr.second] = 1;	if (qu.back().first == x2 && qu.back().second == y2)
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

	if (vis[x2][y2] == 1)
		outx.check = true;
	else outx.check = false;
	for (int i = 0;i < 780;i++) { delete[]vis[i];delete[]ifc[i];delete[]oth[i]; }
	delete[]vis;delete[]ifc;delete[]oth;
}
bool AddConnection::isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2)
{
	if (y < 630 && x < 1335)
		if (x >= 0 && y >= 0) {
			if (x == x2&&y == y2)
				return true;
			if (oth[y][x] == 1)
				return false;
			if (vis[x][y] == 0)
				if (ifc[y][x] == 0)
					return true;
				else
					if (ifc[y0][x0] == 1)
						return false;
					else
						if((ifc[y][x]==ifc[y][x+15]&& ifc[y][x] == ifc[y][x - 15])|| (ifc[y][x] == ifc[y+15][x] && ifc[y][x] == ifc[y-15][x]))
						return true;
						else return false;
		}
	return false;
}

void AddConnection::undo()
{}

void AddConnection::redo()
{}
