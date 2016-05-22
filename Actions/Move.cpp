#include "Move.h"





Move::Move( ApplicationManager * pApp ):Action(pApp )
{

}

Move::~Move( )
{
}

bool Move::ReadActionParameters( )
{
	return false;
}

void Move::Execute( )
{
	
}

void Move::undo( )
{
}

void Move::redo( )
{
}
