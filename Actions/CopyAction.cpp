#include "CopyAction.h"
#include"..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Input.h"



CopyAction::CopyAction(ApplicationManager* pApp) :Action(pApp)
{
	for (int i = 0; i < MaxFigCount; i++)
	{
		newSelFigs[i] = NULL;
	}

}

void CopyAction::ReadActionParameters()
{

	SelectedFigs = pManager->GetSelectedFigures();
	SelectedCount = pManager->NewSelectedCount();
	Output* pOut = pManager->GetOutput();

	if (SelectedFigs[0] == NULL)
	{
		pOut->PrintMessage("Please select a figure first");
	}
	else
	{
		pOut->PrintMessage("Selected figures are copied");
	}

}

void CopyAction::Execute()
{
	ReadActionParameters();
	if (SelectedFigs[0] != NULL)
	{
		for (int i = 0; i < SelectedCount; i++)
		{
			newSelFigs[i] = SelectedFigs[i]->copy();
			newSelFigs[i]->SetSelected(false);

		}
		pManager->SetClipboard(newSelFigs);
	}

}

CopyAction::~CopyAction()
{
}
