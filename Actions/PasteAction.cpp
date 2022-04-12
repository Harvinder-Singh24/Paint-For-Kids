#include "PasteAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include"..\GUI\Output.h"


PasteAction::PasteAction(ApplicationManager* pApp) :Action(pApp)
{
}
void PasteAction::ReadActionParameters()
{
	PastedFig = pManager->GetClipboardArr();
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (PastedFig[0] != NULL)
	{
		//Read clicked point and store in P
		pOut->PrintMessage("Click at a point to paste");
		pIn->GetDrawPoint(P.x, P.y, pOut);                   //gets a point to draw at
		clipboardCount = pManager->getClipboardCount();      //gets the number of items in clipboard
	}
	else
	{
		pOut->PrintMessage("Please copy or cut or move a figure first ");
	}
}
void PasteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (PastedFig[0] != NULL)
	{
		PastedP = PastedFig[0]->UpperPoint();   // gets the upper point of the selected figs

		transX = P.x - PastedP.x;               // change the transfered points according to the upper point stored 
		transY = P.y - PastedP.y;
	}

	for (int i = 0; i < clipboardCount; i++)
	{

		pManager->AddFigure(PastedFig[i]->paste(transX, transY));      // drows the new figs
		pOut->PrintMessage("Figure(s) are pasted!");

	}
}

PasteAction::~PasteAction()
{
}
