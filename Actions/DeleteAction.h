#pragma once

#include "Action.h"
#include "../Figures/CFigure.h"

class DeleteAction : public Action 
{
	CFigure* const* SelectedFigs; //Pointer to the selected figures
public:
	DeleteAction(ApplicationManager* pApp);

	//Reads draw color parameters
	virtual void ReadActionParameters();

	//Changes current/selected figure draw color
	virtual void Execute();

	~DeleteAction();
};