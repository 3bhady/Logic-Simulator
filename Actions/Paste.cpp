#include "Paste.h"


Paste::Paste( ApplicationManager * pApp ):Action(pApp )
{
}


Paste::~Paste( )
{
}

bool Paste::ReadActionParameters()
{
	if ( pManager->GetClipboard( ).empty( ) )
	{
		pManager->GetOutput( )->PrintMsg( "The Clipboard is empty !" );
		return false;
	}
	return true;
}

void Paste::Execute( )
{
	if ( UI.AppMode == EDIT_MODE )
		pManager->GetOutput( )->CloseEditMenu( pManager );
	if ( !ReadActionParameters( ) )
		return;
	/*
	for (unsigned int i = 0; i < size; i++ )
	{
		pManager->GetHighlightedList( )[i]->Unhighlight( );
	}
	pManager->GetHighlightedList( ).clear( );
	*/
	pManager->ClearHighlightedCompList();
	unsigned int size = pManager->GetClipboard( ).size( );
	for (unsigned int i = 0; i < size; i++ )
	{
		
		Component* pG;
		GraphicsInfo GInfo = pManager->GetClipboard( )[i].first;
		switch ( pManager->GetClipboard( )[i].second )
		{
		case AND2_:
		{
				pG = new AND2( GInfo , AND2_FANOUT );
			break;
		}
		case OR2_:
		{
				pG = new OR2( GInfo , AND2_FANOUT );
			break;
		}
		case Buff_:
		{
				pG = new BUFFER( GInfo , AND2_FANOUT );
			break; }
		case INV_:
		{
				pG = new NOT( GInfo , AND2_FANOUT );
			break;
		}
		case NAND2_:
		{
				pG = new NAND2( GInfo , AND2_FANOUT );
			break;
		}
		case NOR2_:
		{
			pG = new NOR2( GInfo , AND2_FANOUT );
		break;
		}
		case XOR2_:
		{
			
				pG = new XOR2( GInfo , AND2_FANOUT );
			break;
		}
		case XNOR2_:
		{
			
				pG = new XNOR2( GInfo , AND2_FANOUT );
			break;
		}
		case AND3_:
		{
			
				pG = new AND3( GInfo , AND2_FANOUT );
			break;
		}
		case OR3_:
		{
			
				pG = new OR3( GInfo , AND2_FANOUT );
			break;
		}
		case NAND3_:
		{
			
				pG = new NAND3( GInfo , AND2_FANOUT );
			break;
		}
		case NOR3_:
		{
			
				pG = new NOR3( GInfo , AND2_FANOUT );
			break;
		}
		case XOR3_:
		{
				pG = new XOR3( GInfo , AND2_FANOUT );
			break;
		}
		case XNOR3_:
		{
			pG = new XNOR3( GInfo , AND2_FANOUT );
			break;
		}
		default:
			break;
		}

		//pManager->GetHighlightedList( ).push_back( pG );
		//pG->Highlight();
		pManager->HighlightComponent(pG);
	}
	
	if (pManager->GetOutput()->MoveComponents(pManager, pManager->GetHighlightedComponent(0)))
		for (unsigned int i = 0; i < size; i++)
			pManager->AddComponent(pManager->GetHighlightedComponent(i)),
			//pManager->GetHighlightedList()[i]->Unhighlight() ,
			ActionClipBoard.push_back(make_pair(pManager->GetHighlightedComponent(i)->get_GraphicInfo(), pManager->GetHighlightedComponent(i)->getType()));
	//pManager->GetHighlightedList().clear();
	pManager->ClearHighlightedCompList();
}

void Paste::undo( )
{
	//Delete the components from the grid
	for (unsigned int i = 0; i < ActionClipBoard.size(); i++)
		pManager->GetComponent(ActionClipBoard[i].first.x1,ActionClipBoard[i].first.y1)->DeleteComponent(pManager);

	//pManager->GetOutput()->DrawJPEGImage(initImage, 0, 0);				//Draw the stored image before this action
}

void Paste::redo( )
{
	int size = ActionClipBoard.size();
	for (int i = 0; i < size; i++)
	{
		Component* pG;
		GraphicsInfo GInfo = ActionClipBoard[i].first;
		switch (ActionClipBoard[i].second)
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
