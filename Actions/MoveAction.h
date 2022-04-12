#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H
#include "Action.h"
#include "SelectAction.h"
#include "..\Figures\CFigure.h"
class MoveAction : public Action
{
public:
	MoveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~MoveAction();
};
#endif