#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircAction : public Action
{
private:
	Point P1, P2; //Circle center/border points
	GfxInfo CircGfxInfo;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads Circle parameters
	virtual void ReadActionParameters();

	//Add Circle to the ApplicationManager
	virtual void Execute();

	~AddCircAction();
};

#endif

