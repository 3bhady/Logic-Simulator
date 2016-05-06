#include "Paste.h"


Paste::Paste( ApplicationManager * pApp ):Action(pApp )
{
}


Paste::~Paste( )
{
}

bool Paste::ReadActionParameters( string s )
{
	if ( pManager->GetClipboard( ).empty( ) )
	{
		pManager->GetOutput( )->PrintMsg( "The Clipboard is empty" );
		return false;
	}
	
	return true;
}

void Paste::Execute( )
{
	if ( !ReadActionParameters( "" ) )
		return;
	int size = pManager->GetHighlightedList( ).size( );
	for ( int i = 0; i < size; i++ )
	{
		pManager->GetHighlightedList( )[i]->Unhighlight( );
	}
	pManager->GetHighlightedList( ).clear( );

	size = pManager->GetClipboard( ).size( );
	for ( int i = 0; i < size; i++ )
	{
		Component* pG;
		GraphicsInfo GInfo = pManager->GetClipboard( )[i].first;
		switch ( pManager->GetClipboard( )[i].second )
		{
		case ADD_AND_GATE_2:
		{
				pG = new AND2( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_OR_GATE_2:
		{
				pG = new OR2( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_Buff:
		{
				pG = new BUFFER( GInfo , AND2_FANOUT );
			break; }
		case ADD_INV:
		{
				pG = new NOT( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_NAND_GATE_2:
		{
				pG = new NAND2( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_NOR_GATE_2:
		{
			pG = new NOR2( GInfo , AND2_FANOUT );
		break;
		}
		case ADD_XOR_GATE_2:
		{
			
				pG = new XOR2( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_XNOR_GATE_2:
		{
			
				pG = new XNOR2( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_AND_GATE_3:
		{
			
				pG = new AND3( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_OR_GATE_3:
		{
			
				pG = new OR3( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_NAND_GATE_3:
		{
			
				pG = new NAND3( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_NOR_GATE_3:
		{
			
				pG = new NOR3( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_XOR_GATE_3:
		{
				pG = new XOR3( GInfo , AND2_FANOUT );
			break;
		}
		case ADD_XNOR_GATE_3:
		{
			pG = new XNOR3( GInfo , AND2_FANOUT );
			break;
		}
		default:
			break;
		}

		pManager->GetHighlightedList( ).push_back( pG );

				


	}
	
	if ( pManager->GetOutput( )->MoveComponents( pManager , pManager->GetHighlightedList( )[0] ) )
		for ( int i = 0; i < size; i++ )
			pManager->AddComponent( pManager->GetHighlightedList( )[i] );
}

void Paste::Undo( )
{
}

void Paste::Redo( )
{
}
