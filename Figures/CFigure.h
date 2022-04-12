#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>

//Base class for all figures
class CFigure
{
protected:
	int ID;									//Each figure has an ID
	bool Selected;					//true if the figure is selected.
	GfxInfo FigGfxInfo;						//Figure graphis info
	bool isZoomed;
	float ZoomScale;

public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool s);		//select/unselect the figure
	bool IsSelected() const;		//check whether fig is selected
	void SetID(int S_ID);			//Sets ID to figure's index in FigList.
	int GetID() const;				//Gets the ID of the figure

	float CalcDist(Point, Point) const;		//measure the length between two points


	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	virtual void Resize(float scale) = 0;	//Resize the figure
	void SetisZoomed(bool Z);
	void SetZoomScale(float scale);
	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &InFile) = 0;	//Load the figure parameters to the file
	string GetColorName(color);					//get color in form of string
	color GetColor(string);						//take color name and return the color

	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	virtual bool OnFig(int, int) = 0;			//check whether a point is within the figure region
	/////////////////////////////////////
	virtual CFigure* copy() = 0; //Copy figure
	virtual CFigure* paste(int, int) = 0;	//Paste figure
	////////////////////////////

	virtual Point UpperPoint() = 0;	//Returns the Upper point on the figure

	string virtual GetType() = 0;
	float virtual GetArea() = 0;
	virtual color GetColor();
};

#endif