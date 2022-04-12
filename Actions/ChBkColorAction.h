#pragma once
#include "Action.h"
#include <string> 
#include "..//ApplicationManager.h"

class ChBkClrAction : public Action
{
	int ColorNum;
public:
	ChBkClrAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~ChBkClrAction();
};