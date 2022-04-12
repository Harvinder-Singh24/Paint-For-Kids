#ifndef PASTE_ACTION_H
#define PASTE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

class PasteAction : public Action
{
private:
	CFigure* const* PastedFig;
	Point P;
	Point PastedP;
	int clipboardCount;
	int transX, transY;

public:
	PasteAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	~PasteAction();
};
#endif
