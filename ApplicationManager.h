#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include <fstream>

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFigs[MaxFigCount]; //List of all selected figures (Array of pointers)

	int SelectedCount;		//number of selected Figs 

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	INT CID;

	CFigure* Clipboard[MaxFigCount];	//Pointer to the copied/cut figure
	int clipboardCount;					//Number of figures in clipboard

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);			//Adds a new figure to the FigList
	int GetFigCount();						//used to get number of fiures
	int GetCID();							//used to make an id for each figure
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window

	// -- Select Functions
	int NewSelectedCount() const;					//Get the number of selected figures
	CFigure* const* GetSelectedFigures() const;		//pointer to the "SelectedFigs" array
	void AddSelectedFigure(CFigure*);				//Adds a figure to the "SelectedFigs" array
	void RemoveSelectedFigure(CFigure*);			//Removes a figure from the "SelectedFigs" array
	void ClearSelectedFigs();                       //Clear SelectedFig array

	// -- Save/Load Functions
	void SaveAll(ofstream & outputFile);

	//////////////////////////
	void RemoveFig();
	// -- Copy/Cut/Paste Functions -- //
	int getClipboardCount();				//Gets no. of figures in clipboard
	void SetClipboard(CFigure* const*);		//Sets figures in clipboard
	CFigure* const* GetClipboardArr()const;		//returns the array in clipboard
	//////////////////////////
	void ResizeFigures(float scale);
	void Zoom(float scale);
	void ChangeDrawColor(int ColorNum);
	void ChangeFillColor(int ColorNum);
	void ChangeBackGroundColor(int ColorNum);
	//////////////////////////
	void RemoveFig(CFigure*);
	color GetRandomClr();				//Computer choses a color based on figures from the graph
	int GetNumOfClrPlayFig(color Rand, color OfSelected);		//Gets the number of Random color chosen by computer

	bool IsCorrectClr(CFigure* Selected, color f, color OfSelected);
	string GetRandomType();							//Gets random type chosen by computer based on shapes on the graph
	int GetNumOfPlayFig();							//Gets the number of Random shapes chosen by computer
	float* GetArrayOfAreas();						//Gets array of area and sort in in descending order
};

#endif