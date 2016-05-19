#include "Delete.h"



Delete::Delete( ApplicationManager *pApp ):Action(pApp )
{

}


Delete::~Delete( )
{

}

bool Delete::ReadActionParameters( string s )
{
	//check if highlighted list is empty 

	return false;
}

void Delete::Execute( )
{	
	// all highlighted compoents from 2D array
	
	//empty the highlighted list by clear and leave them highlighted

	//remove highlighted elements from component list



}

void Delete::undo( )
{
}

void Delete::redo( )
{
}
