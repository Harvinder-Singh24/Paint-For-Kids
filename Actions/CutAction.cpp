#include "CutAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Input.h"



CutAction::CutAction(ApplicationManager* pApp) :Action(pApp)
{
}
void CutAction::ReadActionParameters()
{
	SelectedFigs = pManager->GetSelectedFigures();
	selectedCount = pManager->NewSelectedCount();
	Output* pOut = pManager->GetOutput();

	if (SelectedFigs[0] == NULL)
	{
		pOut->PrintMessage("Cut figure : Select a figure first");
	}
	else
	{
		pOut->PrintMessage("Cut figure : Selected figures moved into clipboard");
	}
}
void CutAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (SelectedFigs[0] != NULL)
	{
		pManager->SetClipboard(SelectedFigs);

		for (int i = 0; i < selectedCount; i++)
		{
			pManager->RemoveFig();
			pOut->ClearDrawArea();
		}

		for (int i = 0; i < selectedCount; i++)
		{
			SelectedFigs[i]->SetSelected(false);
		}
		
	}
	pManager->ClearSelectedFigs();
	/*
	pManager->ExecuteAction(COPY);
	pManager->ExecuteAction(DEL);
	*/
}

CutAction::~CutAction()
{
}
