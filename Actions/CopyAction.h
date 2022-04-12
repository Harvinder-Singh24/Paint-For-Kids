#ifndef COPY_ACTION_H
#define COPY_ACTION_H
#include "Action.h"
#include "SelectAction.h"
#include "..\Figures\CFigure.h"
class CopyAction : public Action
{
private:
	enum { MaxFigCount = 200 };	//Max no of figures
	int SelectedCount;
	CFigure* const* SelectedFigs;
	CFigure* newSelFigs[MaxFigCount];
public:
	CopyAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~CopyAction();
};
#endif