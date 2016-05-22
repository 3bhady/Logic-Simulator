#include "Cut.h"

Cut::Cut(ApplicationManager* pApp):Action(pApp )
{

}


Cut::~Cut( )
{
}

bool Cut::ReadActionParameters()
{
	int size = pManager->GetCompList( ).size( );
	bool selected = false; //it's true if at least there is one selected item to be copied
	for ( int i = 0; i < size; i++ )
		if ( pManager->GetCompList( )[i]->isSelected( ) )
		{
			selected = true; pManager->GetClipboard( ).clear( );  break;
		}
	return selected;
}

void Cut::Execute( )
{
	if ( !ReadActionParameters( ) )
		return;
	for ( unsigned int i = 0; i <pManager->GetCompList( ).size( ); i++ )
		if ( pManager->GetCompList( )[i]->isSelected( ) )
		{
			
			pManager->GetClipboard( ).push_back( make_pair( pManager->GetCompList( )[i]->get_GraphicInfo( ) , pManager->GetCompList( )[i]->getType( ) ) );
			ActionClipboard.push_back(make_pair(pManager->GetCompList()[i]->get_GraphicInfo(), pManager->GetCompList()[i]->getType()));
			pManager->GetCompList( )[i]->DeleteComponent( pManager );
			//delete pManager->GetCompList( )[i];
			//pManager->GetCompList( ).erase( pManager->GetCompList( ).begin() + i );
			i--;
		}
	pManager->ClearHighlightedCompList();
}	

void Cut::undo( )
{
	int size = ActionClipboard.size();
	for (int i = 0; i < size; i++)
	{
		Component* pG;
		GraphicsInfo GInfo = ActionClipboard[i].first;
		switch (pManager->GetClipboard()[i].second)
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
	}
}

void Cut::redo( )
{
}
