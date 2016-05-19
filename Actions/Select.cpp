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
