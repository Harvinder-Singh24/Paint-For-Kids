#include"SwitchToPlay.h"
#include"..\ApplicationManager.h"

SwitchToPlay::SwitchToPlay(ApplicationManager* pApp):Action(pApp)
{}

void SwitchToPlay::ReadActionParameters()
{}

void SwitchToPlay::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->GetFigCount() > 0)
	{
		UI.InterfaceMode = MODE_PLAY;
		pOut->CreatePlayToolBar();
		pOut->PrintMessage("Let's Play!!");
	}
	else
		pOut->PrintMessage("Draw a figure to start playing first!");
}

SwitchToPlay::~SwitchToPlay()
{
}
