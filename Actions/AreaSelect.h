#pragma once
#include "Action.h"
class AreaSelect :	public Action
{
	vector<GraphicsInfo> HighlightedComponentsGfx;		//Components highlighted by this action
	vector<GraphicsInfo> InitialHighlightedCompGfx;		//Components which were highlighted before this action
public:
	AreaSelect(ApplicationManager* pApp);
	~AreaSelect( );

	//Reads parameters required for action to execute
	virtual bool ReadActionParameters();

	//Execute action
	virtual void Execute( );

	//Undo this action
	virtual void undo( ) ;

	//Redo this action
	void redo( );


};

