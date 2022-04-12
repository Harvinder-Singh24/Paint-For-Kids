#pragma once
#include "Action.h"
#include <string> 
#include "..//Figures/CFigure.h"
#include "..//ApplicationManager.h"

class ChFillClrAction : public Action
{
	int ColorNum;
	CFigure* SelectedFig;
public:
	ChFillClrAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~ChFillClrAction();
};