#include "DeleteAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp)
{
}

void DeleteAction::ReadActionParameters()
{
	//Initialise local SelectedFigs 
	SelectedFigs = pManager->GetSelectedFigures();
}

void DeleteAction::Execute()
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	//Check if a figure is selected
	if (SelectedFigs[0] == NULL)
	{
		pOut->PrintMessage("Delete figure : Select a figure first");
	}
	else 
	{
		//Remove the figure 
		pManager->RemoveFig();

		pOut->ClearDrawArea();
		pManager->ClearSelectedFigs();
		pOut->PrintMessage("Figure(s) are Deleted");
	}
}

DeleteAction::~DeleteAction()
{
}
