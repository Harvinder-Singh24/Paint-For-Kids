#include "SaveAction.h"
#include "..\GUI/Input.h"
#include "..\GUI/output.h"
#include "..\ApplicationManager.h"
#include <fstream>


SaveAction::SaveAction(ApplicationManager* pApp) :Action(pApp){}

//the function reads the color from the info of the application and return it in the form of string, so that we can print it in the txt file
string SaveAction::GetColor(color c)
{
	if (c.ucRed == 255 && c.ucGreen == 255 && c.ucBlue==255) {
		return "WHITE";
	}
	if (c.ucRed == 0 && c.ucGreen == 0 && c.ucBlue == 0) {
		return "BLACK";
	}
	if (c.ucRed == 190 && c.ucGreen == 190 && c.ucBlue == 190) {
		return "GRAY";
	}
	if (c.ucRed == 0 && c.ucGreen == 0 && c.ucBlue == 255) {
		return "BLUE";
	}
	if (c.ucRed == 0 && c.ucGreen == 255 && c.ucBlue == 255) {
		return "CYAN";
	}
	if (c.ucRed == 0 && c.ucGreen == 255 && c.ucBlue == 0) {
		return "GREEN";
	}
	if (c.ucRed == 255 && c.ucGreen == 255 && c.ucBlue == 0) {
		return "YELLOW";
	}
	if (c.ucRed == 165 && c.ucGreen == 42 && c.ucBlue == 42) {
		return "BROWN";
	}
	if (c.ucRed == 255 && c.ucGreen == 165 && c.ucBlue == 0) {
		return "ORANGE";
	}
	if (c.ucRed == 255 && c.ucGreen == 0 && c.ucBlue == 0) {
		return "RED";
	}
	if (c.ucRed == 255 && c.ucGreen == 192 && c.ucBlue == 203) {
		return "PINK";
	}
}



void SaveAction::ReadActionParameters()
{
	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Save: Please enter file name(without spaces!) to save your work");

	//if the user didn't set a name for the file the file name will be set with default name "save"
	FileName = pIn->GetSrting(pOut);
	if (FileName.empty())
		FileName = "save";
	pManager->GetOutput()->ClearStatusBar();
}

void SaveAction::Execute()
{
	ReadActionParameters();
	
	outputFile.open(FileName + ".txt", ios::out);

	//getting the colors to change the format to string
	string Draw_Color = GetColor(UI.DrawColor);
	string Fill_Color = GetColor(UI.FillColor);
	string Background_Color = GetColor(UI.BkGrndColor);
	int Number_of_Figures = pManager->GetFigCount();

	outputFile << Draw_Color << '\t' << Fill_Color << '\t' << Background_Color << endl << Number_of_Figures << endl;

	pManager->SaveAll(outputFile);

	outputFile.close();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Saved Successfully");
	Sleep(1000);
	pManager->GetOutput()->ClearStatusBar();
}

SaveAction::~SaveAction()
{
}