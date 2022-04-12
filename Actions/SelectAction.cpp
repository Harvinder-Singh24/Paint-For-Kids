#include "SelectAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp)
{
}

void SelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	
	pOut->PrintMessage("Select a figure(s): Click on the figure you would like to select");

	//Read clicked point and store in P
	pIn->GetPointClicked(P.x, P.y);
	SelectedFig = pManager->GetFigure(P.x, P.y);
	//Clear the status bar
	pOut->ClearStatusBar();
}

//Selected an unselected figure
void SelectAction::Select()
{
	SelectedFig->SetSelected(true);				//Sets the figure as "selected"
	pManager->AddSelectedFigure(SelectedFig);	//Add the figure to ApplicationManager's SelectedFigs array
	Output* pOut = pManager->GetOutput();		//Get a Pointer to the Output Interface
	if (pManager->NewSelectedCount() == 1)
		SelectedFig->PrintInfo(pOut);			//Print the selected figure info on the status bar
	else if (pManager->NewSelectedCount() == 0)
			pOut->PrintMessage("No figure is selected try again");
	else
		pOut->PrintMessage( "Number of selected figures " + to_string(pManager->NewSelectedCount()) ); // print the number of selected figures
}

//Unselect a selected figure
void SelectAction::Nselect()
{
	SelectedFig->SetSelected(false);				//Sets the figure as "unselected"
	pManager->RemoveSelectedFigure(SelectedFig);	//Removes the figure from ApplicationManager's SelectedFigs array
}


//Execute the action
void SelectAction::Execute()
{
	//Reads the point that the user clicked
	ReadActionParameters();

	//Set SelectedFig to the clicked figure
	SelectedFig = pManager->GetFigure(P.x, P.y);

	//Checks if a figure was clicked on, and if the clicked figure is selected or not
	if (SelectedFig != NULL){
		if (SelectedFig->IsSelected())
			Nselect();
		else
			Select();
	}
	pManager->UpdateInterface();
}

SelectAction::~SelectAction()
{
}