#include"SwitchToDraw.h"
#include"..\ApplicationManager.h"

SwitchToDraw::SwitchToDraw(ApplicationManager* pApp):Action(pApp)
{}

void SwitchToDraw::ReadActionParameters()
{}

void SwitchToDraw::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	UI.InterfaceMode = MODE_DRAW;
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Welcome back to draw mode");
}

SwitchToDraw::~SwitchToDraw()
{
}
