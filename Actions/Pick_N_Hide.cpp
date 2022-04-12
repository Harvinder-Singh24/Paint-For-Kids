#include"Pick_N_Hide.h"
#include "..\ApplicationManager.h"
#include"..\GUI\Output.h"
#include"..\GUI\Input.h"
#include"..\DEFS.h"
#include <windows.h>

Pick_N_Hide::Pick_N_Hide(ApplicationManager* pApp):Action(pApp)
{
}

void Pick_N_Hide::ReadActionParameters()
{}

void Pick_N_Hide::Execute()
{
	right = 0; wrong = 0;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	string test = pManager->GetRandomType();
	int TotNumOfFigures = pManager->GetFigCount();
	float* ArrayOfAreas = new float[TotNumOfFigures];
	color ColorOfPlayFig = pManager->GetRandomClr();
	pOut->PrintMessage("Choose the game mode you want to play!");
	Sleep(3000);
	pOut->PrintMessage("Type 's' to start picking by shapes, 'c' to pick by color, 'b' to pick by both shape and color, or 'a' to pick by area!");
	string Act = pIn->GetSrting(pOut);

	if (Act == "s")
	{
		string FullTest = " ";
		if (test == "C")
		{
			FullTest = "circle";
			pOut->PrintMessage("The game has started select all " + (FullTest)+"(s) to win");
		}
		if (test == "T")
		{
			FullTest = "triangle";
			pOut->PrintMessage("The game has started select all " + (FullTest)+"(s) to win");
		}
		if (test == "R")
		{
			FullTest = "rectangle";
			pOut->PrintMessage("The game has started select all " + (FullTest)+"(s) to win");
		}
		if (test == "L")
		{
			FullTest = "line";
			pOut->PrintMessage("The game has started select all " + (FullTest)+"(s) to win");
		}
		Sleep(3000);
		if (test != "NULL")
		{
			NumOfPlayFig = pManager->GetNumOfPlayFig();

			while (right != NumOfPlayFig)
			{
				pIn->GetPointClicked(P.x, P.y);
				CFigure* FigSelected = pManager->GetFigure(P.x, P.y);
				if (FigSelected == NULL)
				{
					pOut->PrintMessage("Please select a valid point inside a figure!");
					Sleep(1000);
				}
				else if (FigSelected->GetType() == test)
				{
					right++;
					pOut->PrintMessage("Bravooo! Select all remaining " + (test)+"(s)");
					pManager->RemoveFig(FigSelected);
				}
				else
				{
					wrong++;
					pOut->PrintMessage("Oh oh! Select all remaining " + (test)+"(s)");
				}
			}
		}
		pOut->PrintMessage("Bravooo! You have made " + to_string(right) + " correct out of " + to_string(right + wrong) + " tries!");
		Sleep(5000);
		pOut->ClearStatusBar();
	}

	else if (Act == "a")
	{
		pOut->PrintMessage("The game has started! Select from the biggest to smallest figures");
		for (int i = 0; i < TotNumOfFigures; i++)
		{
			ArrayOfAreas[i] = pManager->GetArrayOfAreas()[i];
		}
			float* NewArray = new float[TotNumOfFigures];
			for (int i = 0; i < TotNumOfFigures; i++)
			{
				pIn->GetPointClicked(P.x, P.y);
				CFigure* FigSelected = pManager->GetFigure(P.x, P.y);
				NewArray[i] = FigSelected->GetArea();
			}
			for (int i = 0; i < TotNumOfFigures; i++)
			{
				if (NewArray[i] == ArrayOfAreas[i])
				{
					right++;
				}
			}
		pOut->PrintMessage("Well done! you had " + to_string(right) + " correct out of " + to_string(TotNumOfFigures) + " tries!");
	}

	else if (Act == "c")
	{
		while (right != pManager->GetNumOfClrPlayFig(ColorOfPlayFig, OfSelected))
		{
			pIn->GetPointClicked(P.x, P.y);
			CFigure* FigSelected = pManager->GetFigure(P.x, P.y);
			OfSelected = FigSelected->GetColor();
			pOut->PrintMessage("The game has started! Select all " + ColorToString(ColorOfPlayFig) + " colored figures!");
			Sleep(3300);
			if (pManager->IsCorrectClr(FigSelected, ColorOfPlayFig, OfSelected))
			{
				right++;
				pOut->PrintMessage("Bravoo!! Now select all " + ColorToString(ColorOfPlayFig) + " colored figure(s)!");
			}
			else if (!(pManager->IsCorrectClr(FigSelected, ColorOfPlayFig, OfSelected)))
			{
				wrong++;
				pOut->PrintMessage("Oh oh! Now select all " + ColorToString(ColorOfPlayFig) + " colored figure(s)");
			}
			else { pOut->PrintMessage("Please select a valid point!"); }
		}

		pOut->PrintMessage("Bravooo! You have made " + to_string(right) + " correct out of " + to_string(right + wrong) + " tries");
	}
	else if (Act == "b")
	{
		while (right != TotNumOfFigures)
		{
			pIn->GetPointClicked(P.x, P.y);
			CFigure* FigSelected = pManager->GetFigure(P.x, P.y);
			pOut->PrintMessage("The game has started! Select all "+(test)+" colored " + ColorToString(ColorOfPlayFig));
			if (FigSelected == NULL)
			{
				pOut -> PrintMessage("Select a valid point!");
			}
			if ((pManager->IsCorrectClr(FigSelected, ColorOfPlayFig,OfSelected)) && (FigSelected->GetType() == test))
			{
				right++;
				pOut->PrintMessage("Bravooo! Now select all " + (test)+"(s) colored " + ColorToString(ColorOfPlayFig));
			}
			else
				wrong++;
			pOut->PrintMessage("Bravooo! Now select remaining " + (test)+"(s) colored " + ColorToString(ColorOfPlayFig));
		}
	}
	else
	{
		if (Act != "s" || Act != "c" || Act != "b" || Act != "a")
		{
			pOut->PrintMessage("Please enter a valid entry from ('s', 'c', 'b', 'a')");
			Act = pIn->GetSrting(pOut);
		}
	}
}
string Pick_N_Hide::ColorToString(color rand)
{
	string ColorName;
	if (rand.ucRed == 255 && rand.ucGreen == 0 && rand.ucBlue == 0) {
		ColorName = "RED";
	}
	if (rand.ucRed == 190 && rand.ucGreen == 190 && rand.ucBlue == 190) {
		ColorName = "GRAY";
	}
	if (rand.ucRed == 0 && rand.ucGreen == 0 && rand.ucBlue == 255) {
		ColorName = "BLUE";
	}
	return ColorName;
}

Pick_N_Hide::~Pick_N_Hide(){}
