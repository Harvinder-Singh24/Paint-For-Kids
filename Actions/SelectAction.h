#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"
#include "../Figures/CFigure.h"

//Select Action class
class SelectAction : public Action
{
private:
	Point P;  //Clicked point
	CFigure* SelectedFig; //Clicked figure
public:
	SelectAction(ApplicationManager* pApp);

	//Reads select parameters
	virtual void ReadActionParameters();

	//Executes the select action
	virtual void Execute();
	void Select();
	void Nselect();

	~SelectAction();
};

#endif
