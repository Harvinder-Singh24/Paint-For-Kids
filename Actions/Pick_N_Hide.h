#pragma once
#include "Action.h"

class Pick_N_Hide :public Action
{
protected:

	int right, wrong, NumOfPlayFig;
	Point P;
	string test;
	color OfSelected;
public:

	Pick_N_Hide(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	string ColorToString(color Random);
	~Pick_N_Hide();
};