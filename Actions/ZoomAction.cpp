#include "ZoomAction.h"

ZoomAction::ZoomAction(ApplicationManager* pApp): Action(pApp)
{
	scale = 0;
	Fig = nullptr;
}

void ZoomAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Zoom: To zoom in Enter one of these factors: 2, 4 - To zoom out Enter one of these factors: 0.25, 0.5 - Enter 1 to return to original size ");
	scale = stof(pIn->GetSrting(pOut));
}

void ZoomAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	if (pManager->GetFigCount() != 0)
	{
		pOut->PrintMessage("Zoom done");
		pManager->Zoom(scale);
	}
}

ZoomAction::~ZoomAction()
{
}
