#include "Cut.h"

Cut::Cut(ApplicationManager* pApp):Action(pApp )
{

}


Cut::~Cut( )
{
}

bool Cut::ReadActionParameters()
{
	//it's true if at least there is one selected item to be copied
	bool selected = false;

	for ( int i = 0; i < pManager->GetComplistSize(); i++ )
		if ( pManager->GetComponent(i)->isSelected( ) )
		{
			selected = true; pManager->GetClipboard( ).clear( );  break;
		}

	return selected;
}

void Cut::Execute( )
{
	//if in EDITMODE, close Edit menu after cut
	if ( UI.AppMode == EDIT_MODE )
		pManager->GetOutput( )->CloseEditMenu( pManager );

	if ( !ReadActionParameters( ) )
		return;

	//Push the highlighted components in ClipBoard and delete them
	for (int i = 0; i < pManager->GetComplistSize(); i++)
		if ( pManager->GetComponent(i)->isSelected( ) )
		{
			pManager->GetClipboard().push_back(make_pair(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()), pManager->GetHighlightedComponent(i)->get_label()));
			ActionClipboard.push_back(make_pair(make_pair(pManager->GetComponent(i)->get_GraphicInfo(), pManager->GetComponent(i)->getType()),pManager->GetComponent(i)->get_label()));
			pManager->GetComponent(i)->DeleteComponent( pManager );
			//i--;
		}
	pManager->ClearHighlightedCompList();
}	

void Cut::undo( )
{
	//Add the components in the clipboard of this action (cut by this action)
	for (int i = 0; i < ActionClipboard.size(); i++)
	{
		Component* pG;
		GraphicsInfo GInfo = ActionClipboard[i].first.first;
		switch (pManager->GetClipboard()[i].first.second)
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
		default:break;
		}
		pManager->AddComponent(pG);
	}
}

void Cut::redo( )
{
}
