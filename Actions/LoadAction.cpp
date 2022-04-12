#include "LoadAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/output.h"
#include <fstream>
#include"..\Figures/CRectangle.h"
#include"..\Figures/CCircle.h"
#include"..\Figures/CLine.h"
#include"..\Figures/CTriangle.h"


LoadAction::LoadAction(ApplicationManager*pApp) :Action(pApp){}

//the function reads the color name from the saved file and return it in the form of color not string we will use it to to set the colores when we load
color LoadAction::GetColor(string Name)
{
	if (Name == "WHITE") {
		return WHITE;
	}
	if (Name == "BLACK") {
		return BLACK;
	}
	if (Name == "GRAY") {
		return GRAY;
	}
	if (Name == "BLUE") {
		return BLUE;
	}
	if (Name == "CYAN") {
		return CYAN;
	}
	if (Name == "GREEN") {
		return GREEN;
	}
	if (Name == "YELLOW") {
		return YELLOW;
	}
	if (Name == "BROWN") {
		return BROWN;
	}
	if (Name == "ORANGE") {
		return ORANGE;
	}
	if (Name == "RED") {
		return RED;
	}
	if (Name == "PINK") {
		return PINK;
	}
}



void LoadAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//here we will check if the file is valid or not, we will know if the input is not empty, and the file is opened 
	bool input = true;
	do 
	{
		if (!input)
		{
			pOut->PrintMessage("File not found, please try again");
			Sleep(1500);
		}
		pOut->PrintMessage("Load: Please enter file name that you want to load from");

		FileName = pIn->GetSrting(pOut);
		if (FileName.empty())
			break;
		FileName += ".txt";
		inputFile.open(FileName);
		input = false;
	} while (!inputFile.is_open());
	pManager->GetOutput()->ClearStatusBar();
}

void LoadAction::Execute()
{
	ReadActionParameters();

	string Draw_Color;
	string Fill_Color;
	string Background_Color;
	int Number_of_Figures;

	//reading info from the file
	inputFile >> Draw_Color >> Fill_Color >> Background_Color >> Number_of_Figures;

	//setting the colors after we read them from the file
	UI.DrawColor = GetColor(Draw_Color);
	UI.FillColor = GetColor(Fill_Color);
	UI.BkGrndColor = GetColor(Background_Color);

	/*
	here we add the figures, its done as follow
	1. set an empty info to pass them to each fig, which will be filled in the figures classes.
	2. loop from zero to the number of the figures which we read above.
	3. create new fig with empty info
	4. load the info of the figure from functions of figure classes
	5. add figures
	*/
	string Shape;
	for (int i = 0; i < Number_of_Figures; i++) 
	{
		Point emptyP = Point();
		GfxInfo emptyGFX = GfxInfo();
		int emptyID = int();
		inputFile >> Shape;
		if (Shape == "LINE") {
			CLine* line = new CLine(emptyP, emptyP, emptyGFX, emptyID);
			line->Load(inputFile);
			pManager->AddFigure(line);
		}
		if (Shape == "CIRCLE") {
			CCircle* circ = new CCircle(emptyP, emptyP, emptyGFX, emptyID);
			circ->Load(inputFile);
			pManager->AddFigure(circ);
		}
		if (Shape == "RECT") {
			CRectangle* rect = new CRectangle(emptyP, emptyP, emptyGFX, emptyID);
			rect->Load(inputFile);
			pManager->AddFigure(rect);
		}
		if (Shape == "TRIANG") {
			CTriangle* tri = new CTriangle(emptyP, emptyP, emptyP, emptyGFX, emptyID);
			tri->Load(inputFile);
			pManager->AddFigure(tri);
		}
	}
	inputFile.close();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Loaded Successfully");
	Sleep(1000);
	pManager->GetOutput()->ClearStatusBar();
}

LoadAction::~LoadAction()
{
}