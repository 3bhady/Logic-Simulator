#include "Select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

bool Select::ReadActionParameters()
{
	return true;
}

void Select::Execute()
{
	if ( UI.AppMode == EDIT_MODE )
		pManager->GetOutput( )->CloseEditMenu(pManager);	

	//the selected item
	Component * selectedItem = pManager->GetComponent(UI.u_GfxInfo.x1, UI.u_GfxInfo.y1);
	
	//if the clicked area doesn't point to NULL
	if ( selectedItem )
	{	
		GFXInfo = selectedItem->get_GraphicInfo();		//Save the graphics info
		if ( !selectedItem->isSelected( ) )				//Highlight the item if the item is not already highlighted
		{
			pManager->HighlightComponent(selectedItem);
			return;
		}
		if (pManager->GetInput()->DetectChange())		//Move 
		{
			Move = true;

			//Delete the components from the 2D array and draw an empty block over the gate
			for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
			{
				InitialPositions.push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
				pManager->GetHighlightedComponent(i)->EraseComponent(pManager);
			}

			//Move the highlighted components
			if (pManager->GetOutput()->MoveComponents(pManager, selectedItem))

			//Add the components in the grid in their new positions & add them to the moved components list of the action 
			for (unsigned int i = 0; i < pManager->getHighlightedCompListSize(); i++)
			{
				pManager->GetHighlightedComponent(i)->AddComponent(pManager);
				pManager->GetHighlightedComponent(i)->Highlight();
				FinalPositions.push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
			}
		}
		//if not move then unselect the selected item and remove it from the highlighted components vector
		else pManager->UnhighlightComponent(selectedItem);
	}
}

void Select::undo()
{
	if (!Move)
	{
		Component * pC = pManager->GetComponent(GFXInfo.x1, GFXInfo.y1);
		if (!pC->isSelected())
			pManager->HighlightComponent(pC);
		else 
			pManager->UnhighlightComponent(pC);
	}
	else {
		for (unsigned int i = 0; i < FinalPositions.size(); i++)
		{
			Component* pG = pManager->GetComponent(FinalPositions[i].first.x1, FinalPositions[i].first.y1);
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = InitialPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
}

void Select::redo()
{
	if (!Move)
	{
		Component * pC = pManager->GetComponent(GFXInfo.x1, GFXInfo.y1);
		if (!pC->isSelected())
			pManager->HighlightComponent(pC);
		else
			pManager->UnhighlightComponent(pC);
	}
	else {
		for (unsigned int i = 0; i < InitialPositions.size(); i++)
		{
			Component* pG = pManager->GetComponent(InitialPositions[i].first.x1, InitialPositions[i].first.y1);
			pG->EraseComponent(pManager);
			pG->get_GraphicInfo() = FinalPositions[i].first;
			pG->AddComponent(pManager);
		}
	}
}

/*int Select::CheckPin(pair<int, int> Coordinates)
{Component* Comp=pManager->GetArr()[Coordinates.second][Coordinates.first];
int check = Comp->GetInputPinIndex(Coordinates);
}*/

bool Select::MoveSource(Connection * Comp)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->FlushKeyQueue();
	pOut->ClearStatusBar();
	//Print Action Message
	pOut->PrintMsg("Changing the source Pin press Escape to cancel");
	pOut->UpdateBuffer();
	int Cx=0, Cy=0;
	GraphicsInfo GInfo;
	GInfo.x1 = Comp->get_GraphicInfo().x1;
	GInfo.y1 = Comp->get_GraphicInfo().y1;
	GInfo.x2 = Comp->get_GraphicInfo().x2;
	GInfo.y2 = Comp->get_GraphicInfo().y2;
	bool check = false;
	do {
		if (pIn->GetKeyPressed() == ESCAPE)
			return false;
		if (pIn->GetPointClicked(Cx, Cy) == LEFT_CLICK && (pManager->GetArr()[Cy][Cx]) != NULL) {
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
	if (check) {
		Comp->EraseComponent(pManager);
		pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
		pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		if (bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), Comp->get_path()))
			Comp->set_GraphicInfo(GInfo);
		GInfo.x1 = Comp->get_GraphicInfo().x1;
		GInfo.y1 = Comp->get_GraphicInfo().y1;
		GInfo.x2 = Comp->get_GraphicInfo().x2;
		GInfo.y2 = Comp->get_GraphicInfo().y2;
		pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
		pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		return true;
	}
	return false;
}
bool Select::MoveDest(Connection * Comp)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->FlushKeyQueue();
	pOut->ClearStatusBar();
	//Print Action Message
	pOut->PrintMsg("Changing the Destination Pin press Escape to cansel");
	pOut->UpdateBuffer();
	int Cx = 0, Cy = 0;
	GraphicsInfo GInfo;
	GInfo.x1 = Comp->get_GraphicInfo().x1;
	GInfo.y1 = Comp->get_GraphicInfo().y1;
	GInfo.x2 = Comp->get_GraphicInfo().x2;
	GInfo.y2 = Comp->get_GraphicInfo().y2;
	bool check = false;
	do {
		if (pIn->GetKeyPressed() == ESCAPE)
			return false;
		if (pIn->GetPointClicked(Cx, Cy) == LEFT_CLICK && (pManager->GetArr()[Cy][Cx]) != NULL)
		{
			if (pManager->GetArr()[Cy][Cx]->GetInputPinCoordinates(make_pair(Cx, Cy)) != NULL) {
				GInfo.x2 = (pManager->GetArr()[Cy][Cx])->GetInputPinCoordinates(make_pair(Cx, Cy))->first;
				GInfo.y2 = (pManager->GetArr()[Cy][Cx])->GetInputPinCoordinates(make_pair(Cx, Cy))->second;
				break;
			}
			else
			{
				pOut->ClearStatusBar();
				pOut->PrintMsg("You choosed an invalid Component, please choose a Gate or Led  ");
				pOut->UpdateBuffer();
			}
		}
	} while (true);
	if (check) {
		Comp->EraseComponent(pManager);
		pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
		pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		if (bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), Comp->get_path()))
			Comp->set_GraphicInfo(GInfo);
		GInfo.x1 = Comp->get_GraphicInfo().x1;
		GInfo.y1 = Comp->get_GraphicInfo().y1;
		GInfo.x2 = Comp->get_GraphicInfo().x2;
		GInfo.y2 = Comp->get_GraphicInfo().y2;
		pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
		pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		return true;
	}
	return false;
}

bool Select::MoveOutPin(Connection*Comp)
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int Cx = Comp->getSourcePin()->getComponent()->GetOutputPinCoordinates().first, Cy = Comp->getSourcePin()->getComponent()->GetOutputPinCoordinates().second;
	bool check = true;
	GraphicsInfo GInfo;
	Component* ChangedComponent = pManager->GetArr()[Cy][Cx - 15];
	for (int i = 0;i < ChangedComponent->GetOutputPin()->GetConnections().size();i++) {
		Comp = ChangedComponent->GetOutputPin()->GetConnections()[i];
		GInfo.x1 = Comp->get_GraphicInfo().x1;
		GInfo.y1 = Comp->get_GraphicInfo().y1;
		GInfo.x2 = Comp->get_GraphicInfo().x2;
		GInfo.y2 = Comp->get_GraphicInfo().y2;
		if (((pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().first != 0
			&& (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().second != 0)) {
			GInfo.x1 = (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().first;
			GInfo.y1 = (pManager->GetArr()[Cy][Cx])->GetOutputPinCoordinates().second;
		}
		else check = false;

		if (check) {
			Comp->EraseComponent(pManager);
			pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
			pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
			if (bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), Comp->get_path()))
				Comp->set_GraphicInfo(GInfo);
			GInfo.x1 = Comp->get_GraphicInfo().x1;
			GInfo.y1 = Comp->get_GraphicInfo().y1;
			GInfo.x2 = Comp->get_GraphicInfo().x2;
			GInfo.y2 = Comp->get_GraphicInfo().y2;
			pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
			pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		}
		else break;
	}
	return check;
}

bool Select::MoveInput(Connection*Comp)
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int Cx = Comp->getDestPin()->getComponent()->GetInputPinCoordinates(Comp->getDestPin())->first, Cy = Comp->getDestPin()->getComponent()->GetInputPinCoordinates(Comp->getDestPin())->second;
	bool check = true;
	GraphicsInfo GInfo;
	Component* ChangedComponent = pManager->GetArr()[Cy][Cx];

	    Comp = NULL;

		Comp = ChangedComponent->GetInputPin(make_pair(Cx,Cy))->get_connection();
		GInfo.x1 = Comp->get_GraphicInfo().x1;
		GInfo.y1 = Comp->get_GraphicInfo().y1;
		GInfo.x2 = Comp->get_GraphicInfo().x2;
		GInfo.y2 = Comp->get_GraphicInfo().y2;
		if (pManager->GetArr()[Cy][Cx]->GetInputPinCoordinates(make_pair(Cx, Cy)) != NULL) {
			GInfo.x2 = (pManager->GetArr()[Cy][Cx])->GetInputPinCoordinates(make_pair(Cx, Cy))->first;
			GInfo.y2 = (pManager->GetArr()[Cy][Cx])->GetInputPinCoordinates(make_pair(Cx, Cy))->second;
		}
		else check = false;

		if (check) {
			Comp->EraseComponent(pManager);
			pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
			pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
			if (bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), Comp->get_path()))
				Comp->set_GraphicInfo(GInfo);
			GInfo.x1 = Comp->get_GraphicInfo().x1;
			GInfo.y1 = Comp->get_GraphicInfo().y1;
			GInfo.x2 = Comp->get_GraphicInfo().x2;
			GInfo.y2 = Comp->get_GraphicInfo().y2;
			pManager->GetArr()[GInfo.y1][GInfo.x1 - 15]->GetOutputPin()->ConnectTo(Comp);
			pManager->GetArr()[GInfo.y2][GInfo.x2]->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		}

	return check;
	
}

bool Select::ReturnConnection(GraphicsInfo & GInfo,Connection*Comp)
{
		Comp->EraseComponent(pManager);

		pManager->GetComponent(GInfo.x1 - 15,GInfo.y1)->GetOutputPin()->ConnectTo(Comp);
		pManager->GetComponent(GInfo.x2,GInfo.y2)->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		if (bfs(GInfo.x1, GInfo.y1, GInfo.x2, GInfo.y2, pManager->GetArr(), Comp->get_path()))
		Comp->set_GraphicInfo(GInfo);
		GInfo.x1 = Comp->get_GraphicInfo().x1;
		GInfo.y1 = Comp->get_GraphicInfo().y1;
		GInfo.x2 = Comp->get_GraphicInfo().x2;
		GInfo.y2 = Comp->get_GraphicInfo().y2;
		pManager->GetComponent(GInfo.x1 - 15,GInfo.y1)->GetOutputPin()->ConnectTo(Comp);
		pManager->GetComponent(GInfo.x2,GInfo.y2)->GetInputPin(make_pair(GInfo.x2, GInfo.y2))->set_connection(Comp);
		return true;

}

bool Select::bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &ConnectionPath)
{
	BFSOut outx;
	outx.check = false;
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

	if (vis[x2][y2] == 1) {
		outx.check = true;
		for (int i = 0;i < 780;i++)
			for (int j = 0;j < 1400;j++)
				ConnectionPath.arr[j][i] = outx.arr[j][i];
	}
	else outx.check = false;
	for (int i = 0; i < 780; i++) { delete[]vis[i]; delete[]ifc[i]; delete[]oth[i]; }
	delete[]vis; delete[]ifc; delete[]oth;
	return outx.check;
}
bool Select::isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1)
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



Select::~Select()
{
}
