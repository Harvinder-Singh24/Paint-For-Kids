#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	isZoomed = false;
	ZoomScale = 0;
}

float CFigure::CalcDist(Point a, Point b) const 
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::SetID(int S_ID)
{	ID = S_ID;	}

int CFigure::GetID() const
{	return ID;	}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

string CFigure::GetColorName(color c)
{
	if (c.ucRed == 255 && c.ucGreen == 255 && c.ucBlue == 255) {
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

color CFigure::GetColor(string Name)
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

void CFigure::SetisZoomed(bool Z)
{
	isZoomed = Z;
}

void CFigure::SetZoomScale(float scale)
{
	ZoomScale = scale;
}

color CFigure::GetColor()
{
	if (FigGfxInfo.isFilled == true)
		return FigGfxInfo.FillClr;
	else return NULL;
}