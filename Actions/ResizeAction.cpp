#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager * pApp) :Action(pApp)
{
	scale = 0;
	SelectedFig = nullptr;
}

void ResizeAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Resize: Enter one of these factors: 0.25 , 0.5 , 2, 4");
	scale = stof(pIn->GetSrting(pOut));
}

void ResizeAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	if (pManager->NewSelectedCount() != 0)
	{
		pOut->PrintMessage("Figure(s) resized.");
		pManager->ResizeFigures(scale);
	}
	else pOut->PrintMessage("No Figures Selected");

}

ResizeAction::~ResizeAction()
{
}
