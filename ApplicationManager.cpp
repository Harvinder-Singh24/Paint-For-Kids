#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\SelectAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\CopyAction.h"
#include "Actions\PasteAction.h"
#include "Actions\CutAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions/ResizeAction.h"
#include "Actions/ZoomAction.h"
#include "Actions/ChDrwClrAction.h"
#include "Actions/ChFillClrAction.h"
#include "CMUgraphicsLib/colors.h"
#include "Actions/ChBkColorAction.h"
#include"Actions/SwitchToPlay.h"
#include "Actions/SwitchToDraw.h"
#include"Actions/Pick_N_Hide.h"
#include"GUI/UI_Info.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	SelectedCount = 0;
	CID = 1;

	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	

}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);

			break;

		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriAction(this);
			break;

		case RESIZE:
			pAct = new ResizeAction(this);
			break;

		case CHNG_DRAW_CLR:
			pAct = new ChDrwClrAction(this);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChFillClrAction(this);
			break;

		case ITM_CHNG_BK_CLR:
			pAct = new ChBkClrAction(this);
			break;

		case ZOOM:
			pAct = new ZoomAction(this);
			break;

		case SELECT:
			pAct = new SelectAction(this);
			break;

		case DEL:
			pAct = new DeleteAction(this);
			break;

		case COPY:
			pAct = new CopyAction(this);
			break;

		case PASTE:
			pAct = new PasteAction(this);
			break;

		case CUT:
			pAct = new CutAction(this);
			break;

		case MOVE:
			pAct = new MoveAction(this);
			break;


		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			break;

		case TO_PLAY:
			pAct = new SwitchToPlay(this);
			break;

		case TO_DRAW:
			pAct = new SwitchToDraw(this);
			break;

		case PICK_N_HIDE:
			pAct = new Pick_N_Hide(this);
			break;

		case EXIT:
			///create ExitAction here
			if (FigCount > 0) {
				pOut->PrintMessage("If you proceed your files will not be save, click on save to save file, or click any where to Exit");
				ActionType Action = pIn->GetUserAction();
				if (Action == SAVE)
					ExecuteAction(Action);
			}
			EXIT;
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	

	CID++;
}
////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::GetFigCount()
{
	return FigCount;
}
////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::GetCID()
{
	return CID;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->OnFig(x, y))
			return FigList[i];
	}
	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
//==================================================================================//
//								Select Functions									//
//==================================================================================//

//pointer to the "SelectedFigs" array
CFigure* const* ApplicationManager::GetSelectedFigures() const
{
	return SelectedFigs;
}
////////////////////////////////////////////////////////////////////////////////////
// Adds a figure to the "SelectedFigs" array
void ApplicationManager::AddSelectedFigure(CFigure* S)
{

	SelectedFigs[SelectedCount] = S;
	SelectedCount++;
}
////////////////////////////////////////////////////////////////////////////////////
//Get the number of selected figures
int ApplicationManager::NewSelectedCount() const
{
	return SelectedCount;
}
////////////////////////////////////////////////////////////////////////////////////
//unselect a figure from the "SelectedFigs" array
void ApplicationManager::RemoveSelectedFigure(CFigure* S)
{

	for (int i = 0; i < SelectedCount; i++)
	{
		if (SelectedFigs[i] == S)
		{
			SelectedFigs[i] = SelectedFigs[SelectedCount - 1];
			SelectedFigs[SelectedCount - 1] = NULL;
			SelectedCount--;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearSelectedFigs() 
{
	for (int i = 0; i < SelectedCount; i++)
	{
		SelectedFigs[i] = NULL;
	}
	SelectedCount = 0;
}

//==================================================================================//
//								Save/Load Functions									//
//==================================================================================//
void ApplicationManager::SaveAll(ofstream &outputFile)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(outputFile);
	}
}
////////////////////////////////////////////////////////////////////////////////////
// for delete action
void ApplicationManager::RemoveFig()
{
	int i, j;
	for (i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected() == true)
		{

			for (j = i; j < FigCount; j++)
			{
				if (j < FigCount)
					FigList[j] = FigList[j + 1];
				else
				{
					delete FigList[j];
					FigList[j] = NULL;
				}

			}
			i--;
			FigCount--;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////
//Gets the number of figs currently in the clipboard
int ApplicationManager::getClipboardCount()
{
	return clipboardCount;
}

//////////////////////////////////////////////////////////////////////////////////
//Sets the clipboard array (overloaded)
void ApplicationManager::SetClipboard(CFigure* const* f)
{
	if (Clipboard != NULL)
		for (int i = 0; i < clipboardCount; i++)
		{
			delete Clipboard[i];
			Clipboard[i] = NULL;
		}

	for (int i = 0; i < SelectedCount; i++)
	{
		Clipboard[i] = f[i];
	}

	clipboardCount = SelectedCount;
}

//////////////////////////////////////////////////////////////////////////////////
//Gets the array of figs in the clipboard
CFigure* const* ApplicationManager::GetClipboardArr() const
{
	return Clipboard;
}

// resize selected figs
void ApplicationManager::ResizeFigures(float scale)
{
	for (int i = 0; i < SelectedCount; i++)
	{
		SelectedFigs[i]->Resize(scale);
	}
}

//zoom all figs
void ApplicationManager::Zoom(float scale)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetisZoomed(true);
		FigList[i]->SetZoomScale(scale);
	}
}

//Change draw color
void ApplicationManager::ChangeDrawColor(int ColorNum)
{
	for (int i = 0; i < SelectedCount; i++)
	{
		if (ColorNum == 1)
		{
			SelectedFigs[i]->ChngDrawClr(color(255, 0, 0));
		}
		else if (ColorNum == 2)
		{
			SelectedFigs[i]->ChngDrawClr(color(0, 255, 0));
		}
		else if (ColorNum == 3)
		{
			SelectedFigs[i]->ChngDrawClr(color(0, 0, 255));
		}
		else if (ColorNum == 4)
		{
			SelectedFigs[i]->ChngDrawClr(color(255, 165, 0));
		}
		else if (ColorNum == 5)
		{
			SelectedFigs[i]->ChngDrawClr(color(165, 42, 42));
		}
		else if (ColorNum == 6)
		{
			SelectedFigs[i]->ChngDrawClr(color(255, 255, 0));
		}
		else if (ColorNum == 7)
		{
			SelectedFigs[i]->ChngDrawClr(color(0, 0, 0));
		}
		else if (ColorNum == 8)
		{
			SelectedFigs[i]->ChngDrawClr(color(255, 255, 255));
		}
		else
		{
			pOut->PrintMessage("Color not found");
		}
	}
}

//Change fill color
void ApplicationManager::ChangeFillColor(int ColorNum)
{
	for (int i = 0; i < SelectedCount; i++)
	{
		if (ColorNum == 1)
		{
			SelectedFigs[i]->ChngFillClr(color(255, 0, 0));
		}
		else if (ColorNum == 2)
		{
			SelectedFigs[i]->ChngFillClr(color(0, 255, 0));
		}
		else if (ColorNum == 3)
		{
			SelectedFigs[i]->ChngFillClr(color(0, 0, 255));
		}
		else if (ColorNum == 4)
		{
			SelectedFigs[i]->ChngFillClr(color(255, 165, 0));
		}
		else if (ColorNum == 5)
		{
			SelectedFigs[i]->ChngFillClr(color(165, 42, 42));
		}
		else if (ColorNum == 6)
		{
			SelectedFigs[i]->ChngFillClr(color(255, 255, 0));
		}
		else if (ColorNum == 7)
		{
			SelectedFigs[i]->ChngFillClr(color(0, 0, 0));
		}
		else if (ColorNum == 8)
		{
			SelectedFigs[i]->ChngFillClr(color(255, 255, 255));
		}
		else
		{
			pOut->PrintMessage("Color not found");
		}
	}
}
//change background color
void ApplicationManager::ChangeBackGroundColor(int ColorNum)
{
	if (ColorNum == 1)
	{
		UI.BkGrndColor = (color(255, 0, 0));
	}
	else if (ColorNum == 2)
	{
		UI.BkGrndColor = (color(0, 255, 0));
	}
	else if (ColorNum == 3)
	{
		UI.BkGrndColor = (color(0, 0, 255));
	}
	else if (ColorNum == 4)
	{
		UI.BkGrndColor = (color(255, 165, 0));
	}
	else if (ColorNum == 5)
	{
		UI.BkGrndColor = (color(165, 42, 42));
	}
	else if (ColorNum == 6)
	{
		UI.BkGrndColor = (color(255, 255, 0));
	}
	else if (ColorNum == 7)
	{
		UI.BkGrndColor = (color(0, 0, 0));
	}
	else if (ColorNum == 8)
	{
		UI.BkGrndColor = (color(255, 255, 255));
	}
	else
	{
		pOut->PrintMessage("Color not found");
	}
}

string ApplicationManager::GetRandomType()
{
	int counter = 0; int x;
	bool R = 0, T = 0, C = 0, L = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetType() == "R")
		{
			R = 1;
		}
		else if (FigList[i]->GetType() == "C")
		{
			C = 1;
		}
		else if (FigList[i]->GetType() == "L")
		{
			L = 1;
		}
		else if (FigList[i]->GetType() == "T")
		{
			T = 1;
		}

	}
	if (R == 1)
	{
		counter++;
	}
	if (C == 1)
	{
		counter++;
	}
	if (T == 1)
	{
		counter++;
	}
	if (L == 1)
	{
		counter++;
	}
	string* ArrayOfStrings = new string[counter];
	int i = 0;

	if (R == 1)
	{
		ArrayOfStrings[i] = "R";
		i++;
	}
	if (C == 1)
	{
		ArrayOfStrings[i] = "C";
		i++;
	}
	if (T == 1)
	{
		ArrayOfStrings[i] = "T";
		i++;
	}
	if (L == 1)
	{
		ArrayOfStrings[i] = "L";
		i++;
	}

	x = rand() % (counter);
	return ArrayOfStrings[x];
}

int ApplicationManager::GetNumOfPlayFig()
{
	int num = 0;
	string s = GetRandomType();
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetType() == s)
		{
			num++;
		}
	}
	return num;
}


float* ApplicationManager::GetArrayOfAreas()
{
	float* ArrayOfAreas = new float[FigCount]; float temp;
	for (int i = 0; i < FigCount; i++)
	{
		ArrayOfAreas[i] = FigList[i]->GetArea();
	}
	for (int i = 0; i < FigCount; ++i)		//sorting in descending order
	{
		for (int j = i + 1; j < FigCount; ++j)
		{
			if (ArrayOfAreas[i] < ArrayOfAreas[j])
			{
				temp = ArrayOfAreas[i];
				ArrayOfAreas[i] = ArrayOfAreas[j];
				ArrayOfAreas[j] = temp;
			}
		}
	}
	return ArrayOfAreas;
}

void ApplicationManager::RemoveFig(CFigure* SelectedFig)
{
	{
		SelectedFigs[0] = SelectedFig;
		SelectedCount++;
		RemoveFig();
	}
}

color ApplicationManager::GetRandomClr()
{
	int x = rand() % FigCount;
	while (FigList[x]->GetType() == "L")
	{
		x = rand() % FigCount;
	}

	return (FigList[x]->GetColor());
}

int ApplicationManager::GetNumOfClrPlayFig(color c, color Fig)
{
	string ColorName;
	if (c.ucRed == 255 && c.ucGreen == 0 && c.ucBlue == 0) {
		ColorName = "RED";
	}
	if (c.ucRed == 190 && c.ucGreen == 190 && c.ucBlue == 190) {
		ColorName = "GRAY";
	}
	if (c.ucRed == 0 && c.ucGreen == 0 && c.ucBlue == 255) {
		ColorName = "BLUE";
	}
	int num = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetColorName(Fig) == ColorName)
		{
			num++;
		}
	}
	return num;
}

bool ApplicationManager::IsCorrectClr(CFigure* Selected, color rand, color OfSelected)
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
	if (Selected->GetColorName(OfSelected) == ColorName)
	{
		return true;
	}
}