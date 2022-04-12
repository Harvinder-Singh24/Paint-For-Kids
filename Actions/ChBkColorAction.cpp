#include "ChBkColorAction.h"

ChBkClrAction::ChBkClrAction(ApplicationManager* pApp) :Action(pApp)
{
	ColorNum = 0;
}

void ChBkClrAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change BackGround Color: Enter 1 for RED - 2 GREEN - 3 for BLUE - 4 ORANGE - 5 BROWN - 6 YELLOW - 7 BLACK - 8 WHITE");
	ColorNum = stoi(pIn->GetSrting(pOut));
}

void ChBkClrAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	
	pOut->PrintMessage("BackGround Color Changed.");
	pManager->ChangeBackGroundColor(ColorNum);

}

ChBkClrAction::~ChBkClrAction()
{
}
