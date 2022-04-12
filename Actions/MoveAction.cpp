#include "MoveAction.h"
#include "CutAction.h"
#include "PasteAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Input.h"



MoveAction::MoveAction(ApplicationManager* pApp) :Action(pApp)
{
}
void MoveAction::ReadActionParameters()
{
}

void MoveAction::Execute()
{

	//this action copies the figures(s) and wait for user action then pastes it then delete the original figure(S)
	Output* pOut = pManager->GetOutput();
	pManager->ExecuteAction(COPY);
	pManager->ExecuteAction(PASTE);
	pManager->ExecuteAction(DEL);
	pOut->PrintMessage("figure(s) moved");
}

MoveAction::~MoveAction()
{
}