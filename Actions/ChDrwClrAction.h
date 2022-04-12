#pragma once
#include "Action.h"
#include <string> 
#include "..//Figures/CFigure.h"
#include "..//ApplicationManager.h"

class ChDrwClrAction : public Action
{
	int ColorNum;
	CFigure* SelectedFig;
public:
	ChDrwClrAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~ChDrwClrAction();
};