#pragma once
#include "Action.h"
class AreaSelect :	public Action
{
	vector<GraphicsInfo> HighlightedComponentsGfx;
	vector<GraphicsInfo> InitialHighlightedCompGfx;
public:
	AreaSelect(ApplicationManager* pApp);
	~AreaSelect( );
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute( );

	//To undo this action (code depends on action type)
	virtual void undo( ) ;

	//To redo this action (code depends on action type)
	void redo( );


};

