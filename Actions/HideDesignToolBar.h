
#include "Action.h"
class HideDesignToolBar :
	public Action
{
public:
	HideDesignToolBar(ApplicationManager*pApp);
	~HideDesignToolBar();
	//Reads parameters required for action to execute
	virtual bool ReadActionParameters(string s);

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void undo();

	//To redo this action (code depends on action type)
	virtual void redo();
};
