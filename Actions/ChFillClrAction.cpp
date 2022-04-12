#include "ChFillClrAction.h"

ChFillClrAction::ChFillClrAction(ApplicationManager * pApp) :Action(pApp)
{
	ColorNum = 0;
	SelectedFig = nullptr;
}

void ChFillClrAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change Fill Color: Enter 1 for RED - 2 GREEN - 3 for BLUE - 4 ORANGE - 5 BROWN - 6 YELLOW - 7 BLACK - 8 WHITE");
	ColorNum = stoi(pIn->GetSrting(pOut));
}

void ChFillClrAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	if (pManager->NewSelectedCount() != 0)
	{
		pOut->PrintMessage("Figure(s) Fill Color Changed.");
		pManager->ChangeFillColor(ColorNum);
	}
	else pOut->PrintMessage("No Figures Selected");

}

ChFillClrAction::~ChFillClrAction()
{
}
