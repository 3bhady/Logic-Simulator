#include "Select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

bool Select::ReadActionParameters(string s)
{
	return true;
}

void Select::Execute()
{
	if ( UI.AppMode == EDIT_MODE )
	{
		pManager->GetOutput( )->CloseEditMenu(pManager);
		
	}
	Component * selectedItem = pManager->GetArr( )[UI.u_GfxInfo.y1][UI.u_GfxInfo.x1];	//the selected item
	
	if ( selectedItem )					   //if the clicked area doesn't point to NULL
	{	
		
		if ( !selectedItem->isSelected( ) )			//highlight the item if the item is not already highlighted
		{
			selectedItem->Highlight( );
			pManager->GetHighlightedList().push_back(selectedItem);		//push it in the highlighted comp list
			GFXInfo = selectedItem->get_GraphicInfo();		//Save the graphics info
			Move = false;
			return;
		}
			GraphicsInfo &GfxInfo = selectedItem->get_GraphicInfo();	   //the graphics info of the selected component

			if (pManager->GetInput()->DetectChange())		//Move 
			{
				/*
				vector<Component*> HighlightedVec;
				for (int i = 0; i< (int)pManager->GetCompList().size(); i++)
				{
					if (pManager->GetCompList()[i]->isSelected())
						HighlightedVec.push_back(pManager->GetCompList()[i]);
				}
				for (int i = 0; i <(int) HighlightedVec.size(); i++)
				{
					HighlightedVec[i]->DeleteComponent(pManager); //delete the component from the 2D array and draw an empty block over the gate
							 
				}
				*/

				Move = true;

				//delete the components from the 2D array and draw an empty block over the gate
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
					InitialPositions.push_back(make_pair(pManager->GetHighlightedList()[i]->get_GraphicInfo(), pManager->GetHighlightedList()[i]->getType())),
					pManager->GetHighlightedList()[i]->EraseComponent(pManager);
					

				//move the highlighted components
				pManager->GetOutput()->MoveComponents(pManager, selectedItem);
			
				//add the components in the grid in their new positions & add them to the moved components list of the action 
				for (unsigned int i = 0; i < pManager->GetHighlightedList().size(); i++)
				{
					pManager->GetHighlightedList()[i]->AddComponent(pManager);
					pManager->GetHighlightedList()[i]->Highlight();
					FinalPositions.push_back(make_pair(pManager->GetHighlightedList()[i]->get_GraphicInfo(), pManager->GetHighlightedList()[i]->getType()));
				}
			}
			else
			{
				//if not move then unselect the selected item
				selectedItem->Unhighlight();

				//find the selected item and remove it from the highlighted components vector
				vector<Component*>::iterator it;
				it = find(pManager->GetHighlightedList().begin(), pManager->GetHighlightedList().end(), selectedItem);
				pManager->GetHighlightedList().erase(it);
			}
	}
}

void Select::undo()
{
	if (!Move)
		pManager->GetArr()[GFXInfo.y1][GFXInfo.x1]->ChangeState();		//if select return the state of the selected component
	else
	{
		for (int i = 0; i < FinalPositions.size();i++)
			pManager->GetArr()[FinalPositions[i].first.y1][FinalPositions[i].first.x1]->DeleteComponent(pManager);
		int size = InitialPositions.size();
		for (int i = 0; i < size; i++)
		{
			Component* pG;
			GraphicsInfo GInfo = InitialPositions[i].first;
			switch (InitialPositions[i].second)
			{
			case AND2_:
			{
				pG = new AND2(GInfo, AND2_FANOUT);
				break;
			}
			case OR2_:
			{
				pG = new OR2(GInfo, AND2_FANOUT);
				break;
			}
			case Buff_:
			{
				pG = new BUFFER(GInfo, AND2_FANOUT);
				break; }
			case INV_:
			{
				pG = new NOT(GInfo, AND2_FANOUT);
				break;
			}
			case NAND2_:
			{
				pG = new NAND2(GInfo, AND2_FANOUT);
				break;
			}
			case NOR2_:
			{
				pG = new NOR2(GInfo, AND2_FANOUT);
				break;
			}
			case XOR2_:
			{

				pG = new XOR2(GInfo, AND2_FANOUT);
				break;
			}
			case XNOR2_:
			{

				pG = new XNOR2(GInfo, AND2_FANOUT);
				break;
			}
			case AND3_:
			{

				pG = new AND3(GInfo, AND2_FANOUT);
				break;
			}
			case OR3_:
			{

				pG = new OR3(GInfo, AND2_FANOUT);
				break;
			}
			case NAND3_:
			{

				pG = new NAND3(GInfo, AND2_FANOUT);
				break;
			}
			case NOR3_:
			{

				pG = new NOR3(GInfo, AND2_FANOUT);
				break;
			}
			case XOR3_:
			{
				pG = new XOR3(GInfo, AND2_FANOUT);
				break;
			}
			case XNOR3_:
			{
				pG = new XNOR3(GInfo, AND2_FANOUT);
				break;
			}
			default:
				break;
			}
			pManager->AddComponent(pG);
			pG->Highlight();
		}
	}
	pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void Select::redo()
{
	if (!Move)
		pManager->GetArr()[GFXInfo.y1][GFXInfo.x1]->ChangeState();		//if select return the state of the selected component
	else {
		for (int i = 0; i < InitialPositions.size(); i++)
			pManager->GetArr()[InitialPositions[i].first.y1][InitialPositions[i].first.x1]->DeleteComponent(pManager);
		int size = FinalPositions.size();
		for (int i = 0; i < size; i++)
		{
			Component* pG;
			GraphicsInfo GInfo = FinalPositions[i].first;
			switch (FinalPositions[i].second)
			{
			case AND2_:
			{
				pG = new AND2(GInfo, AND2_FANOUT);
				break;
			}
			case OR2_:
			{
				pG = new OR2(GInfo, AND2_FANOUT);
				break;
			}
			case Buff_:
			{
				pG = new BUFFER(GInfo, AND2_FANOUT);
				break; }
			case INV_:
			{
				pG = new NOT(GInfo, AND2_FANOUT);
				break;
			}
			case NAND2_:
			{
				pG = new NAND2(GInfo, AND2_FANOUT);
				break;
			}
			case NOR2_:
			{
				pG = new NOR2(GInfo, AND2_FANOUT);
				break;
			}
			case XOR2_:
			{

				pG = new XOR2(GInfo, AND2_FANOUT);
				break;
			}
			case XNOR2_:
			{

				pG = new XNOR2(GInfo, AND2_FANOUT);
				break;
			}
			case AND3_:
			{

				pG = new AND3(GInfo, AND2_FANOUT);
				break;
			}
			case OR3_:
			{

				pG = new OR3(GInfo, AND2_FANOUT);
				break;
			}
			case NAND3_:
			{

				pG = new NAND3(GInfo, AND2_FANOUT);
				break;
			}
			case NOR3_:
			{

				pG = new NOR3(GInfo, AND2_FANOUT);
				break;
			}
			case XOR3_:
			{
				pG = new XOR3(GInfo, AND2_FANOUT);
				break;
			}
			case XNOR3_:
			{
				pG = new XNOR3(GInfo, AND2_FANOUT);
				break;
			}
			default:
				break;
			}
			pManager->AddComponent(pG);
			pG->Highlight();
			pManager->GetHighlightedList().push_back(pG);
		}
	}
}

Select::~Select()
{
}

void Select::bfs(int x1, int y1, int x2, int y2, Component*** a, BFSOut &outx)
{

	int** vis = new int*[1400];for (int i = 0;i < 1400;i++)vis[i] = new int[780];
	for (int i = 0;i < 1400;i++)for (int j = 0;j < 780;j++)vis[i][j] = 0;
	int** ifc = new int*[780];for (int i = 0;i < 780;i++)ifc[i] = new int[1400];
	int** oth = new int*[780];for (int i = 0;i < 780;i++)oth[i] = new int[1400];
	for (int i = 0;i < 780;i++)
		for (int j = 0;j < 1400;j++) {
			if (a[i][j] != NULL)
				if (dynamic_cast<Connection*>(a[i][j])) { if (((Connection*)(a[i][j]))->getSourcePin() == ((Gate*)a[y1][x1 - 15])->get_Opin())ifc[i][j] = 0;else  ifc[i][j] = 1;oth[i][j] = 0; }
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
	for (int i = 0;i < 780;i++) { delete[]vis[i];delete[]ifc[i];delete[]oth[i]; }
	delete[]vis;delete[]ifc;delete[]oth;
}
bool Select::isvalid(int x, int y, int** vis, int** ifc, int** oth, int x0, int y0, int x2, int y2, int x1)
{
	if (y < 630 && x < 1335)
		if (x >= 0 && y >= 0) {
			if ((x == x2 || x + 15 == x2) && y == y2)
				return true;
			if (oth[y][x] == 1 || (oth[y][x + 15] == 1) || (oth[y][x - 15] == 1 && !(x == x1 || x - 15 == x1)))
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

